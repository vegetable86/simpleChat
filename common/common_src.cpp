#include "common_src.h"

#include <QDebug>

// 序列化消息
QByteArray streamMessage(const MessageHeader &header, const QByteArray &body){
    // 最终的消息包
    QByteArray packet;
    // 构造一个二进制的数据流
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream << header.type
           << header.length
           << header.sender
           << header.receiver
           << header.timestamp;
    if(body != nullptr){
        packet.append(body);
    }
    // 返回构造的数据包
    return packet;
}


Message reStreamMessage(QByteArray &data){
    QDataStream stream(&data, QIODevice::ReadOnly);

    // 反序列化
    // 消息头
    MessageHeader header;
    stream >> header.type
        >> header.length
        >> header.sender
        >> header.receiver
        >> header.timestamp;
    // 消息体
    qint32 offset = stream.device()->pos();
    QByteArray body = data.mid(offset);
    return {header, body};
}

// 登录请求发送的消息体中解析出用户的账号和密码
// 格式为  账号长度 | 账号 | 密码长度 | 密码
User getUser(QByteArray body){
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

