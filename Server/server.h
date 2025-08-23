#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QDateTime>

#include "../common/common_src.h"
#include "../common/Protocol.h"
#include "../common/eventMarco.h"

#include "loginrequest.h"
#include "registerrequest.h"

#define EVENT_DISPATCH_CASE(type, ...) { \
case type: \
type##_Handler handler(__VA_ARGS__); \
return; \
}

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);

private:
    QTcpServer *server;

    void eventDispatch(Message message, QTcpSocket *client);

private slots:
    void handleNewConnect(QTcpServer *server);

    //标记各种状态和信息
public:
    bool allowLogin;
};

#endif // SERVER_H
