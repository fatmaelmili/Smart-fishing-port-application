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

    void on_logOutBTNZ_clicked();

    void on_userprofiledetails_Z_clicked();

    void on_fishingzonemanagementBTNZ_clicked();

    void on_fishingzonemanagementBTN_clicked();

    void on_fishingzonemanagementBTN_W_clicked();

    void on_fishingzonemanagementBTN_U_clicked();

    void on_fishingzonemanagementBTN_A_clicked();

    void on_fishingzonemanagementBTN_D_clicked();

    void on_stockmanagementBTN_stock_clicked();

    void on_userprofiledetails_stock_clicked();

    void on_fishingzonemanagementBTN_stock_clicked();

    void on_logOutBTN_stock_clicked();

    void on_stockmanagementBTNZ_clicked();

    void on_staffmanagementBTN_clicked();

    void on_stockmanagementBTN_W_clicked();

    void on_stockmanagementBTN_U_clicked();

    void on_stockmanagementBTN_A_clicked();

    void on_stockmanagementBTN_D_clicked();

    void on_stockmanagementBTN_clicked();

    void on_logOutBTNe_clicked();

    void on_fishingzonemanagementBTNe_clicked();

    void on_stockmanagementBTNe_clicked();

    void on_staffmanagementBTNe_clicked();

    void on_userprofiledetailsE_clicked();

    void on_backWbtnE_clicked();

    void on_equipmentmanagementBTN_stock_clicked();

    void on_equipmentmanagementBTNZ_clicked();

    void on_equipmentmanagementBTN_clicked();

    void on_equipmentmanagementBTN_W_clicked();

    void on_equipmentmanagementBTN_U_clicked();

    void on_equipmentmanagementBTN_A_clicked();

    void on_equipmentmanagementBTN_D_clicked();

    void on_staffmanagementBTNA_clicked();

    void on_stockmanagementBTNA_clicked();

    void on_equipmentmanagementBTNA_clicked();

    void on_fishingzonemanagementBTNA_clicked();

    void on_logOutBTNA_clicked();

    void on_userprofileC_clicked();

    void on_mainpagebtn_clicked();

    void on_clientdashboardbtn_clicked();

    void on_staffmanagementBTN_DC_clicked();

    void on_stockmanagementBTN_D_2_clicked();

    void on_equipmentmanagementBTN_DC_clicked();

    void on_fishingzonemanagementBTN_DC_clicked();

    void on_logOutBTN_DC_clicked();

    void on_userprofiledetails_DC_clicked();

    void on_backtoclientbtn_clicked();

    void on_clientsmanagementBTNe_clicked();

    void on_clientsmanagementBTN_stock_clicked();

    void on_clientsmanagementBTNZ_clicked();

    void on_clientsmanagementBTN_clicked();

    void on_clientsmanagementBTN_W_clicked();

    void on_clientsmanagementBTN_U_clicked();

    void on_clientsmanagementBTN_A_clicked();

    void on_clientsmanagementBTN_D_clicked();

private:
    Ui::SignIn *ui;
};

#endif // BORT_H
