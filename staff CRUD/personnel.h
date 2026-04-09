#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>
#include <QStringList>
#include <QMap>


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
        AccountBlocked,
        SuspiciousActivity,
        DbError
    };
    enum class FaceLoginResult {
        Ok,
        FaceNotRecognized,
        FaceNotEnabled,
        CvNotAccepted,
        AccountBlocked,
        SuspiciousActivity,
        DbError
    };

    struct UserProfile {
        int idPers = -1;
        QString nom;
        QString prenom;
        QString role;
        QByteArray avatar;
    };
    struct AccountProfile {
        int idPers = -1;
        QString nom;
        QString prenom;
        QString adresse;
        QString tel;
        QString mail;
        QString role;
        QString cvStatus;
        QByteArray avatar;
    };
    struct FaceRecord {
        int idPers = -1;
        QString mail;
        QString role;
        QString cvStatus;
        QByteArray faceData;
    };
    struct CvAnalysisInput {
        int idPers = -1;
        QString fullName;
        QString role;
        QString cvStatus;
        QByteArray cv;
    };
    struct EmployeeOfMonth
    {
        int idPers = -1;
        QString fullName;
        QString role;
        QByteArray avatar;
    };
    struct VoiceRecord {
        int idPers = -1;
        QString mail;
        QString role;
        QString cvStatus;
        QByteArray voiceData;
        QString voiceFeatures;
        QString voicePhrase;
    };

    static bool fetchProfileByMail(const QString& mail, UserProfile* out);
    static bool fetchAccountProfileByMail(const QString& mail, AccountProfile* out);
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
    void setMdp(QString Mdp){this->Mdp = Mdp.trimmed().isEmpty() ? "" : Personnel::hashPassword(Mdp);}
    QString getMdp(){return Mdp;}
    void setCvStatus(QString CvStatus){this->CvStatus=CvStatus;}
    QString getCvStatus(){return CvStatus;}
    void setCv(QByteArray Cv){this->Cv=Cv;}
    QByteArray getCv(){return Cv;}
    void setAvatar(QByteArray Avatar){this->Avatar=Avatar;}
    QByteArray getAvatar(){return Avatar;}
    static QString hashPassword(const QString& plain);
    bool ajouterStaff();
    bool modifierStaff(int IdPers);
    bool supprimerStaff(int IdPers);
    QVector<QStringList> getStaffRows(const QString& sortBy = "", const QString& searchText = "");
    static bool verifyPassword(const QString& plain, const QString& storedSaltHash);
    static LoginResult authenticateByMailEx(const QString& mail,const QString& plainPassword,QString* outRole = nullptr,QString* outCvStatus = nullptr);
    static bool findUserByMail(const QString& mail, QString* fullName = nullptr);
    static QString generateResetToken();
    static bool saveResetToken(const QString& mail, const QString& token, int expiryMinutes = 15);
    static bool validateResetToken(const QString& token);
    static bool resetPasswordByToken(const QString& token, const QString& newPlainPassword);
    static QMap<QString, int> getRoleStatistics();
    static QMap<QString, int> getCvStatusStatistics();
    static int getTotalStaffCount();
    static bool updateOwnAccount(int idPers,const QString& nom,const QString& prenom,const QString& adresse,const QString& tel,const QString& mail,const QString& newPlainPassword,const QByteArray& avatarBytes,bool updateAvatar);
    static bool saveFaceIdByMail(const QString& mail, const QByteArray& faceData);
    static bool hasFaceIdRegistered(const QString& mail);
    static bool removeFaceIdByMail(const QString& mail);
    static FaceLoginResult authenticateByFaceId(const QByteArray& capturedFaceData,QString* outMail = nullptr,QString* outRole = nullptr,QString* outCvStatus = nullptr);
    static QVector<FaceRecord> getAllRegisteredFaceIds();
    static bool fetchCvAnalysisInputById(int idPers, CvAnalysisInput* out);
    static bool updateCvStatusById(int idPers, const QString& newStatus);
    static bool resetAuthRiskByMail(const QString& mail, const QString& method);
    static bool registerFailedAuthByMail(const QString& mail, const QString& method, int riskIncrement = 10);
    static bool registerUnknownAuthAttempt(const QString& method);
    static bool isAccountBlockedByMail(const QString& mail);
    static int getRiskScoreByMail(const QString& mail);
    static bool unblockAccountByMail(const QString& mail);
    static bool isBlockExpiredByMail(const QString& mail);
    static bool clearExpiredBlockByMail(const QString& mail);
    static FaceLoginResult authenticateByFaceIdMail(const QString& mail,QString* outMail = nullptr,QString* outRole = nullptr,QString* outCvStatus = nullptr);
    static bool getEmployeeOfMonth(EmployeeOfMonth* out);
    static bool saveVoiceIdByMail(const QString& mail,const QByteArray& voiceData,const QString& voiceFeatures,const QString& phrase);
    static bool hasVoiceIdRegistered(const QString& mail);
    static bool removeVoiceIdByMail(const QString& mail);
    static QVector<VoiceRecord> getAllRegisteredVoiceIds();
    static FaceLoginResult authenticateByVoiceIdMail(const QString& mail,QString* outMail = nullptr,QString* outRole = nullptr,QString* outCvStatus = nullptr);


};

#endif // PERSONNEL_H
