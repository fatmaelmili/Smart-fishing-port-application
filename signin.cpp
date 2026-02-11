#include "signin.h"
#include "ui_signin.h"
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    ui->staffmanagementBTN->setProperty("active", true);
    ui->staffmanagementBTN->style()->unpolish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->style()->polish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->update();
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


void SignIn::on_staffmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}




void SignIn::on_backstfbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_backWbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_staticbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backWbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);

}


void SignIn::on_staticbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_modifystaffbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdate);

}


void SignIn::on_logOutBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backWbtn_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_userprofiledetails_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}




void SignIn::on_userprofiledetails_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_staffmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}

