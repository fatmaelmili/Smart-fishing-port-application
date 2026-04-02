#include "signin.h"
#include "dbconnection.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();

    bool ok = DBConnection::connect(
        "nour",
        "sunny2024",
        "localhost",
        "XE",
        1521
        );

    if (ok) {
        QMessageBox::information(nullptr, "Base de données",
                                 "✅ Connexion Oracle réussie !");
    } else {
        QMessageBox::critical(nullptr, "Base de données",
                              "❌ Connexion Oracle échouée.");
    }

    SignIn w;
    w.show();

    int result = a.exec();
    DBConnection::disconnect();
    return result;
}
