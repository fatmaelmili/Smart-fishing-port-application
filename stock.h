#ifndef STOCK_H
#define STOCK_H

#include <QString>
#include <QSqlQueryModel>
QSqlQueryModel* afficher();

class Stock
{
private:
    int idStock;
    int quantity;
    QString typePoisson;
    QString etat;

public:
    Stock();
    Stock(int quantity, QString typePoisson, QString etat);

    // Getters
    int getIdStock() const;
    int getQuantity() const;
    QString getTypePoisson() const;
    QString getEtat() const;

    // Setters
    void setQuantity(int q);
    void setTypePoisson(QString type);
    void setEtat(QString etat);

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);
};

#endif
