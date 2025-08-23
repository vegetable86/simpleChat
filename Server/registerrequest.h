#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include <QTcpSocket>

#include "server.h"

#include "../common/common_src.h"
#include "../common/Protocol.h"

class Server;

class registerRequest
{
public:
    registerRequest();
    registerRequest(Message &message, Server *server, QTcpSocket *client);
};

#endif // REGISTERREQUEST_H
