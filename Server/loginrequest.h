#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDataStream>
#include <QIODevice>

#include "../common/Protocol.h"
#include "../common/common_src.h"

#include "server.h"

class Server;

class loginRequest
{
public:
    loginRequest();
    loginRequest(Message &message, Server *server, QTcpSocket *client);

public:

};

#endif // LOGINREQUEST_H
