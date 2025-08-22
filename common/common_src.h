#ifndef COMMON_SRC_H
#define COMMON_SRC_H

#include "Protocol.h"

#include <QIODevice>

// 序列化消息
QByteArray streamMessage(const MessageHeader &header, const QByteArray &body);

// 反序列化消息
Message reStreamMessage(QByteArray &data);


#endif // COMMON_SRC_H
