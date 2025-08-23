#include "registerwindow.h"
#include "ui_registerwindow.h"

registerWindow::registerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerWindow)
{
    ui->setupUi(this);
}


registerWindow::registerWindow(QWidget *parent, QTcpSocket *socket)
    : QWidget(parent)
    , socket(socket)
    , ui(new Ui::registerWindow)
{
    ui->setupUi(this);

    // 向服务器发送注册请求
    QObject::connect(this->ui->registeButton, &QPushButton::clicked, this, [&](){
        if(socket == nullptr || socket->state() == QAbstractSocket::UnconnectedState){
            this->ui->tipsLabel->setText("网络未连接");
            return;
        }
        QString userName, passWord;
        userName = this->ui->userNameEdit->toPlainText().trimmed();
        passWord = this->ui->passWordEdit->toPlainText().trimmed();
        if(userName.size() == 0 || passWord.size() == 0){
            this->ui->tipsLabel->setText("账号或者密码不符合规则");
            return ;
        }

        QByteArray body;
        QDataStream stream(&body, QIODevice::WriteOnly);
        stream << (qint16)userName.size()
               << userName
               << (qint16)passWord.size()
               << passWord;
        // 向服务器发送一条注册消息
        // 消息体格式: | 用户名长度 | 用户名 | 密码长度 | 密码 |
        QByteArray packet = streamMessage({MessageType::MSG_REGISTER_REQ, 0, "", "", QDateTime::currentSecsSinceEpoch()}, body);
        socket->write(packet);
    });

    // 点击backButton后向外发送一个返回信号
    QObject::connect(this->ui->backButton, &QPushButton::clicked, this, [&](){
        emit pushBackButton();
    });

}

registerWindow::~registerWindow()
{
    delete ui;
}
