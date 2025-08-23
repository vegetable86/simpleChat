#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QDateTime>
#include <QDataStream>

#include "../common/Protocol.h"
#include "../common/eventMarco.h"
#include "../common/common_src.h"

namespace Ui {
class registerWindow;
}

class registerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit registerWindow(QWidget *parent = nullptr);
    registerWindow(QWidget* parent, QTcpSocket *socket);
    ~registerWindow();

private:
    QTcpSocket *socket;

signals:
    void pushBackButton(void);

private:
    Ui::registerWindow *ui;
};

#endif // REGISTERWINDOW_H
