#ifndef CLIENTS_H
#define CLIENTS_H

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
    SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_btnForgetmdp_clicked();

    void on_backsigninBTN_clicked();

    void on_resetbtn_clicked();

    void on_ubploacvbtn_clicked();

    void on_signinbtn_clicked();

    void on_clientsmanagementBTN_W_clicked();



    void on_backtoclientbtn_clicked();

    void on_mainpagebtn_clicked();

    void on_clientdashboardbtn_clicked();

private:
    Ui::SignIn *ui;
};
#endif // CLIENTS_H
