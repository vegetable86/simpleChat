#include "friendlistrequest.h"

friendListRequest::friendListRequest() {}


friendListRequest::friendListRequest(Message &message, Server *server, QTcpSocket *client){
    QString userName = message.header.sender;
    QSqlQuery query;
    // 使用username查询他相关的所有好友
    query.prepare(R"(SELECT u2.username
                        FROM users u1
                        JOIN friends f ON f.user_id = u1.id AND f.status = 1
                        JOIN users u2 ON u2.id = CASE
                                                    WHEN f.user_id = u1.id THEN f.friend_id
                                                        ELSE f.user_id
                                                END
                        WHERE u1.username = :user;
                    )");
    query.bindValue(":user", userName);
    query.exec();

    // 创建一个二进制流，将好友列表放入二进制流
    // 格式 | 好友名长度 | 好友名 | 长度 | 好友名 | ... | ... | ...
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    int count = 0;
    while(query.next()){
        QByteArray friendName = query.value(0).toString().toUtf8();
        qint16 friendNameLength = friendName.size();
        // qDebug() << "返回" << userName << "好友列表:";
        stream << friendNameLength;
        stream.writeRawData(friendName.constData(), friendNameLength);
    }

    qDebug() << "QByteArray.size(): " << data.size() ;

    MessageHeader messageBack = {
        MessageType::MSG_FRIEND_LIST_RESP,
        (quint32)data.size(),
        "",
        "",
        QDateTime::currentSecsSinceEpoch()
    };
    client->write(streamMessage(messageBack, data));
}
