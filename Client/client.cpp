#include "client.h"

Client::Client(QWidget *parent)
    : QWidget{parent}
{
    box = new QVBoxLayout(this);
    userNameBlock = new QLabel("用户名");
    userName = new QTextEdit;
    passWordBlock = new QLabel("密码");
    passWord = new QTextEdit;
    loginButton = new QPushButton;
    socketConnectSuccessSign = new QLabel("服务器连接中...");


    userName->setFixedSize(200, 27);
    passWord->setFixedSize(200, 27);
    loginButton->setFixedSize(200, 27);
    loginButton->setText("登录");
    loginButton->setEnabled(false);

    box->addWidget(userNameBlock);
    box->addWidget(userName);
    box->addWidget(passWordBlock);
    box->addWidget(passWord);
    box->addWidget(loginButton);
    box->addWidget(socketConnectSuccessSign);


    socket = new QTcpSocket;


    qDebug() << "连接中...";
    QHostAddress address("127.0.0.1");
    socket->connectToHost(address, 8080);


    // 成功连接到服务器之后会出现连接成功的字样
    QObject::connect(socket, &QTcpSocket::connected, this, [=](){
        socketConnectSuccessSign->setText("服务器连接成功，可以登录");
        loginButton->setEnabled(true);
    });

    // 点击按钮之后发送一个登录请求到服务器
    QObject::connect(loginButton, &QPushButton::clicked, this, [=](){
        // 需要构造一个消息头
        // MessageHeader
        // 登录
        qDebug() << "点击登录，发送请求";
        socket->write(sendLoginMessage(userName->toPlainText(), passWord->toPlainText()));
    });

    // 客户端接收到消息
    QObject::connect(socket, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = socket->readAll();
        Message message = reStreamMessage(data);

        qDebug() << "客户端解析登录响应信息";

        eventDispatch(message);
    });
}


void Client::eventDispatch(Message message){
    switch(message.header.type){
        EVENT_DISPATCH_CASE(MSG_LOGIN_RESP_ALLOW);
        EVENT_DISPATCH_CASE(MSG_LOGIN_RESP_REJECT);
    }
}

QByteArray Client::sendLoginMessage(QString userName, QString passWord){
    // 账号密码写入登录的消息体
    // 构造出的结构: 账号长度(2字节) | 账号 | 密码长度(2字节) | 密码
    QByteArray body;
    QDataStream bodyStream(&body, QIODevice::WriteOnly);
    bodyStream << (qint16)userName.size()
               << userName
               << (qint16)passWord.size()
               << passWord;

    MessageHeader messageHeader = {MessageType::MSG_LOGIN_REQ,
                                   (quint32)body.size(),
                                   "",
                                   "",
                                   QDateTime::currentSecsSinceEpoch()};

    return streamMessage(messageHeader, body);
}


