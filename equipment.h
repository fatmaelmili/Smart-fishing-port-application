#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QVector>
#include <QStringList>

class equipment
{
private:
    QString name;
    QString type;
    QString state;
    int qty;
    int cap;

public:
    // Constructors
    equipment();
    equipment(QString name, QString type, QString state, int qty, int cap);

    // CRUD operations
    bool ajouter();                 // INSERT
    bool supprimer(QString name);   // DELETE by name
    bool modifier(QString oldName); // UPDATE by name

    // Data retrieval
    static QVector<QStringList> getAll();                  // SELECT *
    static QVector<QStringList> search(const QString &text); // SEARCH
};

#endif // EQUIPMENT_H
