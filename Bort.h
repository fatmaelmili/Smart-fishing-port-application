#ifndef BORT_H
#define BORT_H

#include <QMainWindow>
#include <QSslSocket>
#include <QChartView>
#include <QTableWidget>
#include <QPdfWriter>
#include <QPainter>
#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif
//APRESINTEGRATION
#include <QColor>
#include <QPixmap>
#include <QAudioSource>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QBuffer>
#include <QTimer>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtMath>
#include <QLabel>
//MALIK
#include <QSortFilterProxyModel>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include "arduino.h"

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
    //fatma
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

    void on_ubploaAvatarbtn_clicked();

    void on_addstaffbtn_clicked();
    void refreshStaffTable();
    void refreshStaffTable_U();

    void on_deletestaffbtn_clicked();

    void on_tablestaff_U_itemSelectionChanged();

    void on_addstaffbtn_U_clicked();

    void on_deletestaffbtn_U_clicked();

    void on_ubploacvbtn_U_clicked();

    void on_ubploavatarbtn_U_clicked();
    void on_showPassCheck_toggled(bool checked);

    void on_newbtn_clicked();

    void on_backsigninBTNR_clicked();

    void on_showPassCheckR_toggled(bool checked);

    void on_sortstaff_currentTextChanged(const QString &arg1);

    void on_sortstaff_U_currentTextChanged(const QString &arg1);

    void on_staffsearchbarre_textChanged(const QString &arg1);

    void on_staffsearchbarre_U_textChanged(const QString &arg1);

    void on_exportbtn_clicked();

    void on_exportpdfstaffbtn_U_clicked();

    void on_exportpdfstaffbtn_clicked();

    void on_addstaffbtn_A_clicked();

    void on_browbtn_clicked();

    void on_facebtn_clicked();

    void on_withfacebtn_clicked();

    void on_cvanalysebtn_U_clicked();

    void on_cvanalysebtn_clicked();

    void on_staffmanagementBTN_stock_clicked();


    void on_staffmanagementBTNZ_clicked();

    void on_Voicebtn_clicked();

    void on_withvoicebtn_clicked();
    void onArduinoReadyRead();

    //dhia
    void on_addZonebtn_clicked();
    void loadZonesToTable();
    void on_ZoneTable_cellClicked(int row, int column);
    void on_EditZonebtn_clicked();
    void on_DeleteZone_clicked();
    void on_exportZone_clicked();
    void showPieChart();

    void on_RiskPrediction_clicked();

    void on_Regulations_clicked();

    //sana
    void on_clientaddbtn_clicked();
    void on_deleteclientbtn_clicked();
    void on_updateclientbtn_clicked();
    void on_clientpdfbtn_clicked();
    void on_searchclient_textChanged(const QString &text);
    void on_clientsort_currentTextChanged(const QString &text);
    void loadItems();
    int getMaxQuantity(QString item);
    void on_itemsinput_currentTextChanged(const QString &text);
    //malik
    void on_delete_stock_clicked();

    void refreshStockTable();

    void on_edit_stock_clicked();

    void on_table_stock_clicked(const QModelIndex &index);
    void on_addspecies_stock_clicked();
    void on_exportpdf_stock_clicked();
    void on_sort_stock_currentTextChanged(const QString &text);
    void on_charts_stock_clicked();
    void on_search_stock_textChanged(const QString &text);
    void on_recognition_stock_clicked();
    //nour

    void refreshEquipmentTable();

    void on_addEqbtn_clicked();
    void on_tableeq_itemSelectionChanged();
    void on_modifybtn_clicked();
    void on_deletebtnE_clicked();



    void on_AnalyticsZone_clicked();

    void on_visual_stock_clicked();

private:
    //fatma
    struct CvAnalysisResult
    {
        int score = 0;
        QString decision;
        QStringList matchedRoleKeywords;
        QStringList matchedGeneralKeywords;
        QString summary;
    };

    Ui::SignIn *ui;
    QByteArray captureFaceFromCamera();
    QString ensureFaceCascadeFile();
#ifdef USE_OPENCV
    cv::Mat detectAndCropFace(const cv::Mat& frame);
#endif
    QByteArray m_cvBlob;
    QByteArray m_avatarBlob;
    QString m_currentRole;
    QChartView *m_roleChartView = nullptr;
    QChartView *m_cvChartView = nullptr;
    QWidget *m_roleLegendWidget = nullptr;
    QWidget *m_cvLegendWidget = nullptr;
    QString m_currentUserMail;
    int m_currentUserId = -1;
    QString m_currentAvatarPath;
    QByteArray m_currentAccountAvatar;
    int m_faceAuthFailureCount = 0;
    const int m_faceFraudThreshold = 3;
    QAudioFormat m_lastVoiceFormat;
    int m_voiceAuthFailureCount = 0;
    const int m_voiceFraudThreshold = 3;
    void registerFaceAuthFailure(const QString& reason);
    void resetFaceAuthFailureCounter();
    void showFaceFraudAlert(const QString& reason);
    void updateUserProfileUI(const QString& fullName, const QString& role, const QByteArray& avatarBytes);
    void applyRolePermissions(const QString& role);
    void setModuleAccess(const QString& prefix, bool allowed, bool hide = true);
    bool showCaptchaPuzzle();
    bool sendSmtpCommand(QSslSocket& socket, const QString& command, const QString& expectedCode);
    bool sendResetEmail(const QString& toMail, const QString& fullName, const QString& token);
    void loadStaffDashboardStats();
    void buildRoleChart();
    void buildCvStatusChart();
    QPixmap captureWidgetScaled(QWidget *widget, double scaleFactor = 3.0);
    void drawRoundedCard(QPainter &painter, const QRect &rect, const QColor &fillColor,const QColor &borderColor, int radius = 24);
    void exportStaffDashboardToPdf();
    void exportStaffTableToPdf(QTableWidget *table, const QString &reportTitle,const QString &defaultFileName);
    void openCurrentUserAccountPage();
    bool loadCurrentUserAccountData();
    void loadEmployeeCount();
    void updateFaceIdStatusLabel();
#ifdef USE_OPENCV
    double compareFacesDistance(const cv::Mat& face1, const cv::Mat& face2);
#endif
    bool authenticateWithFaceId();
    void runCvAnalysisForSelectedRow(QTableWidget *table);
    QString extractTextFromPdfBlob(const QByteArray& pdfBlob) const;
    QStringList roleKeywords(const QString& role) const;
    bool analyzeCvAgainstRole(const QByteArray& cvBlob,const QString& role,QString* outDecision,QString* outReport) const;
    QStringList generalCvKeywords() const;
    CvAnalysisResult analyzeCvAdvanced(const QByteArray& cvBlob, const QString& role) const;
    void showCvAnalysisDialog(const QString& fullName,const QString& role,const CvAnalysisResult& result);
    void clearUpdateStaffForm();
    void clearSignInForm(bool keepRememberedMail = false);
    void saveRememberedUser();
    void loadRememberedUser();
    void loadEmployeeOfMonth();
    QString extractAvatarInitials(const QString& fullName) const;
    QColor avatarColorFromName(const QString& fullName) const;
    QByteArray generateInitialsAvatar(const QString& fullName, int size = 160) const;
    void generateAvatarForAddStaff();
    void generateAvatarForUpdateStaff();
    QByteArray captureVoiceFromMicrophone(int durationMs = 3000);
    QVector<double> pcm16ToSamples(const QByteArray& audioBytes, const QAudioFormat& format) const;
    QVector<double> extractVoiceFeatures(const QByteArray& audioBytes, const QAudioFormat& format) const;
    QString voiceFeaturesToJson(const QVector<double>& features) const;
    QVector<double> jsonToVoiceFeatures(const QString& json) const;
    double compareVoiceFeatures(const QVector<double>& a, const QVector<double>& b) const;
    bool authenticateWithVoiceId();
    void updateVoiceIdStatusLabel();
    bool beginSessionForCurrentUser();
    void performLogoutFlow();
    void showStyledSessionLogoutMessage(const QString& fullName, qint64 sessionSeconds);
    QString formatDurationEnglish(qint64 totalSeconds) const;
    QLabel* ensureBestEmployeeHoursLabel();
    Arduino A;
    QByteArray m_arduinoBuffer;

    void initArduinoConnection();
    void processArduinoLine(const QByteArray& line);
    void processRfidUid(const QString& uid);
    QString formatMonthlyHoursForRfid(qint64 totalSeconds) const;
    void setupAccessHistoryTable();
    void addAccessHistoryEntry(const QString& user,const QString& status,const QString& method);
    void logRfidAccess(const QString& user, const QString& status);
    //dhia
    int selectedZoneId = -1;
    int predictSuitability(const QString& zoneType, const QString& riskLevel, double longitude, double latitude);
    QString suitabilityMessage(int score);
    QString suitabilityColor(int score);
    QString suitabilityLevel(int score);
    QString currentSeason();
    int environmentalWeatherModifier(double longitude, double latitude);
    QString generateRegulationsAI(const QString& zoneType, const QString& riskLevel, double longitude, double latitude);
    double calculateSimilarity(const QString& zoneType1, const QString& riskLevel1, double lon1, double lat1,
                               const QString& zoneType2, const QString& riskLevel2, double lon2, double lat2);
    //sana
    void loadClients(QString search = "", QString sort = "");

    //nour
    QString m_selectedEquipmentName;
    //MALIK
    QSortFilterProxyModel *proxyModel;
    Qt3DExtras::Qt3DWindow *view;
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QEntity *currentEntity;
    void init3DView();
    Qt3DCore::QEntity* loadModel(QString path);
};

#endif // BORT_H
