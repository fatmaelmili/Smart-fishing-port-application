#include "clients.h"
#include "ui_clients.h"

#include <QStyle>
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    loadClients();
    ui->clientsmanagementBTN->setProperty("active", true);
    ui->clientsmanagementBTN->style()->unpolish(ui->clientsmanagementBTN);
    ui->clientsmanagementBTN->style()->polish(ui->clientsmanagementBTN);
    ui->clientsmanagementBTN->update();
}

SignIn::~SignIn()
{
    delete ui;
}


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

    if(!q.exec())
    {
        qDebug() << q.lastError();
        return false;
    }

    return true;
}



bool SignIn::supprimerClient(int idclients)
{
    QSqlQuery q;

    q.prepare("DELETE FROM CLIENTS WHERE IDCLIENTS = :id");
    q.bindValue(":id", idclients);

    if(!q.exec())
    {
        qDebug() << "Delete error:" << q.lastError();
        return false;
    }

    qDebug() << "Delete success";
    return true;
}


bool SignIn::modifierClient(int idclients)
{
    QSqlQuery q;

    q.prepare(R"(
        UPDATE SANA.CLIENTS
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



QVector<QStringList> SignIn::afficherClients()
{
    QVector<QStringList> rows;

    QSqlQuery q;

    q.prepare(R"(
        SELECT IDCLIENTS, TYPE, DATECL, MONTANT, MODEPAY,
               ETAT, DESCRIPTION, ARTICLE, QTE
        FROM SANA.CLIENTS
        ORDER BY IDCLIENTS DESC
    )");

    if(!q.exec()){
        qDebug() << q.lastError();
        return rows;
    }

    while(q.next()){
        QStringList row;

        for(int i=0;i<9;i++)
            row << q.value(i).toString();

        rows.push_back(row);
    }

    return rows;
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

void SignIn::on_clientaddbtn_clicked()
{
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
        qDebug() << "Client added";

        loadClients();

        ui->clientnameinput->clear();
        ui->phoneinput->clear();
        ui->itemsinput->clear();
        ui->quantityinput->setValue(0);
    }
}

void SignIn::on_deleteclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row < 0)
    {
        qDebug() << "No row selected";
        return;
    }

    QTableWidgetItem *item = ui->clienttable->item(row,0);

    if(!item)
    {
        qDebug() << "ID cell empty";
        return;
    }

    int id = item->text().toInt();

    qDebug() << "Deleting client ID:" << id;

    bool ok = supprimerClient(id);

    if(ok)
    {
        qDebug() << "Client deleted";
        loadClients();
    }
}

void SignIn::on_updateclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
        return;

    int id = ui->clienttable->item(row,0)->text().toInt();

    QString clientname = ui->clientnameinput->text();
    QString datecl = ui->clientdateinput->date().toString("yyyy-MM-dd");
    QString phone = ui->phoneinput->text();
    QString article = ui->itemsinput->text();
    int qte = ui->quantityinput->value();
    QString modepay = ui->choosepayment->currentText();

    float montant = 0;
    QString etat = "Paid";
    QString description = phone;

    SignIn C(clientname,datecl,montant,modepay,etat,description,article,qte);

    bool test = C.modifierClient(id);

    if(test)
        qDebug()<<"Client updated";
}

void SignIn::loadClients()
{
    QVector<QStringList> rows = afficherClients();

    ui->clienttable->clearContents();
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
