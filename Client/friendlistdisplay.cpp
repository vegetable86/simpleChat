#include "friendlistdisplay.h"

friendListDisplay::friendListDisplay() {}

friendListDisplay::friendListDisplay(QQmlApplicationEngine *userMainQml){
    userMainQml->rootContext()->setContextProperty("userModel", this);
}

int friendListDisplay::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_friends.size();
}

QVariant friendListDisplay::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= m_friends.size()){
        return QVariant();
    }
    const Friend &f = m_friends[index.row()];
    switch (role) {
    case userNameRole:
        return f.name;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> friendListDisplay::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[userNameRole] = "friendName";
    return roles;
}

void friendListDisplay::addFriend(const Friend &n_friend){
    beginInsertRows(QModelIndex(), m_friends.size(), m_friends.size());
    m_friends.append(n_friend);
    endInsertRows();
}

void friendListDisplay::loadFriendList(Message message, QQmlApplicationEngine *mainWindow){
    QByteArray data = message.body;
    qint32 countByte = data.size();

    // 通过格式 | 长度(2字节) | 信息 | ...

    QDataStream stream(&data, QIODevice::ReadWrite);
    qint32 base = 0;
    while(base < countByte){
        qint16 nameLength = 0;
        stream >> nameLength;
        QByteArray friendName(nameLength, 0);
        stream.readRawData(friendName.data(), nameLength);

        QString t_friendName = QString::fromUtf8(friendName);
        base += 2 + nameLength;
        // 添加进好友列表中
        Friend n_friend = {
                           t_friendName
        };
        this->addFriend(n_friend);
    }

    // 修改mainWindoW
    // mainWindow->rootContext()->setContextProperty("userModel", this);
}
