#include "client.h"
#include "loginsuccess.h"
#include "loginfail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // main函数中负责链接不同页面跳转之间的信号
    Client *loginWindow = new Client;
    loginSuccess *loginSuccessWindow = new loginSuccess;
    loginFail *loginFailWindow = new loginFail;


    // 发送登录成功信号
    QObject::connect(loginWindow, &Client::loginAllow, loginSuccessWindow, [&](){
        loginSuccessWindow->show();
    });

    // 发送登录失败信号
    QObject::connect(loginWindow, &Client::loginFail, loginFailWindow, [&](){
        loginFailWindow->show();
    });

    loginWindow->show();
    return a.exec();
}
