#include "bort.h"
#include "connection.h"
#include "clients.h"   // 🔥 ADD THIS

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection& c = connection::createInsatance();
    bool test = c.createconnect();

    if(!test)
        qDebug() << "Database connection failed";

    // 🔥 LOAD AI MEMORY
    Client::loadLearning();

    SignIn w;
    w.show();

    return a.exec();
}
