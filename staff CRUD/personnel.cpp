#include "personnel.h"
#include <QString>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QByteArray>
#include <QVariant>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
Personnel::Personnel() {
}
QString Personnel::hashPassword(const QString& plain)
{
    QByteArray salt(16, Qt::Uninitialized);
    for (int i = 0; i < salt.size(); ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::global()->bounded(0, 256));
    }

    QByteArray input = salt + plain.toUtf8();
    QByteArray hash = QCryptographicHash::hash(input, QCryptographicHash::Sha256);

    QString saltB64 = QString::fromLatin1(salt.toBase64());
    QString hashHex = QString::fromLatin1(hash.toHex());

    return saltB64 + ":" + hashHex;
}

Personnel::Personnel(QString Nom,QString Prenom,QString Adresse,QString Tel,QString Mail,QString Role,QString Mdp,QString CvStatus,QByteArray Cv,QByteArray Avatar){
    this->Nom=Nom;
    this->Prenom=Prenom;
    this->Adresse=Adresse;
    this->Tel=Tel;
    this->Mail=Mail;
    this->Role=Role;
    this->Mdp = Personnel::hashPassword(Mdp);
    this->CvStatus=CvStatus;
    this->Cv=Cv;
    this->Avatar=Avatar;

}
bool Personnel::ajouterStaff(){
    QSqlQuery q;
    q.prepare(R"(
        INSERT INTO FATMA.PERSONNEL
        (NOM, PRENOM, ADRESSE, TEL, MAIL, ROLE, MDP, CVSTATUS, CV, AVATAR)
        VALUES
        (:nom, :prenom, :adresse, :tel, :mail, :role, :mdp, :cvstatus, :cv, :avatar)
    )");

    q.bindValue(":nom", Nom);
    q.bindValue(":prenom", Prenom);
    q.bindValue(":adresse", Adresse);
    q.bindValue(":tel", Tel);
    q.bindValue(":mail", Mail);
    q.bindValue(":role", Role);
    q.bindValue(":mdp", Mdp);
    q.bindValue(":cvstatus", CvStatus);
    q.bindValue(":cv", Cv.isEmpty() ? QVariant() : QVariant::fromValue(Cv));
    q.bindValue(":avatar", Avatar.isEmpty() ? QVariant() : QVariant::fromValue(Avatar));

    if (!q.exec()) {

        return false;
    }

    return true;
}

QVector<QStringList> Personnel::getStaffRows()
{
    QVector<QStringList> rows;

    QSqlQuery q;
    q.prepare(R"(
    SELECT
        IDPERS,
        (PRENOM || ' ' || NOM) AS FULLNAME,
        ADRESSE,
        TEL,
        MAIL,
        MDP,
        ROLE,
        CVSTATUS,
        CASE WHEN CV IS NULL THEN 'No' ELSE 'Yes' END AS HAS_CV,
        CASE WHEN AVATAR IS NULL THEN 'No' ELSE 'Yes' END AS HAS_AVATAR
    FROM FATMA.PERSONNEL
    ORDER BY IDPERS DESC
)");

    if (!q.exec()) {
        qDebug() << "getStaffRows error:" << q.lastError().text();
        return rows;
    }

    while (q.next()) {
        QStringList row;
        for (int i = 0; i < 10; ++i)
            row << q.value(i).toString();
        rows.push_back(row);
    }

    return rows;
}
bool Personnel::supprimerStaff(int idPers)
{
    QSqlQuery q;
    q.prepare("DELETE FROM FATMA.PERSONNEL WHERE IDPERS = :id");
    q.bindValue(":id", idPers);

    if (!q.exec()) {
        qDebug() << "supprimerStaff error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Personnel::modifierStaff(int IdPers)
{
    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET NOM      = :nom,
            PRENOM    = :prenom,
            ADRESSE   = :adresse,
            TEL       = :tel,
            MAIL      = :mail,
            ROLE      = :role,
            CVSTATUS  = :cvstatus,
            CV        = :cv,
            AVATAR    = :avatar,
            MDP       = :mdp
        WHERE IDPERS = :id
    )");

    q.bindValue(":nom", Nom);
    q.bindValue(":prenom", Prenom);
    q.bindValue(":adresse", Adresse);
    q.bindValue(":tel", Tel);
    q.bindValue(":mail", Mail);
    q.bindValue(":role", Role);
    q.bindValue(":cvstatus", CvStatus);
    q.bindValue(":cv", Cv.isEmpty() ? QVariant() : QVariant::fromValue(Cv));
    q.bindValue(":avatar", Avatar.isEmpty() ? QVariant() : QVariant::fromValue(Avatar));
    q.bindValue(":mdp", hashPassword(Mdp));
    q.bindValue(":id", IdPers);
    if (!q.exec()) {
        qDebug() << "modifierStaff error:" << q.lastError().text();
        return false;
    }
    return true;
}



