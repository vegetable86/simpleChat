#include "loginsuccess.h"
#include "ui_loginsuccess.h"

loginSuccess::loginSuccess(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginSuccess)
{
    ui->setupUi(this);

    QObject::connect(ui->loginSuccessConfirm, QPushButton::clicked, this, [=](){
        // setAttribute(Qt::WA_DeleteOnClose);
        // close();
        hide();
    });
}

loginSuccess::~loginSuccess()
{
    delete ui;
}
