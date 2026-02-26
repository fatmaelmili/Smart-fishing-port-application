#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class connection
{
public:
    static connection& createInsatance();
    bool createconnect();
private:
    QSqlDatabase db;
    connection();
    ~connection();
    connection(const connection&) = delete;
    connection& operator=(const connection&)=delete;
};

#endif // CONNECTION_H
