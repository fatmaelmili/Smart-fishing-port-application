#include "equipment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// ─────────────────────────────────────────────
// Constructors
// ─────────────────────────────────────────────

equipment::equipment() {}

equipment::equipment(QString name, QString type, QString state, int qty, int cap)
{
    this->name = name;
    this->type = type;
    this->state = state;
    this->qty = qty;
    this->cap = cap;
}

// ─────────────────────────────────────────────
// ADD
// ─────────────────────────────────────────────

bool equipment::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO EQUIPEMENTS (NOMEQ, TYPEEQ, ETAT, QTE, CAPACITE) "
              "VALUES (:n, :t, :e, :q, :c)");

    q.bindValue(":n", name);
    q.bindValue(":t", type);
    q.bindValue(":e", state);
    q.bindValue(":q", qty);
    q.bindValue(":c", cap);

    if (!q.exec()) {
        qDebug() << "INSERT ERROR:" << q.lastError().text();
        return false;
    }

    return true;
}

// ─────────────────────────────────────────────
// DELETE
// ─────────────────────────────────────────────

bool equipment::supprimer(QString name)
{
    QSqlQuery q;
    q.prepare("DELETE FROM EQUIPEMENTS WHERE NOMEQ = :n");
    q.bindValue(":n", name);

    if (!q.exec()) {
        qDebug() << "DELETE ERROR:" << q.lastError().text();
        return false;
    }

    return true;
}

// ─────────────────────────────────────────────
// UPDATE
// ─────────────────────────────────────────────

bool equipment::modifier(QString oldName)
{
    QSqlQuery q;
    q.prepare("UPDATE EQUIPEMENTS SET "
              "NOMEQ = :n, TYPEEQ = :t, ETAT = :e, QTE = :q, CAPACITE = :c "
              "WHERE NOMEQ = :old");

    q.bindValue(":n", name);
    q.bindValue(":t", type);
    q.bindValue(":e", state);
    q.bindValue(":q", qty);
    q.bindValue(":c", cap);
    q.bindValue(":old", oldName);

    if (!q.exec()) {
        qDebug() << "UPDATE ERROR:" << q.lastError().text();
        return false;
    }

    return true;
}

// ─────────────────────────────────────────────
// GET ALL
// ─────────────────────────────────────────────

QVector<QStringList> equipment::getAll()
{
    QVector<QStringList> rows;

    QSqlQuery q;
    if (!q.exec("SELECT NOMEQ, TYPEEQ, ETAT, QTE, CAPACITE FROM EQUIPEMENTS")) {
        qDebug() << "SELECT ERROR:" << q.lastError().text();
        return rows;
    }

    while (q.next()) {
        QStringList row;
        for (int i = 0; i < 5; i++)
            row << q.value(i).toString();

        rows.push_back(row);
    }

    return rows;
}

// ─────────────────────────────────────────────
// SEARCH
// ─────────────────────────────────────────────

QVector<QStringList> equipment::search(const QString &text)
{
    QVector<QStringList> rows;

    QSqlQuery q;
    q.prepare("SELECT NOMEQ, TYPEEQ, ETAT, QTE, CAPACITE FROM EQUIPEMENTS "
              "WHERE LOWER(NOMEQ) LIKE LOWER(:s) "
              "OR LOWER(TYPEEQ) LIKE LOWER(:s) "
              "OR LOWER(ETAT) LIKE LOWER(:s)");

    q.bindValue(":s", "%" + text + "%");

    if (!q.exec()) {
        qDebug() << "SEARCH ERROR:" << q.lastError().text();
        return rows;
    }

    while (q.next()) {
        QStringList row;
        for (int i = 0; i < 5; i++)
            row << q.value(i).toString();

        rows.push_back(row);
    }

    return rows;
}
