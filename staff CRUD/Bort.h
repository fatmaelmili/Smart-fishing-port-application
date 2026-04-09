#ifndef BORT_H
#define BORT_H

#include <QMainWindow>
#include <QSslSocket>
#include <QChartView>
#include <QTableWidget>
#include <QPdfWriter>
#include <QPainter>
#include <opencv2/opencv.hpp>
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

private:
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
    cv::Mat detectAndCropFace(const cv::Mat& frame);
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
    double compareFacesDistance(const cv::Mat& face1, const cv::Mat& face2);
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

};

#endif // BORT_H
