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

