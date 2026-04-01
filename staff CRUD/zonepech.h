#ifndef ZONEPECHE_H
#define ZONEPECHE_H

#include <QString>

class ZonePech
{
private:
    int idZone;
    QString nom;
    QString longitude;
    QString latitude;
    QString typeZone;
    QString niveauRisque;
    QString description;

public:
    ZonePech();
    ZonePech(QString nom, QString longitude, QString latitude,
             QString typeZone, QString niveauRisque, QString description);
    ZonePech(int idZone, QString nom, QString longitude, QString latitude,
             QString typeZone, QString niveauRisque, QString description);

    // Getters
    int getIdZone() const;
    QString getNom() const;
    QString getLongitude() const;
    QString getLatitude() const;
    QString getTypeZone() const;
    QString getNiveauRisque() const;
    QString getDescription() const;

    // Setters
    void setIdZone(int idZone);
    void setNom(const QString &nom);
    void setLongitude(const QString &longitude);
    void setLatitude(const QString &latitude);
    void setTypeZone(const QString &typeZone);
    void setNiveauRisque(const QString &niveauRisque);
    void setDescription(const QString &description);

    // CRUD
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
};

#endif // ZONEPECHE_H
