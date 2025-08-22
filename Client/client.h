#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>

#include "../common/Protocol.h"
#include "../common/common_src.h"
#include "../common/eventMarco.h"

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);

private:
    QVBoxLayout *box;
    QLabel *userNameBlock;
    QLabel *passWordBlock;
    QLabel *socketConnectSuccessSign;
    QTextEdit *userName;
    QTextEdit *passWord;
    QPushButton *loginButton;

    QTcpSocket *socket;

public:
    QByteArray sendLoginMessage(QString userName, QString passWord);
};

#endif // CLIENT_H
