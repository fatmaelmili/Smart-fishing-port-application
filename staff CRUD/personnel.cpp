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
#include <QDateTime>
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
    this->Mdp = Mdp.trimmed().isEmpty() ? "" : Personnel::hashPassword(Mdp);
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

QVector<QStringList> Personnel::getStaffRows(const QString& sortBy, const QString& searchText)
{
    QVector<QStringList> rows;

    QString orderBy = "IDPERS DESC";

    if (sortBy == "Staff Full Name") {
        orderBy = "UPPER(PRENOM), UPPER(NOM)";
    }
    else if (sortBy == "Staff Role") {
        orderBy = "UPPER(ROLE)";
    }
    else if (sortBy == "Staff CvStatus") {
        orderBy = "UPPER(CVSTATUS)";
    }

    QString queryStr = R"(
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
    )";

    if (!searchText.trimmed().isEmpty()) {
        queryStr += R"(
            WHERE UPPER(PRENOM || ' ' || NOM) LIKE UPPER(:search)
               OR UPPER(ROLE) LIKE UPPER(:search)
               OR UPPER(CVSTATUS) LIKE UPPER(:search)
        )";
    }

    queryStr += " ORDER BY " + orderBy;

    QSqlQuery q;
    q.prepare(queryStr);

    if (!searchText.trimmed().isEmpty()) {
        q.bindValue(":search", "%" + searchText.trimmed() + "%");
    }

    if (!q.exec()) {
        qDebug() << "getStaffRows error:" << q.lastError().text();
        return rows;
    }

    while (q.next()) {
        QStringList row;
        for (int i = 0; i < 10; ++i) {
            row << q.value(i).toString();
        }
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
    QString queryStr = R"(
        UPDATE FATMA.PERSONNEL
        SET NOM = :nom,
            PRENOM = :prenom,
            ADRESSE = :adresse,
            TEL = :tel,
            MAIL = :mail,
            ROLE = :role,
            CVSTATUS = :cvstatus
    )";

    const bool updatePassword = !Mdp.trimmed().isEmpty();
    const bool updateCv = !Cv.isEmpty();
    const bool updateAvatar = !Avatar.isEmpty();

    if (updatePassword) {
        queryStr += ", MDP = :mdp";
    }

    if (updateCv) {
        queryStr += ", CV = :cv";
    }

    if (updateAvatar) {
        queryStr += ", AVATAR = :avatar";
    }

    queryStr += " WHERE IDPERS = :id";

    QSqlQuery q;
    q.prepare(queryStr);

    q.bindValue(":nom", Nom);
    q.bindValue(":prenom", Prenom);
    q.bindValue(":adresse", Adresse);
    q.bindValue(":tel", Tel);
    q.bindValue(":mail", Mail);
    q.bindValue(":role", Role);
    q.bindValue(":cvstatus", CvStatus);
    q.bindValue(":id", IdPers);

    if (updatePassword) {
        q.bindValue(":mdp", Mdp);
    }

    if (updateCv) {
        q.bindValue(":cv", QVariant::fromValue(Cv));
    }

    if (updateAvatar) {
        q.bindValue(":avatar", QVariant::fromValue(Avatar));
    }

    if (!q.exec()) {
        qDebug() << "modifierStaff error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}
bool Personnel::verifyPassword(const QString& plain, const QString& storedSaltHash)
{
    const QStringList parts = storedSaltHash.split(':');
    if (parts.size() != 2) return false;
    const QByteArray salt = QByteArray::fromBase64(parts[0].toLatin1());
    const QByteArray storedHashHex = parts[1].toLatin1().toLower();
    const QByteArray input = salt + plain.toUtf8();
    const QByteArray computedHashHex =QCryptographicHash::hash(input, QCryptographicHash::Sha256).toHex().toLower();
    return computedHashHex == storedHashHex;
}

Personnel::LoginResult Personnel::authenticateByMailEx(const QString& mail,
                                                       const QString& plainPassword,
                                                       QString* outRole,
                                                       QString* outCvStatus)
{
    QSqlQuery q;
    q.prepare(R"(
        SELECT MDP, ROLE, CVSTATUS, NVL(ACCOUNT_STATUS, 'ACTIVE')
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "Auth DB error:" << q.lastError().text();
        return LoginResult::DbError;
    }

    if (!q.next()) {
        registerUnknownAuthAttempt("CLASSIC");
        return LoginResult::UserNotFound;
    }

    const QString stored        = q.value(0).toString();
    const QString role          = q.value(1).toString();
    const QString cvStatus      = q.value(2).toString();
    const QString accountStatus = q.value(3).toString();

    if (outRole) *outRole = role;
    if (outCvStatus) *outCvStatus = cvStatus;

    if (accountStatus.trimmed().compare("BLOCKED", Qt::CaseInsensitive) == 0) {
        if (isBlockExpiredByMail(mail)) {
            clearExpiredBlockByMail(mail);
        } else {
            return LoginResult::AccountBlocked;
        }
    }

    if (!verifyPassword(plainPassword, stored)) {
        registerFailedAuthByMail(mail, "CLASSIC", 10);

        if (isAccountBlockedByMail(mail)) {
            return LoginResult::AccountBlocked;
        }

        if (getRiskScoreByMail(mail) >= 60) {
            return LoginResult::SuspiciousActivity;
        }

        return LoginResult::WrongPassword;
    }

    if (cvStatus.trimmed().compare("Accepted", Qt::CaseInsensitive) != 0) {
        resetAuthRiskByMail(mail, "CLASSIC");
        return LoginResult::CvNotAccepted;
    }

    resetAuthRiskByMail(mail, "CLASSIC");

    return LoginResult::Ok;
}
bool Personnel::fetchProfileByMail(const QString& mail, UserProfile* out)
{
    if (!out) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT IDPERS, NOM, PRENOM, ROLE, AVATAR
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail);

    if (!q.exec()) {
        qDebug() << "fetchProfileByMail error:" << q.lastError().text();
        return false;
    }
    if (!q.next()) return false;

    out->idPers  = q.value(0).toInt();
    out->nom     = q.value(1).toString();
    out->prenom  = q.value(2).toString();
    out->role    = q.value(3).toString();
    out->avatar  = q.value(4).toByteArray();
    return true;
}


bool Personnel::findUserByMail(const QString& mail, QString* fullName)
{
    QSqlQuery q;
    q.prepare(R"(
        SELECT PRENOM, NOM
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail);

    if (!q.exec()) {
        qDebug() << "findUserByMail error:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        return false;
    }

    if (fullName) {
        *fullName = (q.value(0).toString() + " " + q.value(1).toString()).trimmed();
    }

    return true;
}


QString Personnel::generateResetToken()
{
    QByteArray randomBytes(32, Qt::Uninitialized);
    for (int i = 0; i < randomBytes.size(); ++i) {
        randomBytes[i] = static_cast<char>(QRandomGenerator::global()->bounded(0, 256));
    }

    return QString::fromLatin1(randomBytes.toHex());
}

bool Personnel::saveResetToken(const QString& mail, const QString& token, int expiryMinutes)
{
    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET RESET_TOKEN = :token,
            RESET_TOKEN_EXPIRY = :expiry
        WHERE MAIL = :mail
    )");

    q.bindValue(":token", token);
    q.bindValue(":expiry", QDateTime::currentDateTime().addSecs(expiryMinutes * 60));
    q.bindValue(":mail", mail);

    if (!q.exec()) {
        qDebug() << "saveResetToken error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}

bool Personnel::validateResetToken(const QString& token)
{
    QSqlQuery q;
    q.prepare(R"(
        SELECT COUNT(*)
        FROM FATMA.PERSONNEL
        WHERE RESET_TOKEN = :token
          AND RESET_TOKEN_EXPIRY IS NOT NULL
          AND RESET_TOKEN_EXPIRY >= :now_value
    )");

    q.bindValue(":token", token);
    q.bindValue(":now_value", QDateTime::currentDateTime());

    if (!q.exec()) {
        qDebug() << "validateResetToken error:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        return false;
    }

    return q.value(0).toInt() > 0;
}
bool Personnel::resetPasswordByToken(const QString& token, const QString& newPlainPassword)
{
    if (newPlainPassword.trimmed().isEmpty()) {
        return false;
    }

    if (!validateResetToken(token)) {
        return false;
    }

    const QString newHashedPassword = Personnel::hashPassword(newPlainPassword);

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET MDP = :mdp,
            RESET_TOKEN = NULL,
            RESET_TOKEN_EXPIRY = NULL
        WHERE RESET_TOKEN = :token
          AND RESET_TOKEN_EXPIRY >= :now_value
    )");

    q.bindValue(":mdp", newHashedPassword);
    q.bindValue(":token", token);
    q.bindValue(":now_value", QDateTime::currentDateTime());

    if (!q.exec()) {
        qDebug() << "resetPasswordByToken error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}

QMap<QString, int> Personnel::getRoleStatistics()
{
    QMap<QString, int> stats;
    QSqlQuery q;

    q.prepare(R"(
        SELECT NVL(TRIM(ROLE), 'Unknown') AS ROLE_NAME, COUNT(*)
        FROM FATMA.PERSONNEL
        WHERE UPPER(TRIM(CVSTATUS)) = 'ACCEPTED'
        GROUP BY NVL(TRIM(ROLE), 'Unknown')
        ORDER BY ROLE_NAME
    )");

    if (!q.exec()) {
        qDebug() << "getRoleStatistics error:" << q.lastError().text();
        return stats;
    }

    while (q.next()) {
        stats.insert(q.value(0).toString(), q.value(1).toInt());
    }

    return stats;
}

QMap<QString, int> Personnel::getCvStatusStatistics()
{
    QMap<QString, int> stats;
    QSqlQuery q;

    q.prepare(R"(
        SELECT NVL(TRIM(CVSTATUS), 'Unknown') AS STATUS_NAME, COUNT(*)
        FROM FATMA.PERSONNEL
        GROUP BY NVL(TRIM(CVSTATUS), 'Unknown')
        ORDER BY STATUS_NAME
    )");

    if (!q.exec()) {
        qDebug() << "getCvStatusStatistics error:" << q.lastError().text();
        return stats;
    }

    while (q.next()) {
        stats.insert(q.value(0).toString(), q.value(1).toInt());
    }

    return stats;
}

int Personnel::getTotalStaffCount()
{
    QSqlQuery q;
    q.prepare(R"(
        SELECT COUNT(*)
        FROM FATMA.PERSONNEL
        WHERE UPPER(TRIM(CVSTATUS)) = 'ACCEPTED'
    )");

    if (!q.exec()) {
        qDebug() << "getTotalStaffCount error:" << q.lastError().text();
        return 0;
    }

    if (q.next()) {
        return q.value(0).toInt();
    }

    return 0;
}
bool Personnel::fetchAccountProfileByMail(const QString& mail, AccountProfile* out)
{
    if (!out) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT IDPERS, NOM, PRENOM, ADRESSE, TEL, MAIL, ROLE, CVSTATUS, AVATAR
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail);

    if (!q.exec()) {
        qDebug() << "fetchAccountProfileByMail error:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        return false;
    }

    out->idPers   = q.value(0).toInt();
    out->nom      = q.value(1).toString();
    out->prenom   = q.value(2).toString();
    out->adresse  = q.value(3).toString();
    out->tel      = q.value(4).toString();
    out->mail     = q.value(5).toString();
    out->role     = q.value(6).toString();
    out->cvStatus = q.value(7).toString();
    out->avatar   = q.value(8).toByteArray();

    return true;
}

bool Personnel::updateOwnAccount(int idPers,
                                 const QString& nom,
                                 const QString& prenom,
                                 const QString& adresse,
                                 const QString& tel,
                                 const QString& mail,
                                 const QString& newPlainPassword,
                                 const QByteArray& avatarBytes,
                                 bool updateAvatar)
{
    QString queryStr = R"(
        UPDATE FATMA.PERSONNEL
        SET NOM = :nom,
            PRENOM = :prenom,
            ADRESSE = :adresse,
            TEL = :tel,
            MAIL = :mail
    )";

    const bool updatePassword = !newPlainPassword.trimmed().isEmpty();

    if (updatePassword) {
        queryStr += ", MDP = :mdp";
    }

    if (updateAvatar) {
        queryStr += ", AVATAR = :avatar";
    }

    queryStr += " WHERE IDPERS = :id";

    QSqlQuery q;
    q.prepare(queryStr);

    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":adresse", adresse);
    q.bindValue(":tel", tel);
    q.bindValue(":mail", mail);
    q.bindValue(":id", idPers);

    if (updatePassword) {
        q.bindValue(":mdp", Personnel::hashPassword(newPlainPassword));
    }

    if (updateAvatar) {
        q.bindValue(":avatar", avatarBytes.isEmpty() ? QVariant() : QVariant::fromValue(avatarBytes));
    }

    if (!q.exec()) {
        qDebug() << "updateOwnAccount error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}
bool Personnel::saveFaceIdByMail(const QString& mail, const QByteArray& faceData)
{
    if (mail.trimmed().isEmpty() || faceData.isEmpty()) {
        qDebug() << "saveFaceIdByMail: invalid mail or empty face data.";
        return false;
    }

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET FACE_ID_DATA = :faceData,
            FACE_ID_ENABLED = 1,
            FACE_ID_UPDATED_AT = SYSDATE
        WHERE MAIL = :mail
    )");

    q.bindValue(":faceData", QVariant::fromValue(faceData));
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "saveFaceIdByMail error:" << q.lastError().text();
        return false;
    }

    qDebug() << "saveFaceIdByMail OK | mail =" << mail
             << "| rows =" << q.numRowsAffected()
             << "| bytes =" << faceData.size();

    return q.numRowsAffected() > 0;
}

bool Personnel::hasFaceIdRegistered(const QString& mail)
{
    if (mail.trimmed().isEmpty()) {
        return false;
    }

    QSqlQuery q;
    q.prepare(R"(
        SELECT FACE_ID_ENABLED, FACE_ID_DATA
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "hasFaceIdRegistered error:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        return false;
    }

    const int enabled = q.value(0).toInt();
    const QByteArray faceData = q.value(1).toByteArray();

    return enabled == 1 && !faceData.isEmpty();
}

bool Personnel::removeFaceIdByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) {
        qDebug() << "removeFaceIdByMail: empty mail.";
        return false;
    }

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET FACE_ID_DATA = NULL,
            FACE_ID_ENABLED = 0,
            FACE_ID_UPDATED_AT = NULL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "removeFaceIdByMail error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}

Personnel::FaceLoginResult Personnel::authenticateByFaceId(const QByteArray& capturedFaceData,
                                                           QString* outMail,
                                                           QString* outRole,
                                                           QString* outCvStatus)
{
    if (capturedFaceData.isEmpty()) {
        return FaceLoginResult::FaceNotRecognized;
    }

    QSqlQuery q;
    q.prepare(R"(
        SELECT MAIL, ROLE, CVSTATUS, FACE_ID_ENABLED, NVL(ACCOUNT_STATUS, 'ACTIVE')
        FROM FATMA.PERSONNEL
        WHERE FACE_ID_DATA = :faceData
    )");
    q.bindValue(":faceData", QVariant::fromValue(capturedFaceData));

    if (!q.exec()) {
        qDebug() << "authenticateByFaceId error:" << q.lastError().text();
        return FaceLoginResult::DbError;
    }

    if (!q.next()) {
        return FaceLoginResult::FaceNotRecognized;
    }

    const QString mail          = q.value(0).toString();
    const QString role          = q.value(1).toString();
    const QString cvStatus      = q.value(2).toString();
    const int faceEnabled       = q.value(3).toInt();
    const QString accountStatus = q.value(4).toString();

    if (outMail) *outMail = mail;
    if (outRole) *outRole = role;
    if (outCvStatus) *outCvStatus = cvStatus;

    if (accountStatus.trimmed().compare("BLOCKED", Qt::CaseInsensitive) == 0) {
        return FaceLoginResult::AccountBlocked;
    }

    if (faceEnabled != 1) {
        registerFailedAuthByMail(mail, "FACE_ID", 20);
        if (isAccountBlockedByMail(mail)) {
            return FaceLoginResult::AccountBlocked;
        }
        return FaceLoginResult::FaceNotEnabled;
    }

    if (cvStatus.trimmed().compare("Accepted", Qt::CaseInsensitive) != 0) {
        resetAuthRiskByMail(mail, "FACE_ID");
        return FaceLoginResult::CvNotAccepted;
    }

    resetAuthRiskByMail(mail, "FACE_ID");
    return FaceLoginResult::Ok;
}
QVector<Personnel::FaceRecord> Personnel::getAllRegisteredFaceIds()
{
    QVector<FaceRecord> records;

    QSqlQuery q;
    q.prepare(R"(
        SELECT IDPERS, MAIL, ROLE, CVSTATUS, FACE_ID_DATA
        FROM FATMA.PERSONNEL
        WHERE FACE_ID_ENABLED = 1
          AND FACE_ID_DATA IS NOT NULL
    )");

    if (!q.exec()) {
        qDebug() << "getAllRegisteredFaceIds error:" << q.lastError().text();
        return records;
    }

    while (q.next()) {
        FaceRecord rec;
        rec.idPers = q.value(0).toInt();
        rec.mail = q.value(1).toString();
        rec.role = q.value(2).toString();
        rec.cvStatus = q.value(3).toString();
        rec.faceData = q.value(4).toByteArray();

        qDebug() << "Loaded Face ID:" << rec.mail
                 << "| bytes =" << rec.faceData.size();

        records.push_back(rec);
    }

    return records;
}
bool Personnel::fetchCvAnalysisInputById(int idPers, CvAnalysisInput* out)
{
    if (!out) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT
            IDPERS,
            (PRENOM || ' ' || NOM) AS FULLNAME,
            ROLE,
            CVSTATUS,
            CV
        FROM FATMA.PERSONNEL
        WHERE IDPERS = :id
    )");
    q.bindValue(":id", idPers);

    if (!q.exec()) {
        qDebug() << "fetchCvAnalysisInputById error:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        return false;
    }

    out->idPers   = q.value(0).toInt();
    out->fullName = q.value(1).toString().trimmed();
    out->role     = q.value(2).toString().trimmed();
    out->cvStatus = q.value(3).toString().trimmed();
    out->cv       = q.value(4).toByteArray();

    return true;
}

bool Personnel::updateCvStatusById(int idPers, const QString& newStatus)
{
    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET CVSTATUS = :status
        WHERE IDPERS = :id
    )");
    q.bindValue(":status", newStatus.trimmed());
    q.bindValue(":id", idPers);

    if (!q.exec()) {
        qDebug() << "updateCvStatusById error:" << q.lastError().text();
        return false;
    }

    return true;
}
bool Personnel::resetAuthRiskByMail(const QString& mail, const QString& method)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET FAILED_LOGIN_ATTEMPTS = 0,
            LAST_LOGIN_ATTEMPT = SYSDATE,
            LAST_LOGIN_SUCCESS = SYSDATE,
            LAST_AUTH_METHOD = :method
        WHERE MAIL = :mail
    )");
    q.bindValue(":method", method.trimmed());
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "resetAuthRiskByMail error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}

bool Personnel::registerFailedAuthByMail(const QString& mail, const QString& method, int riskIncrement)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery readQ;
    readQ.prepare(R"(
        SELECT NVL(FAILED_LOGIN_ATTEMPTS, 0), NVL(RISK_SCORE, 0)
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    readQ.bindValue(":mail", mail.trimmed());

    if (!readQ.exec() || !readQ.next()) {
        qDebug() << "registerFailedAuthByMail read error:" << readQ.lastError().text();
        return false;
    }

    int failed = readQ.value(0).toInt() + 1;
    int risk   = readQ.value(1).toInt() + riskIncrement;

    if (failed >= 3) risk += 20;
    if (failed >= 5) risk += 30;

    const bool shouldBlock = (failed >= 5 || risk >= 60);
    QString status = shouldBlock ? "BLOCKED" : "ACTIVE";
    QDateTime blockedUntil = shouldBlock ? QDateTime::currentDateTime().addSecs(3600) : QDateTime();

    QSqlQuery updateQ;
    updateQ.prepare(R"(
    UPDATE FATMA.PERSONNEL
    SET FAILED_LOGIN_ATTEMPTS = :failed,
        LAST_LOGIN_ATTEMPT = SYSDATE,
        ACCOUNT_STATUS = :status,
        RISK_SCORE = :risk,
        LAST_AUTH_METHOD = :method,
        BLOCKED_UNTIL = :blockedUntil
    WHERE MAIL = :mail
)");
    updateQ.bindValue(":blockedUntil", shouldBlock ? QVariant(blockedUntil) : QVariant(QVariant::DateTime));
    updateQ.bindValue(":failed", failed);
    updateQ.bindValue(":status", status);
    updateQ.bindValue(":risk", risk);
    updateQ.bindValue(":method", method.trimmed());
    updateQ.bindValue(":mail", mail.trimmed());

    if (!updateQ.exec()) {
        qDebug() << "registerFailedAuthByMail update error:" << updateQ.lastError().text();
        return false;
    }

    return updateQ.numRowsAffected() > 0;
}

bool Personnel::registerUnknownAuthAttempt(const QString& method)
{
    Q_UNUSED(method);
    return true;
}

bool Personnel::isAccountBlockedByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT NVL(ACCOUNT_STATUS, 'ACTIVE')
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec() || !q.next()) {
        return false;
    }

    return q.value(0).toString().trimmed().compare("BLOCKED", Qt::CaseInsensitive) == 0;
}

int Personnel::getRiskScoreByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) return 0;

    QSqlQuery q;
    q.prepare(R"(
        SELECT NVL(RISK_SCORE, 0)
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec() || !q.next()) {
        return 0;
    }

    return q.value(0).toInt();
}

bool Personnel::unblockAccountByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET ACCOUNT_STATUS = 'ACTIVE',
            FAILED_LOGIN_ATTEMPTS = 0,
            RISK_SCORE = 0
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "unblockAccountByMail error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}
bool Personnel::isBlockExpiredByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT BLOCKED_UNTIL
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec() || !q.next()) {
        return false;
    }

    if (q.value(0).isNull()) {
        return false;
    }

    const QDateTime blockedUntil = q.value(0).toDateTime();
    return QDateTime::currentDateTime() >= blockedUntil;
}

bool Personnel::clearExpiredBlockByMail(const QString& mail)
{
    if (mail.trimmed().isEmpty()) return false;

    QSqlQuery q;
    q.prepare(R"(
        UPDATE FATMA.PERSONNEL
        SET ACCOUNT_STATUS = 'ACTIVE',
            FAILED_LOGIN_ATTEMPTS = 0,
            RISK_SCORE = 0,
            BLOCKED_UNTIL = NULL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "clearExpiredBlockByMail error:" << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}
Personnel::FaceLoginResult Personnel::authenticateByFaceIdMail(const QString& mail,
                                                               QString* outMail,
                                                               QString* outRole,
                                                               QString* outCvStatus)
{
    if (mail.trimmed().isEmpty()) {
        return FaceLoginResult::FaceNotRecognized;
    }

    QSqlQuery q;
    q.prepare(R"(
        SELECT MAIL, ROLE, CVSTATUS, FACE_ID_ENABLED, NVL(ACCOUNT_STATUS, 'ACTIVE')
        FROM FATMA.PERSONNEL
        WHERE MAIL = :mail
    )");
    q.bindValue(":mail", mail.trimmed());

    if (!q.exec()) {
        qDebug() << "authenticateByFaceIdMail error:" << q.lastError().text();
        return FaceLoginResult::DbError;
    }

    if (!q.next()) {
        return FaceLoginResult::FaceNotRecognized;
    }

    const QString dbMail         = q.value(0).toString();
    const QString role           = q.value(1).toString();
    const QString cvStatus       = q.value(2).toString();
    const int faceEnabled        = q.value(3).toInt();
    const QString accountStatus  = q.value(4).toString();

    if (outMail) *outMail = dbMail;
    if (outRole) *outRole = role;
    if (outCvStatus) *outCvStatus = cvStatus;

    if (accountStatus.trimmed().compare("BLOCKED", Qt::CaseInsensitive) == 0) {
        if (isBlockExpiredByMail(dbMail)) {
            clearExpiredBlockByMail(dbMail);
        } else {
            return FaceLoginResult::AccountBlocked;
        }
    }

    if (faceEnabled != 1) {
        registerFailedAuthByMail(dbMail, "FACE_ID", 20);
        return FaceLoginResult::FaceNotEnabled;
    }

    if (cvStatus.trimmed().compare("Accepted", Qt::CaseInsensitive) != 0) {
        resetAuthRiskByMail(dbMail, "FACE_ID");
        return FaceLoginResult::CvNotAccepted;
    }

    resetAuthRiskByMail(dbMail, "FACE_ID");
    return FaceLoginResult::Ok;
}
bool Personnel::getEmployeeOfMonth(EmployeeOfMonth* out)
{
    if (!out) return false;

    QSqlQuery q;
    q.prepare(R"(
        SELECT
            IDPERS,
            TRIM(PRENOM || ' ' || NOM) AS FULLNAME,
            ROLE,
            AVATAR
        FROM FATMA.PERSONNEL
        WHERE UPPER(TRIM(CVSTATUS)) = 'ACCEPTED'
        ORDER BY IDPERS
    )");

    if (!q.exec()) {
        qDebug() << "getEmployeeOfMonth error:" << q.lastError().text();
        return false;
    }

    QVector<EmployeeOfMonth> acceptedEmployees;

    while (q.next()) {
        EmployeeOfMonth emp;
        emp.idPers = q.value(0).toInt();
        emp.fullName = q.value(1).toString().trimmed();
        emp.role = q.value(2).toString().trimmed();
        emp.avatar = q.value(3).toByteArray();
        acceptedEmployees.push_back(emp);
    }

    if (acceptedEmployees.isEmpty()) {
        return false;
    }

    const QDate currentDate = QDate::currentDate();


    const int monthKey = currentDate.year() * 100 + currentDate.month();


    const int index = monthKey % acceptedEmployees.size();

    *out = acceptedEmployees[index];
    return true;
}



