#include "loginfail.h"
#include "ui_loginfail.h"

loginFail::loginFail(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginFail)
{
    ui->setupUi(this);

    QObject::connect(ui->loginFailButton, &QPushButton::clicked, this, [&](){
        // setAttribute(Qt::WA_DeleteOnClose);
        // close();
        hide();
    });
}

loginFail::~loginFail()
{
    delete ui;
}
