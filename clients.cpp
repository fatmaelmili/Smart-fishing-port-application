#include "clients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Client::Client(){}

Client::Client(QString type, QString datecl, float montant,
               QString modepay, QString etat,
               QString description, QString article, int qte)
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

//add 3ammi mo7sen
bool Client::ajouterClient()
{
    QSqlQuery q;

    q.prepare("INSERT INTO CLIENTS(TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE) "
              "VALUES(:type, TO_DATE(:datecl,'YYYY-MM-DD'), :montant, :modepay, :etat, :description, :article, :qte)");

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

// delete 3ammi jaballah
bool Client::supprimerClient(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM CLIENTS WHERE IDCLIENTS = :id");
    q.bindValue(":id", id);
    return q.exec();
}

// update 3ammi mo7sen jaballah
bool Client::modifierClient(int id)
{
    QSqlQuery q;

    q.prepare("UPDATE CLIENTS SET TYPE=:type, DATECL=TO_DATE(:datecl,'YYYY-MM-DD'), "
              "MONTANT=:montant, MODEPAY=:modepay, ETAT=:etat, DESCRIPTION=:description, "
              "ARTICLE=:article, QTE=:qte WHERE IDCLIENTS=:id");

    q.bindValue(":type", type);
    q.bindValue(":datecl", datecl);
    q.bindValue(":montant", montant);
    q.bindValue(":modepay", modepay);
    q.bindValue(":etat", etat);
    q.bindValue(":description", description);
    q.bindValue(":article", article);
    q.bindValue(":qte", qte);
    q.bindValue(":id", id);

    return q.exec();
}

// fetching eyy baba
QVector<QStringList> Client::afficherClients()
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
