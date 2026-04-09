#include "connection.h"

connection::connection() {
    db = QSqlDatabase::addDatabase("QODBC");
}
connection::~connection(){
    if(db.isOpen())
        db.close();
}
connection& connection::createInsatance(){
    static connection instance;
    return instance;

}
bool connection::createconnect()
{bool test=false;

    db.setDatabaseName("BORT");//inserer le nom de la source de données
    db.setUserName("fatma");//inserer nom de l'utilisateur
    db.setPassword("perlo2005");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
