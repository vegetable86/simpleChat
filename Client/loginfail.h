#ifndef LOGINFAIL_H
#define LOGINFAIL_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class loginFail;
}

class loginFail : public QWidget
{
    Q_OBJECT

public:
    explicit loginFail(QWidget *parent = nullptr);
    ~loginFail();

private:
    Ui::loginFail *ui;
};

#endif // LOGINFAIL_H
