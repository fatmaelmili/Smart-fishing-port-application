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
    void on_btnForgetmdp_clicked();
    void on_backsigninBTN_clicked();
    void on_resetbtn_clicked();
    void on_signinbtn_clicked();
    void on_mainpagebtn_clicked();
    void on_clientdashboardbtn_clicked();
    void on_backtoclientbtn_clicked();
    void on_clientsmanagementBTN_W_clicked();
    void on_clientaddbtn_clicked();
    void on_deleteclientbtn_clicked();
    void on_updateclientbtn_clicked();
    void on_clientpdfbtn_clicked();
    void on_searchclient_textChanged(const QString &text);
    void on_clientsort_currentTextChanged(const QString &text);
    void loadItems();
    int getMaxQuantity(QString item);
    void on_itemsinput_currentTextChanged(const QString &text);

private:
    Ui::SignIn *ui;

    void loadClients(QString search = "", QString sort = "");
};

#endif // BORT_H
