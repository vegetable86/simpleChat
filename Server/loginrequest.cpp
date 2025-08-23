#include "loginrequest.h"

loginRequest::loginRequest() {}

loginRequest::loginRequest(Message &message, Server *server, QTcpSocket *client) {
    Q_UNUSED(server);

    User need = getUser(message.body);
    qDebug() << "loginRequest.cpp (7) 接收到登录请求";


    // 数据库查询用户账号和密码
    // 如果查询成功给客户端发送个允许登录
    // 不成功就发送登录失败，账号不存在或者
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password_hash = :password");
    query.bindValue(":username", need.userName);
    query.bindValue(":password", need.passWord);
    query.exec();

    qDebug() << "登录账号 查询中...  " << need.userName;
    // 如果查询结果存在
    if(query.next()){
        // if(1){
        client->write(streamMessage({MessageType::MSG_LOGIN_RESP_ALLOW, 0, "", "", QDateTime::currentMSecsSinceEpoch()}, nullptr));
    }
    // 如果不存在
    else{
        client->write(streamMessage({MessageType::MSG_LOGIN_RESP_REJECT, 0, "", "", QDateTime::currentMSecsSinceEpoch()}, nullptr));
    }
}
