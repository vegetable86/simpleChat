#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QQuickView>
#include <QStringLiteral>
#include <QQmlApplicationEngine>

#include "../common/Protocol.h"
#include "../common/common_src.h"
#include "../common/eventMarco.h"

#include "loginsuccess.h"
#include "loginfail.h"
#include "registerwindow.h"

// 事件分发宏
#define EVENT_DISPATCH_CASE(type, ...) { \
case type: \
emit type##_EMIT(__VA_ARGS__); \
return ; \
}

// 可点击Label
class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickedLabel(QWidget *parent = nullptr);

signals:
    void clicked(void);

protected:
    void mousePressEvent(QMouseEvent *mouseEvent) override;
};

// 客户端界面
class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);

signals:
    // 允许登录
    void loginAllow(void);
    // 拒绝登录
    void loginReject(void);
    // 需要注册用户
    void needRegisterUser(void);
    // 注册用户成功
    void registerSuccess(void);
    // 注册用户失败
    void registerFail(void);


private:
    // 界面的主layout
    QVBoxLayout *mainBox;
    // 存放登录和密码编辑的layout
    QVBoxLayout *box;
    // 存放登录按钮和注册链接的layout
    QHBoxLayout *registerAndLogin;


    QLabel *userNameBlock;
    QLabel *passWordBlock;
    QLabel *socketConnectSuccessSign;
    QTextEdit *userName;
    QTextEdit *passWord;
    QPushButton *loginButton;
    ClickedLabel *registerUser;

    QTcpSocket *socket;

// 界面跳转
private:
    loginSuccess *loginSuccessWindow;
    loginFail *loginFailWindow;
    registerWindow *registerWindows;

// qml界面，登录成功后调用
private:
    QQmlApplicationEngine *userMainQml;

private:
    void eventDispatch(Message message);

public:
    QByteArray sendLoginMessage(QString userName, QString passWord);
};

#endif // CLIENT_H
