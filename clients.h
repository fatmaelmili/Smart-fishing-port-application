#ifndef CLIENTS_H
#define CLIENTS_H

#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class SignIn;
}
QT_END_NAMESPACE

class SignIn : public QMainWindow
{
    Q_OBJECT

public:
    SignIn(QWidget *parent = nullptr);

    // Constructor used for CRUD operations
    SignIn(QString type, QString datecl, float montant, QString modepay,
           QString etat, QString description, QString article, int qte);

    ~SignIn();

    // CRUD functions
    bool ajouterClient();
    bool supprimerClient(int idclients);
    bool modifierClient(int idclients);
    QVector<QStringList> afficherClients();

    // Table refresh
    void loadClients();

private slots:

    void on_btnForgetmdp_clicked();
    void on_backsigninBTN_clicked();
    void on_resetbtn_clicked();
    void on_signinbtn_clicked();
    void on_clientsmanagementBTN_W_clicked();
    void on_backtoclientbtn_clicked();
    void on_mainpagebtn_clicked();
    void on_clientdashboardbtn_clicked();

    // CLIENT BUTTONS
    void on_clientaddbtn_clicked();
    void on_deleteclientbtn_clicked();
    void on_updateclientbtn_clicked();

private:
    Ui::SignIn *ui;

    // CLIENT ATTRIBUTES (database fields)
    int idclients;
    QString type;
    QString datecl;
    float montant;
    QString modepay;
    QString etat;
    QString description;
    QString article;
    int qte;
};

#endif // CLIENTS_H
