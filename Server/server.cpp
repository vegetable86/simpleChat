#include "server.h"


Server::Server(QWidget *parent)
    : QWidget{parent}
{
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress("127.0.0.1", 8080))){
        qDebug() << "服务器监听失败: " << server->serverAddress();
        QCoreApplication::exit(1);
    }
    qInfo() << "服务器启动，监听端口：" << server->serverPort();

    QObject::connect(server, &QTcpServer::newConnection, this, [this](){
        handleNewConnect(server);
    });
}


void Server::handleNewConnect(QTcpServer *server){

    //获取下一个连接的客户端socket
    QTcpSocket *client = server->nextPendingConnection();

    qInfo() << "获取到新的客户端连接:" << client->peeerAddress().toString()
            << ":"
            << client->peerPort();

    // 对Tcp协议栈的修改
    client->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    QObject::connect(client, &QTcpSocket::readyRead, this, [this](){
        handleClientDate(client);
    });
}

void Server::handleClientDate(QTcpSocket *client){
    // 将二进制流解析成message
    QByteArray data = client->readAll();
    Message message = reStreamMessage(data);

    qDebug() << "解析message";
    eventDispatch(message);
}

void Server::eventDispatch(Message message){
    switch(message.header.type){
        EVENT_DISPATCH_CASE(MSG_LOGIN_REQ);
    }
}
