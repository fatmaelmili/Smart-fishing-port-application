#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>
#include <QStringList>


class Personnel
{
private:
    int IdPers;
    QString Nom;
    QString Prenom;
    QString Adresse;
    QString Tel;
    QString Mail;
    QString Role;
    QString Mdp;
    QString CvStatus;
    QByteArray Cv;
    QByteArray Avatar;
public:
    enum class LoginResult {
        Ok,
        UserNotFound,
        WrongPassword,
        CvNotAccepted,
        DbError
    };
    Personnel();
    Personnel(QString Nom,QString Prenom,QString Adresse,QString Tel,QString Mail,QString Role,QString Mdp,QString CvStatus,QByteArray Cv,QByteArray Avatar);
    void setIdPers(int IdPers){this->IdPers=IdPers;}
    int getIdPers(){return IdPers;}
    void setNom(QString Nom){this->Nom=Nom;}
    QString getNom(){return Nom;}
    void setPrenom(QString Prenom){this->Prenom=Prenom;}
    QString getPrenom(){return Prenom ;}
    void setAdresse(QString Adresse){this->Adresse=Adresse;}
    QString getAdresse(){return Adresse;}
    void setTel(QString Tel){this->Tel=Tel;}
    QString getTel(){return Tel;}
    void setMail(QString Mail){this->Mail=Mail;}
    QString getMail(){return Mail;}
    void setRole(QString Role){this->Role=Role;}
    QString getRole(){ return Role;}
    void setMdp(QString Mdp){this->Mdp = Personnel::hashPassword(Mdp);}
    QString getMdp(){return Mdp;}
    void setCvStatus(QString CvStatus){this->CvStatus=CvStatus;}
    QString getCvStatus(){return CvStatus;}
    void setCv(QByteArray Cv){this->Cv=Cv;}
    QByteArray getCv(){return Cv;}
    void setAvatar(QByteArray Avatar){this->Avatar=Avatar;}
    QByteArray getAvatar(){return Avatar;}
    QString hashPassword(const QString& plain);
    bool ajouterStaff();
    bool modifierStaff(int IdPers);
    bool supprimerStaff(int IdPers);
    QVector<QStringList> getStaffRows();
    static bool verifyPassword(const QString& plain, const QString& storedSaltHash);
    static LoginResult authenticateByMailEx(const QString& mail,const QString& plainPassword,QString* outRole = nullptr,QString* outCvStatus = nullptr);


};

#endif // PERSONNEL_H
