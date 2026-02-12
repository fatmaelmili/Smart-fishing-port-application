#ifndef SIGNIN_H
#define SIGNIN_H

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

    void on_staffmanagementBTN_W_clicked();



    void on_backstfbtn_clicked();

    void on_backWbtn_clicked();

    void on_staticbtn_clicked();

    void on_backWbtn_U_clicked();

    void on_staticbtn_U_clicked();

    void on_modifystaffbtn_clicked();

    void on_logOutBTN_W_clicked();

    void on_logOutBTN_U_clicked();

    void on_logOutBTN_D_clicked();

    void on_logOutBTN_clicked();

    void on_logOutBTN_A_clicked();

    void on_backWbtn_A_clicked();

    void on_userprofiledetails_A_clicked();

    void on_userprofiledetails_W_clicked();

    void on_userprofiledetails_clicked();

    void on_userprofiledetails_U_clicked();

    void on_userprofiledetails_D_clicked();

    void on_staffmanagementBTN_A_clicked();

private:
    Ui::SignIn *ui;
};
#endif // SIGNIN_H
