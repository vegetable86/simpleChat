#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QByteArray>
#include <QString>

struct MessageHeader {
    quint32 type;        // 消息类型
    quint32 length;      // 消息体长度
    QString sender;     // 发送者ID
    QString receiver;    // 接收者ID
    qint64 timestamp;   // 时间戳
};

enum MessageType {
    MSG_LOGIN_REQ,        // 登录请求
    MSG_LOGIN_RESP_ALLOW, // 允许登录响应
    MSG_LOGIN_RESP_REJECT,// 拒绝登录请求
    MSG_TEXT,             // 文本消息
    MSG_FILE_REQ,         // 文件传输请求
    MSG_FILE_DATA,        // 文件数据块
    MSG_FRIEND_REQ,       // 添加好友请求
    MSG_FRIEND_RESP,      // 添加好友响应
    MSG_FRIEND_LIST_REQ,  // 获取好友列表
    MSG_FRIEND_LIST_RESP, // 好友列表响应
    MSG_STATUS_UPDATE     // 在线状态更新
};

enum NotNeed{
    NOT_NEED_SENDER,	//不需要发送者
    NOT_NEED_RECEIVER,  //不需要接收者
};

struct Message {
    MessageHeader header;
    QByteArray body;
};

#endif // PROTOCOL_H
