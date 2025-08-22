#ifndef LOGINSUCCESS_H
#define LOGINSUCCESS_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class loginSuccess;
}

class loginSuccess : public QWidget
{
    Q_OBJECT

public:
    explicit loginSuccess(QWidget *parent = nullptr);
    ~loginSuccess();

private:
    Ui::loginSuccess *ui;
};

#endif // LOGINSUCCESS_H
