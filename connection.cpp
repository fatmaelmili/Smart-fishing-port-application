#include "connection.h"

connection::connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

connection::~connection()
{
    if(db.isOpen())
        db.close();
}

connection& connection::createInsatance()
{
    static connection instance;
    return instance;
}

bool connection::createconnect()
{
    bool test=false;

    db.setDatabaseName("BORT");
    db.setUserName("sana");
    db.setPassword("lazybatata");

    if(db.open())
        test=true;

    return test;
}
