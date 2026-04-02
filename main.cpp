
#include "bort.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>
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
<<<<<<< HEAD
    connection& c=connection::createInsatance();
    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

=======
    w.show();
>>>>>>> gestion_clients

    return a.exec();
}
