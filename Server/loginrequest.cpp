#include "loginrequest.h"

loginRequest::loginRequest() {}

loginRequest::loginRequest(Message message){
    User need = getUser(message.body);
    qDebug() << "loginRequest.cpp (7) 接收到登录请求";

    // 数据库查询用户账号和密码
    // 如果查询成功给客户端发送个允许登录
    // 不成功就发送登录失败，账号不存在或者
    QSqlQuery query;
    query.prepare("SELECT * FROM qq WHERE username = :username AND password_hash = :password");
    query.bindValue(":username", need.userName);
    query.bindValue(":password", need.passWord);
    query.exec();

    // 如果查询结果存在
    if(query.next()){
        qDebug() << "数据查询成功,存在用户:" << need.userName << "登录成功";
        allowLogin = true;
    }
    // 如果不存在
    else{
        allowLogin = false;
    }
}

// 登录请求发送的消息体中解析出用户的账号和密码
// 格式为  账号长度 | 账号 | 密码长度 | 密码
User loginRequest::getUser(QByteArray body){
    qint16 userNameLength, passWordLength;
    QString userName, passWord;

    QDataStream stream(&body, QIODevice::ReadOnly);

    // 账号
    stream >> userNameLength;
    userName.resize(userNameLength);
    stream >> userName;

    // 密码
    stream >> passWordLength;
    passWord.resize(passWordLength);
    stream >> passWord;
    return {userName, passWord};
}
