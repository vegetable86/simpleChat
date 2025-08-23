#include "registerrequest.h"

registerRequest::registerRequest() {}

registerRequest::registerRequest(Message &message, Server *server, QTcpSocket *client) {
    User need = getUser(message.body);

    qDebug() << "registerRequest(8) 接收到注册请求";

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password_hash = :password");
    query.bindValue(":username", need.userName);
    query.bindValue(":password", need.passWord);
    query.exec();

    qDebug() << "注册账号查询中...  " << need.userName;

    // 如果能够创建，那么就创建账号，并向客户端发送一个注册成功消息
    if(!query.next()) {
        query.prepare("INSERT INTO users (username, password_hash) VALUE (:username, :password)");
        query.bindValue(":username", need.userName);
        query.bindValue(":password", need.passWord);
        query.exec();
        // 向客户端发送一个注册成功消息
        client->write(streamMessage({MSG_REGISTER_RESP_ALLOW, 0, "", "", QDateTime::currentSecsSinceEpoch()}, nullptr));
    }
    // 如果不能够创建，那么就向客户端发送一个注册失败的消息
    else{
        client->write(streamMessage({MSG_REGISTER_RESP_REJECT, 0, "", "", QDateTime::currentSecsSinceEpoch()}, nullptr));
    }

}
