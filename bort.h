#ifndef BORT_H
#define BORT_H

#include "qmessagebox.h"
#include <QMainWindow>
#include <QPropertyAnimation>//added this
#include <QGraphicsOpacityEffect>//added this
#include <QList>//added this
#include <QPair>//added this
#include <QTimer>//added this
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>//added this
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

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
    void on_aiclientbtn_clicked();//added this
    void loadClientsFromDB();//added this
    void showAnimatedPopup(QString prediction, double confidence);//added this
    void runAIPrediction(int clientId);//added this
    void on_aipredictionbtndashboard_clicked();
    void showAIPopup();
    void predictGains();
    void predictBestFish();//added all of these
private:
    Ui::SignIn *ui;
    //added all of this
    double getMonthlyGains();
    QString getMostSoldItem(int &quantity);
    int getTotalPurchases();
    void updateDashboard();
    void setupBarChart();
    void setupPieChart();
    void handleBarClicked(int index);
    void handlePieClicked(QPieSlice *slice);
    QMessageBox *loadingMsg = nullptr;//added this
    void loadClients(QString search = "", QString sort = "");
    void on_pdfitembtn_clicked();
    void showStyledPopup(QString text);
};

#endif // BORT_H
