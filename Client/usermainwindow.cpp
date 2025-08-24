#include "usermainwindow.h"

userMainWindow::userMainWindow() {}

userMainWindow::userMainWindow(QTcpSocket *clientSocket, infoUnion *userInfo, QQmlApplicationEngine *userMainQml_t):
    socket(clientSocket),
    Info(userInfo),
    userMainQml(userMainQml_t)
{
    // 进行信息的映射
    QVariantMap infoMap;
    infoMap["userName"] = userInfo->userName;
    // 将用户映射信息放入qml中
    userMainQml->rootContext()->setContextProperty("infoMap", infoMap);

    // 对服务端请求一个获取用户好友列表的消息
    MessageHeader messageHeader = {
        MessageType::MSG_FRIEND_LIST_REQ,
        0,
        userInfo->userName,
        "",
        QDateTime::currentSecsSinceEpoch()
    };
    clientSocket->write(streamMessage(messageHeader, nullptr));
}

