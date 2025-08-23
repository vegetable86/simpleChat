#include "client.h"
#include "loginsuccess.h"
#include "loginfail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 登录界面
    Client *loginWindow = new Client;
    loginWindow->show();
    return a.exec();
}
