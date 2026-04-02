#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QVector>
#include <QStringList>
class Client
{
private:
    QString type;
    QString datecl;
    float montant;
    QString modepay;
    QString etat;
    QString description;
    QString article;
    int qte;
public:
    Client();
    Client(QString type, QString datecl, float montant,
           QString modepay, QString etat,
           QString description, QString article, int qte);
    bool ajouterClient();
    bool supprimerClient(int id);
    bool modifierClient(int id);
    QVector<QStringList> afficherClients(QString search = "", QString sort = "");
};

#endif // CLIENT_H
