#include "bort.h"
#include "ui_clients.h"

#include "clients.h"
#include "editclientdialog.h"

#include <QMessageBox>
#include <QDebug>

// ==================constructor goes weeeeee==================
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    loadClients();
}

// ==================destructor goes wooo==================
SignIn::~SignIn()
{
    delete ui;
}

// ==================wiiiii navigation goes brrr==================

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

    ui->resetlabel->setText("Reset link sent.");
}

void SignIn::on_signinbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}

void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}

void SignIn::on_clientdashboardbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backtoclientbtn_clicked()
    {
        ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
    }


void SignIn::on_clientsmanagementBTN_W_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}

// ==================all mo7sen jaballah loads==================

void SignIn::loadClients()
{
    Client C;
    QVector<QStringList> rows = C.afficherClients();

    ui->clienttable->setRowCount(0);

    for(int i = 0; i < rows.size(); i++)
    {
        ui->clienttable->insertRow(i);

        for(int j = 0; j < rows[i].size(); j++)
        {
            ui->clienttable->setItem(i, j, new QTableWidgetItem(rows[i][j]));
        }
    }
}

// =================add a mos7sinon==================

void SignIn::on_clientaddbtn_clicked()
{
    if(ui->clientnameinput->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Client name is required");
        return;
    }

    Client C(
        ui->clientnameinput->text(),
        ui->clientdateinput->date().toString("yyyy-MM-dd"),
        0,
        ui->choosepayment->currentText(),
        "Paid",
        ui->phoneinput->text(),
        ui->itemsinput->text(),
        ui->quantityinput->value()
        );

    if(C.ajouterClient())
    {
        QMessageBox::information(this, "Success", "Client added");
        loadClients();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Add failed");
    }
}

// ==================delete the mo7sinon :c==================

void SignIn::on_deleteclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    int id = ui->clienttable->item(row,0)->text().toInt();

    if(QMessageBox::question(this, "Confirm",
                              "Delete this client?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;

    Client C;

    if(C.supprimerClient(id))
    {
        QMessageBox::information(this, "Deleted", "Client deleted");
        loadClients();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Delete failed");
    }
}

// ==================update the mo7sinon :DD==================

void SignIn::on_updateclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    int id = ui->clienttable->item(row,0)->text().toInt();

    EditClientDialog dialog(this);

    dialog.setClientData(
        ui->clienttable->item(row,1)->text(),
        ui->clienttable->item(row,2)->text(),
        ui->clienttable->item(row,6)->text(),
        ui->clienttable->item(row,7)->text(),
        ui->clienttable->item(row,8)->text().toInt(),
        ui->clienttable->item(row,4)->text(),
        id
        );

    if(dialog.exec() == QDialog::Accepted)
    {
        loadClients();
    }
}
