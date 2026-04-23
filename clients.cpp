#include "clients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QCoreApplication>

QMap<QString, QMap<QString, double>> Client::learningData;
QMap<QString, double> Client::fishScores;   // ✅ ADD THIS LINE

Client::Client(){}

Client::Client(QString type, QString datecl, float montant,
               QString modepay, QString etat,
               QString description, QString article, int qte)
{
    this->type = type;
    this->datecl = datecl;
    this->montant = montant;
    this->modepay = modepay;
    this->etat = etat;
    this->description = description;
    this->article = article;
    this->qte = qte;
}
//added this
//====learning lel local ai=======
void Client::loadLearning()
{
    QFile file(QCoreApplication::applicationDirPath() + "/learning.json");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "No learning file yet";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    for(auto key : root.keys())
    {
        QJsonObject inner = root[key].toObject();

        for(auto subKey : inner.keys())
        {
            learningData[key][subKey] = inner[subKey].toDouble();
        }
    }

    file.close();
    qDebug() << "Learning loaded";
}
//added this
//======save the learning======
void Client::saveLearning()
{
    QFile file(QCoreApplication::applicationDirPath() + "/learning.json");

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot create learning.json";
        return;
    }

    QJsonObject root;

    for(auto key : learningData.keys())
    {
        QJsonObject inner;

        for(auto subKey : learningData[key].keys())
        {
            inner[subKey] = learningData[key][subKey];
        }

        root[key] = inner;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    qDebug() << "learning.json saved!";
}


//add 3ammi mo7sen
bool Client::ajouterClient()
{
    QSqlQuery q;

    q.prepare("INSERT INTO CLIENTS(TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE) "
              "VALUES(:type, TO_DATE(:datecl,'YYYY-MM-DD'), :montant, :modepay, :etat, :description, :article, :qte)");

    q.bindValue(":type", type);
    q.bindValue(":datecl", datecl);
    q.bindValue(":montant", montant);
    q.bindValue(":modepay", modepay);
    q.bindValue(":etat", etat);
    q.bindValue(":description", description);
    q.bindValue(":article", article);
    q.bindValue(":qte", qte);

    return q.exec();
}

// delete 3ammi jaballah
bool Client::supprimerClient(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM CLIENTS WHERE IDCLIENTS = :id");
    q.bindValue(":id", id);
    return q.exec();
}

// update 3ammi mo7sen jaballah
bool Client::modifierClient(int id)
{
    QSqlQuery q;

    q.prepare("UPDATE CLIENTS SET TYPE=:type, DATECL=TO_DATE(:datecl,'YYYY-MM-DD'), "
              "MONTANT=:montant, MODEPAY=:modepay, ETAT=:etat, DESCRIPTION=:description, "
              "ARTICLE=:article, QTE=:qte WHERE IDCLIENTS=:id");

    q.bindValue(":type", type);
    q.bindValue(":datecl", datecl);
    q.bindValue(":montant", montant);
    q.bindValue(":modepay", modepay);
    q.bindValue(":etat", etat);
    q.bindValue(":description", description);
    q.bindValue(":article", article);
    q.bindValue(":qte", qte);
    q.bindValue(":id", id);

    return q.exec();
}

// fetch search w sort the big three
QVector<QStringList> Client::afficherClients(QString search, QString sort)
{
    QVector<QStringList> rows;
    QSqlQuery q;

    QString query = "SELECT * FROM CLIENTS";

    if(!search.trimmed().isEmpty())
    {
        QString s = search.trimmed();

        query += " WHERE "
                 "UPPER(TYPE) LIKE '%" + s.toUpper() + "%' OR "
                                 "UPPER(MODEPAY) LIKE '%" + s.toUpper() + "%' OR "
                                 "TO_CHAR(DATECL,'YYYY-MM-DD') LIKE '%" + s + "%' OR "
                       "TO_CHAR(IDCLIENTS) LIKE '%" + s + "%'";
    }

    if(sort == "client's name")
        query += " ORDER BY TYPE ASC";
    else if(sort == "date of birth")
        query += " ORDER BY DATECL ASC";
    else if(sort == "payment type")
        query += " ORDER BY MODEPAY ASC";
    else if(sort == "article")
        query += " ORDER BY ARTICLE ASC";
    else
        query += " ORDER BY IDCLIENTS DESC";

    qDebug() << "FINAL QUERY:" << query;

    if(!q.exec(query))
    {
        qDebug() << "SQL ERROR:" << q.lastError();
        return rows;
    }

    while(q.next())
    {
        QStringList row;
        for(int i = 0; i < 9; i++)
            row << q.value(i).toString();

        rows.push_back(row);
    }

    return rows;
}
//added this
int levenshteinDistance(const QString &s1, const QString &s2)
{
    int len1 = s1.size(), len2 = s2.size();
    QVector<QVector<int>> dp(len1 + 1, QVector<int>(len2 + 1));

    for(int i = 0; i <= len1; i++) dp[i][0] = i;
    for(int j = 0; j <= len2; j++) dp[0][j] = j;

    for(int i = 1; i <= len1; i++)
    {
        for(int j = 1; j <= len2; j++)
        {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;

            dp[i][j] = std::min({
                dp[i-1][j] + 1,
                dp[i][j-1] + 1,
                dp[i-1][j-1] + cost
            });
        }
    }

    return dp[len1][len2];
}
//added this
//===========jannet l3arrafa====================

QList<QPair<QString, double>> Client::predictTop3(int clientId)
{
    QSqlQuery query;
    QList<QPair<QString, double>> results;

    QString clientArticle = "";
    query.prepare("SELECT ARTICLE FROM CLIENTS WHERE IDCLIENTS = :id");
    query.bindValue(":id", clientId);

    if(query.exec() && query.next())
        clientArticle = query.value(0).toString().toLower().trimmed();

    if(clientArticle.isEmpty())
        return results;
    query.exec("SELECT ARTICLE, COUNT(*) as freq FROM CLIENTS GROUP BY ARTICLE");

    QList<QPair<QString, double>> scored;

    while(query.next())
    {
        QString art = query.value(0).toString().toLower().trimmed();
        int freq = query.value(1).toInt();

        if(art == clientArticle)
            continue;

        int dist = levenshteinDistance(clientArticle, art);
        int maxLen = std::max(clientArticle.length(), art.length());
        double similarity = 1.0 - ((double)dist / maxLen);
        double learnedBoost = learningData[clientArticle][art];
        double score = learnedBoost * 20 + similarity * 5 + freq;

        scored.append(qMakePair(art, score));
    }
    std::sort(scored.begin(), scored.end(),
              [](auto &a, auto &b){ return a.second > b.second; });

    double total = 0;
    for(auto &p : scored)
        total += p.second;
    for(int i = 0; i < scored.size() && i < 3; i++)
    {
        double percent = (scored[i].second / total) * 100;

        results.append(qMakePair(scored[i].first, percent));
    }
    for(auto &res : results)
    {
        learningData[clientArticle][res.first] += 1.0;
    }

    saveLearning();

    return results;
}

void Client::loadAI()
{
    QFile file(QCoreApplication::applicationDirPath() + "/ai_learning.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();

    for(auto key : obj.keys())
        fishScores[key] = obj[key].toDouble();

    file.close();
}


void Client::saveAI()
{
    QFile file(QCoreApplication::applicationDirPath() + "/ai_learning.json");

    if(!file.open(QIODevice::WriteOnly))
        return;

    QJsonObject obj;

    for(auto key : fishScores.keys())
        obj[key] = fishScores[key];

    file.write(QJsonDocument(obj).toJson());
    file.close();
}


void Client::updateFishScore(QString fish, double value)
{
    fishScores[fish] += value;
}




