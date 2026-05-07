#include "stock.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Stock::Stock()
{
    quantity = 0;
    typePoisson = "";
    etat = "";
}

Stock::Stock(int quantity, QString typePoisson, QString etat)
{
    this->quantity = quantity;
    this->typePoisson = typePoisson;
    this->etat = etat;
}

// Getters
int Stock::getIdStock() const { return idStock; }
int Stock::getQuantity() const { return quantity; }
QString Stock::getTypePoisson() const { return typePoisson; }
QString Stock::getEtat() const { return etat; }

// Setters
void Stock::setQuantity(int q) { quantity = q; }
void Stock::setTypePoisson(QString type) { typePoisson = type; }
void Stock::setEtat(QString e) { etat = e; }

// CREATE
bool Stock::ajouter()
{
    QSqlQuery query(QSqlDatabase::database());

    QString sql = "INSERT INTO \"BORT\".\"STOCKS\" (\"QTE\", \"TYPEPOISSON\", \"ETAT\") VALUES ("
                  + QString::number(quantity) + ", '"
                  + typePoisson + "', '"
                  + etat + "')";

    qDebug() << sql;

    if(query.exec(sql))
    {
        qDebug() << "Insert OK";
        return true;
    }
    else
    {
        qDebug() << "Insert ERROR:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Stock::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM BORT.STOCKS");

    model->setHeaderData(0, Qt::Horizontal, "IDStock");
    model->setHeaderData(1, Qt::Horizontal, "Quantity");
    model->setHeaderData(2, Qt::Horizontal, "Name");
    model->setHeaderData(3, Qt::Horizontal, "Status");

    return model;
}

bool Stock::modifier(int id)
{
    QSqlQuery query;

    QString sql = "UPDATE BORT.STOCKS SET "
                  "QTE = :qte, "
                  "TYPEPOISSON = :type, "
                  "ETAT = :etat "
                  "WHERE IDSTOCK = :id";

    query.prepare(sql);

    query.bindValue(":qte", quantity);
    query.bindValue(":type", typePoisson);
    query.bindValue(":etat", etat);
    query.bindValue(":id", id);
    qDebug() << "Update called for ID:" << id;
    if(query.exec())
    {
        qDebug() << "Update OK";
        qDebug() << "Rows affected:" << query.numRowsAffected();

        return query.numRowsAffected() > 0;
    }
    else
    {
        qDebug() << "Update ERROR:" << query.lastError().text();
        return false;
    }

}

bool Stock::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM BORT.STOCKS WHERE IDSTOCK = :id");
    query.bindValue(":id", id);

    if(query.exec())
    {
        qDebug() << "Delete OK";
        return true;
    }
    else
    {
        qDebug() << "Delete ERROR:" << query.lastError().text();
        return false;
    }
}
