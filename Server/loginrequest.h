#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDataStream>
#include <QIODevice>

#include "../common/Protocol.h"

struct User{
    QString userName;
    QString passWord;
};

class loginRequest
{
public:
    loginRequest();
    loginRequest(Message message);

private:
    User getUser(QByteArray body);
};

#endif // LOGINREQUEST_H
