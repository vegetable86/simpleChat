#include "server.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("qq");
    db.setUserName("root");
    db.setPassword("12345678");
    db.open();

    // 服务器类
    Server w;
    w.show();
    return a.exec();
}
