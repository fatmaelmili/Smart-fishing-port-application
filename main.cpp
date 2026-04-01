#include "bort.h"
#include "connection.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QSqlDatabase::drivers();

    connection& c = connection::createInsatance();
    bool test = c.createconnect();

    qDebug() << QSqlDatabase::database().isOpen();

    if(!test)
        qDebug() << "Database connection failed";

    SignIn w;
    w.show();

    return a.exec();
}
