#ifndef BORT_H
#define BORT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SignIn;
}
QT_END_NAMESPACE

class SignIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    // NAVIGATION
    void on_btnForgetmdp_clicked();
    void on_backsigninBTN_clicked();
    void on_resetbtn_clicked();
    void on_signinbtn_clicked();
    void on_mainpagebtn_clicked();
    void on_clientdashboardbtn_clicked();
    void on_backtoclientbtn_clicked();
    void on_clientsmanagementBTN_W_clicked();

    // CLIENT MANAGEMENT
    void on_clientaddbtn_clicked();
    void on_deleteclientbtn_clicked();
    void on_updateclientbtn_clicked();

private:
    Ui::SignIn *ui;

    void loadClients();
};

#endif // BORT_H
