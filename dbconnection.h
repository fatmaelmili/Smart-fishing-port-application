#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

class DBConnection {
public:
    static bool connect(const QString& user,
                        const QString& password,
                        const QString& host     = "localhost",
                        const QString& sid      = "XE",
                        int            port     = 1521)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

        // Oracle ODBC connection string — no DSN needed
        QString connStr = QString(
                              "Driver={Oracle in XE};"
                              "DBQ=%1:%2/%3;"
                              "Uid=%4;"
                              "Pwd=%5;"
                              ).arg(host).arg(port).arg(sid).arg(user).arg(password);

        db.setDatabaseName(connStr);

        if (!db.open()) {
            qDebug() << "[DBConnection] Connexion échouée:" << db.lastError().text();
            return false;
        }

        qDebug() << "[DBConnection] Connexion Oracle via ODBC réussie.";
        return true;
    }

    static void disconnect() {
        QSqlDatabase::database().close();
    }
};

#endif // DBCONNECTION_H
