#include "zonepech.h"

#include <QSqlQuery>

ZonePech::ZonePech()
{
    idZone = 0;
    nom = "";
    longitude = "";
    latitude = "";
    typeZone = "";
    niveauRisque = "";
    description = "";
}

ZonePech::ZonePech(QString nom, QString longitude, QString latitude,
                   QString typeZone, QString niveauRisque, QString description)
{
    this->idZone = 0;
    this->nom = nom;
    this->longitude = longitude;
    this->latitude = latitude;
    this->typeZone = typeZone;
    this->niveauRisque = niveauRisque;
    this->description = description;
}

ZonePech::ZonePech(int idZone, QString nom, QString longitude, QString latitude,
                   QString typeZone, QString niveauRisque, QString description)
{
    this->idZone = idZone;
    this->nom = nom;
    this->longitude = longitude;
    this->latitude = latitude;
    this->typeZone = typeZone;
    this->niveauRisque = niveauRisque;
    this->description = description;
}

// Getters
int ZonePech::getIdZone() const
{
    return idZone;
}

QString ZonePech::getNom() const
{
    return nom;
}

QString ZonePech::getLongitude() const
{
    return longitude;
}

QString ZonePech::getLatitude() const
{
    return latitude;
}

QString ZonePech::getTypeZone() const
{
    return typeZone;
}

QString ZonePech::getNiveauRisque() const
{
    return niveauRisque;
}

QString ZonePech::getDescription() const
{
    return description;
}

// Setters
void ZonePech::setIdZone(int idZone)
{
    this->idZone = idZone;
}

void ZonePech::setNom(const QString &nom)
{
    this->nom = nom;
}

void ZonePech::setLongitude(const QString &longitude)
{
    this->longitude = longitude;
}

void ZonePech::setLatitude(const QString &latitude)
{
    this->latitude = latitude;
}

void ZonePech::setTypeZone(const QString &typeZone)
{
    this->typeZone = typeZone;
}

void ZonePech::setNiveauRisque(const QString &niveauRisque)
{
    this->niveauRisque = niveauRisque;
}

void ZonePech::setDescription(const QString &description)
{
    this->description = description;
}

// CRUD
bool ZonePech::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ZONEPECHES (NOM, LONGITUDE, LATITUDE, TYPEZONE, NIVEAURISQUE, DESCRIPTION) "
                  "VALUES (:nom, :longitude, :latitude, :typeZone, :niveauRisque, :description)");

    query.bindValue(":nom", nom);
    query.bindValue(":longitude", longitude);
    query.bindValue(":latitude", latitude);
    query.bindValue(":typeZone", typeZone);
    query.bindValue(":niveauRisque", niveauRisque);
    query.bindValue(":description", description);

    return query.exec();
}

bool ZonePech::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE ZONEPECHES "
                  "SET NOM = :nom, LATITUDE = :latitude, LONGITUDE = :longitude, "
                  "TYPEZONE = :typeZone, NIVEAURISQUE = :niveauRisque, DESCRIPTION = :description "
                  "WHERE IDZONE = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":latitude", latitude);
    query.bindValue(":longitude", longitude);
    query.bindValue(":typeZone", typeZone);
    query.bindValue(":niveauRisque", niveauRisque);
    query.bindValue(":description", description);
    query.bindValue(":id", id);

    return query.exec();
}

bool ZonePech::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ZONEPECHES WHERE IDZONE = :id");
    query.bindValue(":id", id);

    return query.exec();
}

