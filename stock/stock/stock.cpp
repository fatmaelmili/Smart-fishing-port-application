#include "signin.h"
#include "ui_stock.h"
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    ui->staffmanagementBTN_stock->setProperty("active", true);
    ui->staffmanagementBTN_stock->style()->unpolish(ui->staffmanagementBTN_stock);
    ui->staffmanagementBTN_stock->style()->polish(ui->staffmanagementBTN_stock);
    ui->staffmanagementBTN_stock->update();
}

SignIn::~SignIn()
{
    delete ui;
}





