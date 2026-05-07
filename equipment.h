#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QVector>
#include <QStringList>

class equipment
{
public:
    equipment();
    equipment(QString name, QString type, QString state, int qty, int cap);

    bool ajouter();
    bool supprimer(QString name);
    bool modifier(QString oldName);

    static QVector<QStringList> getAll();
    static QVector<QStringList> search(const QString &text);

    // Getters
    QString getName()  const { return name;  }
    QString getType()  const { return type;  }
    QString getState() const { return state; }
    int     getQty()   const { return qty;   }
    int     getCap()   const { return cap;   }

    // Setters
    void setName (const QString &v) { name  = v; }
    void setType (const QString &v) { type  = v; }
    void setState(const QString &v) { state = v; }
    void setQty  (int v)            { qty   = v; }
    void setCap  (int v)            { cap   = v; }

private:
    QString name;
    QString type;
    QString state;
    int     qty = 0;
    int     cap = 0;
};

#endif // EQUIPMENT_H
