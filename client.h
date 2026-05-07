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
    static QMap<QString, QMap<QString, double>> learningData;//added this
public:
    Client();
    Client(QString type, QString datecl, float montant,
           QString modepay, QString etat,
           QString description, QString article, int qte);
    bool ajouterClient();
    bool supprimerClient(int id);
    bool modifierClient(int id);
    QVector<QStringList> afficherClients(QString search = "", QString sort = "");
    QList<QPair<QString, double>> predictTop3(int clientId);//added this
    static void loadLearning();//added this
    static void saveLearning();//added this
    static QMap<QString, double> fishScores;

    static void loadAI();
    static void saveAI();
    static void updateFishScore(QString fish, double value);
};

#endif
