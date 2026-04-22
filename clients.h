#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

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
    static QMap<QString, QMap<QString, double>> learningData;
public:
    Client();
    Client(QString type, QString datecl, float montant,
           QString modepay, QString etat,
           QString description, QString article, int qte);
    bool ajouterClient();
    bool supprimerClient(int id);
    bool modifierClient(int id);
    QVector<QStringList> afficherClients(QString search = "", QString sort = "");
    QList<QPair<QString, double>> predictTop3(int clientId);
    static void loadLearning();
    static void saveLearning();
};

#endif
