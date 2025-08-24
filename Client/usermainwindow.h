#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>

#include "friendlistdisplay.h"

#include "../common/common_src.h"
#include "../common/Protocol.h"
#include "../common/eventMarco.h"

class userMainWindow : public QObject
{
    Q_OBJECT
public:
    userMainWindow();
    userMainWindow(QTcpSocket *clientSocket, infoUnion *userInfo, QQmlApplicationEngine *userMainQml);

private:
    QTcpSocket *socket;
    infoUnion *Info;


    QQmlApplicationEngine *userMainQml;

};

#endif // USERMAINWINDOW_H
