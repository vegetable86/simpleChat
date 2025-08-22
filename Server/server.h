#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QCoreApplication>
#include <QTcpSocket>

#include "../common/common_src.h"
#include "../common/Protocol.h"

#define EVENT_DISPATCH_CASE(type) { \
    case type: \
        type##_Handler handler(message); \
        break; \
}

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);

private:
    QTcpServer *server;

    void handleClientDate(QTcpSocket *client);
    void eventDispatch(Message message);

private slots:
    void handleNewConnect(QTcpServer *server);

};

#endif // SERVER_H
