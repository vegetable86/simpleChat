#ifndef FRIENDLISTREQUEST_H
#define FRIENDLISTREQUEST_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDataStream>
#include <QIODevice>
#include <QDataStream>

#include "../common/Protocol.h"
#include "../common/common_src.h"
#include "../common/eventMarco.h"

#include "server.h"

class Server;

class friendListRequest
{
public:
    friendListRequest();
    friendListRequest(Message &message, Server *server, QTcpSocket *client);
};

#endif // FRIENDLISTREQUEST_H
