#ifndef CONNECTION_H
#define CONNECTION_H
<<<<<<< HEAD
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
=======

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

>>>>>>> gestion_clients
class connection
{
public:
    static connection& createInsatance();
    bool createconnect();
<<<<<<< HEAD
private:
    QSqlDatabase db;
    connection();
    ~connection();
    connection(const connection&) = delete;
    connection& operator=(const connection&)=delete;
};

#endif // CONNECTION_H
=======

private:
    QSqlDatabase db;

    connection();
    ~connection();

    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;
};

#endif
>>>>>>> gestion_clients
