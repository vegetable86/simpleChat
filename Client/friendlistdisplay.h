#ifndef FRIENDLISTDISPLAY_H
#define FRIENDLISTDISPLAY_H

#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>
#include <QDataStream>
#include <QAbstractListModel>

#include "../common/common_src.h"
#include "../common/Protocol.h"
#include "../common/eventMarco.h"

struct Friend{
    QString name;
    // ...
};

class friendListDisplay : public QAbstractListModel
{
    Q_OBJECT

public:
    enum friendRoles {
        userNameRole = Qt::UserRole + 1,
        // ...
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addFriend(const Friend &n_friend);

    friendListDisplay();
    friendListDisplay(QQmlApplicationEngine *userMainQml);

    // 加载好友列表
    void loadFriendList(Message message, QQmlApplicationEngine *mainWindow);

private:
    QVector<Friend> m_friends;
};

#endif // FRIENDLISTDISPLAY_H
