#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QCoreApplication>
#include <QTcpSocket>

#include "../common/common_src.h"
#include "../common/Protocol.h"
#include "../common/eventMarco.h"

#include "loginrequest.h"

#define EVENT_DISPATCH_CASE(type, m) { \
case type: \
type##_Handler handler(m); \
break; \
}

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);

private:
    QTcpServer *server;

    void eventDispatch(Message message);

private slots:
    void handleNewConnect(QTcpServer *server);

};

#endif // SERVER_H
