#include "client.h"

// 可点击Label
ClickedLabel::ClickedLabel(QWidget *parent) : QLabel{parent}{

}

void ClickedLabel::mousePressEvent(QMouseEvent *mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        emit clicked();
    }
}


// 客户端开始界面
Client::Client(QWidget *parent)
    : QWidget{parent}
{
     // socket链接
    socket = new QTcpSocket(this);
    qDebug() << "连接中...";
    QHostAddress address("127.0.0.1");
    socket->connectToHost(address, 8080);

    //界面初始化
    loginSuccessWindow = new loginSuccess;
    loginFailWindow = new loginFail;
    registerWindows = new registerWindow(nullptr, this->socket);

    mainBox = new QVBoxLayout(this);
    box = new QVBoxLayout;
    registerAndLogin = new QHBoxLayout;

    // Client主页面的控件
    userNameBlock = new QLabel("用户名");
    userName = new QTextEdit;
    passWordBlock = new QLabel("密码");
    passWord = new QTextEdit;
    loginButton = new QPushButton;
    socketConnectSuccessSign = new QLabel("服务器连接中...");
    registerUser = new ClickedLabel;

    userName->setFixedSize(300, 27);
    passWord->setFixedSize(300, 27);
    loginButton->setFixedSize(200, 27);
    loginButton->setText("登录");
    loginButton->setEnabled(false);
    registerUser->setText("点击进行注册");

    box->addWidget(userNameBlock);
    box->addWidget(userName);
    box->addWidget(passWordBlock);
    box->addWidget(passWord);
    registerAndLogin->addWidget(registerUser);
    registerAndLogin->addWidget(loginButton);

    mainBox->addLayout(box);
    mainBox->addLayout(registerAndLogin);
    mainBox->addWidget(socketConnectSuccessSign);




    // 成功连接到服务器之后会出现连接成功的字样
    QObject::connect(socket, &QTcpSocket::connected, this, [=](){
        socketConnectSuccessSign->setText("服务器连接成功，可以登录");
        loginButton->setEnabled(true);
    });

    // 点击登录按钮之后发送一个登录请求到服务器
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

    // 发送登录成功信号，并跳转出登录成功界面
    QObject::connect(this, &Client::loginAllow, loginSuccessWindow, [&](){
        loginSuccessWindow->show();
    });

    // 发送登录失败信号，并跳转出登录失败界面
    QObject::connect(this, &Client::loginReject, loginFailWindow, [&](){
        loginFailWindow->show();
    });

    // 点击注册label，跳转到注册页面
    QObject::connect(this->registerUser, &ClickedLabel::clicked, registerWindows, [&](){
        this->hide();
        registerWindows->show();
    });

    // 注册返回按钮，返回登录界面
    QObject::connect(registerWindows, &registerWindow::pushBackButton, this, [&](){
        registerWindows->hide();
        this->show();
    });

    // 注册成功之后的逻辑
    QObject::connect(this, &Client::registerSuccess, registerWindows, [&](){
        registerWindows->successRegister();
    });

    // 注册失败
    QObject::connect(this, &Client::registerFail, registerWindows, [&](){
        registerWindows->failRegister();
    });
}


void Client::eventDispatch(Message message){
    switch(message.header.type){
        // 登录
        EVENT_DISPATCH_CASE(MSG_LOGIN_RESP_ALLOW);
        EVENT_DISPATCH_CASE(MSG_LOGIN_RESP_REJECT);
        // 注册
        EVENT_DISPATCH_CASE(MSG_REGISTER_RESP_ALLOW);
        EVENT_DISPATCH_CASE(MSG_REGISTER_RESP_REJECT);
    }
}

QByteArray Client::sendLoginMessage(QString userName, QString passWord){
    // 账号密码写入登录的消息体
    // 构造出的结构: 账号长度(2字节) | 账号 | 密码长度(2字节) | 密码
    QByteArray body;
    QDataStream bodyStream(&body, QIODevice::ReadWrite);
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


