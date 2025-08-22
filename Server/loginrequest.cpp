#include "loginrequest.h"

loginRequest::loginRequest() {}

loginRequest::loginRequest(Message message){
    User need = getUser(message.body);
    qDebug() << "用户名:" << need.userName;
    qDebug() << "密码:" << need.passWord;

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
