#include "clients.h"
#include "ui_clients.h"
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    ui->clientsmanagementBTN->setProperty("active", true);
    ui->clientsmanagementBTN->style()->unpolish(ui->clientsmanagementBTN);
    ui->clientsmanagementBTN->style()->polish(ui->clientsmanagementBTN);
    ui->clientsmanagementBTN->update();
}

SignIn::~SignIn()
{
    delete ui;
}




void SignIn::on_btnForgetmdp_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageForgetpass);
}


void SignIn::on_backsigninBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_resetbtn_clicked()
{

        QString input = ui->resetlineEdit->text().trimmed();

        if (input.isEmpty()) {
            ui->resetlabel->setText("Please enter your email or username.");
            return;
        }

        ui->resetlabel->setText("Reset link sent. Check your email.");


}


void SignIn::on_ubploacvbtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select a CV",
        QDir::homePath(),
        "CV (*.pdf *.doc *.docx);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    // Afficher le chemin du fichier dans le champ
    //ui->cvpathEdit->setText(filePath);
    ui->cvpathEdit->setText(QFileInfo(filePath).fileName());

}


void SignIn::on_signinbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_clientsmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}




void SignIn::on_backtoclientbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_clientdashboardbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}

