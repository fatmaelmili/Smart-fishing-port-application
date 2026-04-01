#include "clients.h"
#include "ui_clients.h"
#include "editclientdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

// ================== CONSTRUCTOR ==================
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    loadClients();
}

// ================== DESTRUCTOR ==================
SignIn::~SignIn()
{
    delete ui;
}

// ================== DATA CONSTRUCTOR ==================
SignIn::SignIn(QString type, QString datecl, float montant, QString modepay,
               QString etat, QString description, QString article, int qte)
{
    this->type = type;
    this->datecl = datecl;
    this->montant = montant;
    this->modepay = modepay;
    this->etat = etat;
    this->description = description;
    this->article = article;
    this->qte = qte;
}

// ================== ADD ==================
bool SignIn::ajouterClient()
{
    QSqlQuery q;

    q.prepare(R"(
        INSERT INTO CLIENTS(TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE)
        VALUES(:type, TO_DATE(:datecl,'YYYY-MM-DD'), :montant, :modepay, :etat, :description, :article, :qte)
    )");

    q.bindValue(":type", type);
    q.bindValue(":datecl", datecl);
    q.bindValue(":montant", montant);
    q.bindValue(":modepay", modepay);
    q.bindValue(":etat", etat);
    q.bindValue(":description", description);
    q.bindValue(":article", article);
    q.bindValue(":qte", qte);

    return q.exec();
}

// ================== DELETE ==================
bool SignIn::supprimerClient(int idclients)
{
    QSqlQuery q;

    q.prepare("DELETE FROM CLIENTS WHERE IDCLIENTS = :id");
    q.bindValue(":id", idclients);

    return q.exec();
}

// ================== UPDATE ==================
bool SignIn::modifierClient(int idclients)
{
    QSqlQuery q;

    q.prepare(R"(
        UPDATE CLIENTS
        SET TYPE=:type,
            DATECL=TO_DATE(:datecl,'YYYY-MM-DD'),
            MONTANT=:montant,
            MODEPAY=:modepay,
            ETAT=:etat,
            DESCRIPTION=:description,
            ARTICLE=:article,
            QTE=:qte
        WHERE IDCLIENTS=:id
    )");

    q.bindValue(":type", type);
    q.bindValue(":datecl", datecl);
    q.bindValue(":montant", montant);
    q.bindValue(":modepay", modepay);
    q.bindValue(":etat", etat);
    q.bindValue(":description", description);
    q.bindValue(":article", article);
    q.bindValue(":qte", qte);
    q.bindValue(":id", idclients);

    return q.exec();
}

// ================== FETCH ==================
QVector<QStringList> SignIn::afficherClients()
{
    QVector<QStringList> rows;
    QSqlQuery q;

    q.prepare("SELECT * FROM CLIENTS ORDER BY IDCLIENTS DESC");

    if(!q.exec())
    {
        qDebug() << q.lastError();
        return rows;
    }

    while(q.next())
    {
        QStringList row;
        for(int i = 0; i < 9; i++)
            row << q.value(i).toString();

        rows.push_back(row);
    }

    return rows;
}

// ================== LOAD TABLE ==================
void SignIn::loadClients()
{
    QVector<QStringList> rows = afficherClients();

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

// ================== ADD BUTTON ==================
void SignIn::on_clientaddbtn_clicked()
{
    if(ui->clientnameinput->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Client name is required");
        return;
    }

    type = ui->clientnameinput->text();
    datecl = ui->clientdateinput->date().toString("yyyy-MM-dd");
    article = ui->itemsinput->text();
    qte = ui->quantityinput->value();
    modepay = ui->choosepayment->currentText();
    description = ui->phoneinput->text();

    montant = 0;
    etat = "Paid";

    if(ajouterClient())
    {
        QMessageBox::information(this, "Success", "Client added");
        loadClients();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to add client");
    }
}

// ================== DELETE BUTTON ==================
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

    if(supprimerClient(id))
    {
        QMessageBox::information(this, "Deleted", "Client deleted");
        loadClients();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Delete failed");
    }
}

// ================== UPDATE BUTTON ==================
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

// ================== MISSING UI SLOTS ==================

void SignIn::on_btnForgetmdp_clicked()
{
}

void SignIn::on_backsigninBTN_clicked()
{
}

void SignIn::on_resetbtn_clicked()
{
}

void SignIn::on_signinbtn_clicked()
{
}

void SignIn::on_clientsmanagementBTN_W_clicked()
{
}

void SignIn::on_backtoclientbtn_clicked()
{
}

void SignIn::on_mainpagebtn_clicked()
{
}

void SignIn::on_clientdashboardbtn_clicked()
{
}
