#include "Bort.h"
#include "ui_Bort.h"
#include "personnel.h"
#include <opencv2/opencv.hpp>
#include <QBuffer>
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRandomGenerator>
#include <QDateTime>
#include <QSslSocket>
#include <QVBoxLayout>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSet>
#include <QHorizontalBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLegend>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QPageLayout>
#include <QDir>
#include <QTableWidget>
#include <QHeaderView>
#include <QFontMetrics>
#include <QTextOption>
#include <QSet>
#include <QTemporaryFile>
#include <QRegularExpression>
#include <QSet>
#include <QPdfDocument>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QSettings>
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    ui->statrole->hide();
    ui->statcv->hide();
    refreshStaffTable();
    refreshStaffTable_U();
    loadStaffDashboardStats();
    loadRememberedUser();
    loadEmployeeOfMonth();
    ui->staffmanagementBTN->setProperty("active", true);
    ui->staffmanagementBTN->style()->unpolish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->style()->polish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->update();
    ui->fishingzonemanagementBTNZ->setProperty("active", true);
    ui->fishingzonemanagementBTNZ->style()->unpolish(ui->fishingzonemanagementBTNZ);
    ui->fishingzonemanagementBTNZ->style()->polish(ui->fishingzonemanagementBTNZ);
    ui->fishingzonemanagementBTNZ->update();

    ui->PasswordEdit->setEchoMode(QLineEdit::Password);
    ui->NewEdit->setEchoMode(QLineEdit::Password);
    ui->passlab_A->setEchoMode(QLineEdit::Password);
    const auto avatarLabels = this->findChildren<QLabel*>();
    for (QLabel* lab : avatarLabels) {
        if (!lab) continue;

        if (lab->objectName().startsWith("avatar") &&
            lab->objectName() != "avatarpathEdit" &&
            lab->objectName() != "avatarpathEdit_U")
        {
            lab->setStyleSheet(R"(
            QLabel {
                background-color: rgba(255,255,255,0.06);
                border: 2px solid #38BDF8;
                border-radius: 28px;
                padding: 2px;
            }
            QLabel:hover {
                border: 2px solid #7DD3FC;
                background-color: rgba(255,255,255,0.10);
            }
        )");

            lab->setAlignment(Qt::AlignCenter);
            lab->setScaledContents(false);
            lab->setCursor(Qt::PointingHandCursor);

            QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(lab);
            effect->setBlurRadius(22);
            effect->setOffset(0, 0);
            effect->setColor(QColor(56, 189, 248, 140));
            lab->setGraphicsEffect(effect);
        }
    }


}
void SignIn::on_showPassCheck_toggled(bool checked)
{
    ui->PasswordEdit->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}
void SignIn::refreshStaffTable()
{
    QStringList headers = {
        "Staff Id",
        "Staff Full Name",
        "Staff Address",
        "Phone Number",
        "Staff Mail",
        "Staff Password",
        "Staff Role",
        "Cv Status",
        "Cv",
        "Avatar"
    };

    ui->tablestaff->clear();
    ui->tablestaff->setColumnCount(headers.size());
    ui->tablestaff->setHorizontalHeaderLabels(headers);
    ui->tablestaff->setRowCount(0);

    QString selectedSort = ui->sortstaff->currentText();
    QString searchText = ui->staffsearchbarre->text().trimmed();

    Personnel p;
    QVector<QStringList> rows = p.getStaffRows(selectedSort, searchText);

    ui->tablestaff->setRowCount(rows.size());

    for (int r = 0; r < rows.size(); ++r) {
        for (int c = 0; c < headers.size(); ++c) {
            QTableWidgetItem *item = new QTableWidgetItem(rows[r][c]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablestaff->setItem(r, c, item);
        }
    }

    ui->tablestaff->setColumnHidden(0, true);
    ui->tablestaff->resizeColumnsToContents();
}

SignIn::~SignIn()
{
    delete ui;
}




void SignIn::on_btnForgetmdp_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageForgetpass);
}


void SignIn::on_backsigninBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_resetbtn_clicked()
{
    QString mail = ui->resetlineEdit->text().trimmed();

    if (mail.isEmpty()) {
        ui->resetlabel->setText("Please enter your email.");
        return;
    }

    QRegularExpression reMail("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$");
    if (!reMail.match(mail).hasMatch()) {
        ui->resetlabel->setText("Please enter a valid email address.");
        return;
    }

    QString fullName;
    if (!Personnel::findUserByMail(mail, &fullName)) {
        ui->resetlabel->setText("No account found with this email.");
        return;
    }

    if (!showCaptchaPuzzle()) {
        ui->resetlabel->setText("Captcha failed. Please try again.");
        return;
    }

    const QString token = Personnel::generateResetToken();

    if (!Personnel::saveResetToken(mail, token, 15)) {
        ui->resetlabel->setText("Could not generate reset request.");
        return;
    }

    if (!sendResetEmail(mail, fullName, token)) {
        ui->resetlabel->setText("Token saved, but email sending failed.");
        return;
    }

    ui->resetlabel->setText("Reset link sent successfully. Please check your email.");
    ui->stackedWidget->setCurrentWidget(ui->pageresetmdp);
    ui->tokenlineEdit->clear();
    ui->NewEdit->clear();
    ui->tokenlineEdit->setFocus();
}

bool SignIn::showCaptchaPuzzle()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Anti-robot verification");
    dialog.setModal(true);
    dialog.setMinimumSize(360, 220);
    dialog.setStyleSheet(R"(
        QDialog {
            background-color: #0E3150;
            color: white;
            border-radius: 10px;
        }
        QLabel {
            color: white;
            font-size: 14px;
        }
        QPushButton {
            background-color: #1E66F5;
            color: white;
            font-size: 16px;
            border: none;
            border-radius: 8px;
            padding: 10px;
            min-height: 44px;
        }
        QPushButton:hover {
            background-color: #3B82F6;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *title = new QLabel("Mini puzzle: click the numbers in order 1 → 2 → 3 → 4");
    title->setWordWrap(true);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QGridLayout *grid = new QGridLayout();
    mainLayout->addLayout(grid);

    QList<int> values = {1, 2, 3, 4};
    for (int i = values.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        values.swapItemsAt(i, j);
    }

    int expected = 1;

    for (int i = 0; i < values.size(); ++i) {
        QPushButton *btn = new QPushButton(QString::number(values[i]));
        grid->addWidget(btn, i / 2, i % 2);

        connect(btn, &QPushButton::clicked, &dialog, [&, btn, value = values[i]]() mutable {
            if (value == expected) {
                btn->setEnabled(false);
                expected++;
                if (expected == 5) {
                    dialog.accept();
                }
            } else {
                QMessageBox::warning(&dialog, "Wrong order",
                                     "Wrong order. Please restart the verification.");
                dialog.reject();
            }
        });
    }

    QPushButton *cancelBtn = new QPushButton("Cancel");
    mainLayout->addWidget(cancelBtn);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    return dialog.exec() == QDialog::Accepted;
}

bool SignIn::sendSmtpCommand(QSslSocket& socket, const QString& command, const QString& expectedCode)
{
    if (!command.isEmpty()) {
        socket.write(command.toUtf8());
        if (!socket.waitForBytesWritten(10000))
            return false;
    }

    if (!socket.waitForReadyRead(10000))
        return false;

    const QByteArray response = socket.readAll();
    qDebug() << "SMTP:" << response;

    return response.startsWith(expectedCode.toUtf8());
}

bool SignIn::sendResetEmail(const QString& toMail, const QString& fullName, const QString& token)
{

    const QString smtpHost = "smtp.gmail.com";
    const int smtpPort = 465;
    const QString senderEmail = "bortapplication@gmail.com";
    const QString senderPassword = "azqf mjxk jdlq qbyl";

    QString subject = "BORT Password Reset";
    QString body =
        "Hello " + fullName + ",\r\n\r\n"
                              "We received a request to reset your BORT account password.\r\n\r\n"
                              "Your reset code:\r\n" + token + "\r\n\r\n"
                  "Please return to the application and enter this code to reset your password.\r\n\r\n"
                  "This code will expire in 15 minutes.\r\n"
                  "If you did not request this reset, please ignore this email.\r\n\r\n"
                  "Best regards,\r\n"
                  "BORT - Smart Fishing Port Application";

    QSslSocket socket;
    socket.connectToHostEncrypted(smtpHost, smtpPort);

    if (!socket.waitForEncrypted(15000)) {
        qDebug() << "SSL connection failed:" << socket.errorString();
        return false;
    }

    if (!sendSmtpCommand(socket, "", "220")) return false;
    if (!sendSmtpCommand(socket, "EHLO localhost\r\n", "250")) return false;
    if (!sendSmtpCommand(socket, "AUTH LOGIN\r\n", "334")) return false;
    if (!sendSmtpCommand(socket, senderEmail.toUtf8().toBase64() + "\r\n", "334")) return false;
    if (!sendSmtpCommand(socket, senderPassword.toUtf8().toBase64() + "\r\n", "235")) return false;
    if (!sendSmtpCommand(socket, "MAIL FROM:<" + senderEmail + ">\r\n", "250")) return false;
    if (!sendSmtpCommand(socket, "RCPT TO:<" + toMail + ">\r\n", "250")) return false;
    if (!sendSmtpCommand(socket, "DATA\r\n", "354")) return false;

    QString data;
    data += "From: BORT <" + senderEmail + ">\r\n";
    data += "To: <" + toMail + ">\r\n";
    data += "Subject: " + subject + "\r\n";
    data += "MIME-Version: 1.0\r\n";
    data += "Content-Type: text/plain; charset=UTF-8\r\n";
    data += "\r\n";
    data += body + "\r\n";
    data += ".\r\n";

    if (!sendSmtpCommand(socket, data, "250")) return false;
    if (!sendSmtpCommand(socket, "QUIT\r\n", "221")) return false;

    return true;
}

void SignIn::on_ubploacvbtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select a CV",
        QDir::homePath(),
        "CV (*.pdf *.doc *.docx);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open CV file.");
        return;
    }

    m_cvBlob = f.readAll();
    f.close();

    ui->cvpathEdit->setText(QFileInfo(filePath).fileName());
}
void SignIn::on_ubploaAvatarbtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select an avatar",
        QDir::homePath(),
        "Images (*.jpg *.jpeg *.png *.webp);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open avatar file.");
        return;
    }

    m_avatarBlob = f.readAll();
    f.close();

    ui->avatarpathEdit->setText(QFileInfo(filePath).fileName());
}

void SignIn::on_signinbtn_clicked()
{
    QString mail = ui->UserNameEdit->text().trimmed();
    QString pass = ui->PasswordEdit->text();

    if (mail.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Sign In", "Please enter email and password.");
        return;
    }

    QString role, cvStatus;
    const auto res = Personnel::authenticateByMailEx(mail, pass, &role, &cvStatus);

    if (res != Personnel::LoginResult::Ok) {
        switch (res) {
        case Personnel::LoginResult::UserNotFound:
            QMessageBox::critical(this, "Sign In", "No account found with this email.");
            break;

        case Personnel::LoginResult::WrongPassword:
            QMessageBox::critical(this, "Sign In", "Incorrect password.");
            break;

        case Personnel::LoginResult::CvNotAccepted:
            QMessageBox::warning(this, "Sign In",
                                 "Your account is not approved yet.\n"
                                 "CV Status: " + cvStatus + "\n"
                                                  "Please wait for acceptance.");
            break;

        case Personnel::LoginResult::AccountBlocked:
            QMessageBox::critical(this, "Sign In",
                                  "This account is temporarily blocked due to suspicious authentication activity.");
            break;

        case Personnel::LoginResult::SuspiciousActivity:
            QMessageBox::warning(this, "Sign In",
                                 "Suspicious activity detected.\nPlease try again later or contact the administrator.");
            break;

        case Personnel::LoginResult::DbError:
        default:
            QMessageBox::critical(this, "Sign In", "Database error. Please try again.");
            break;
        }
        return;
    }

    m_currentRole = role;
    applyRolePermissions(m_currentRole);
    Personnel::UserProfile prof;
    if (Personnel::fetchProfileByMail(mail, &prof)) {
        QString fullName = (prof.prenom + " " + prof.nom).trimmed();
        m_currentUserMail = mail;
        m_currentUserId = prof.idPers;
        m_currentAccountAvatar = prof.avatar;
        updateUserProfileUI(fullName, prof.avatar);
    }
    saveRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    loadEmployeeCount();
    clearSignInForm(ui->remembercheck->isChecked());
}


void SignIn::on_staffmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}




void SignIn::on_backstfbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_backWbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    loadEmployeeCount();
}


void SignIn::on_staticbtn_clicked()
{
    loadStaffDashboardStats();
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backWbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);

}


void SignIn::on_staticbtn_U_clicked()
{
    loadStaffDashboardStats();
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_modifystaffbtn_clicked()
{
    refreshStaffTable_U();
    ui->stackedWidget->setCurrentWidget(ui->pageupdate);

}


void SignIn::on_logOutBTN_W_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_U_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_D_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_A_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backWbtn_A_clicked()
{
    if (m_currentUserMail.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Face ID", "No connected user found.");
        return;
    }

    Personnel::AccountProfile profile;
    if (!Personnel::fetchAccountProfileByMail(m_currentUserMail, &profile)) {
        QMessageBox::warning(this, "Face ID", "Unable to load current user profile.");
        return;
    }

    if (profile.cvStatus.trimmed().compare("Accepted", Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, "Face ID", "Only users with an accepted CV can register Face ID.");
        return;
    }

    QByteArray faceData = captureFaceFromCamera();

    if (faceData.isEmpty()) {
        QMessageBox::warning(this, "Face ID", "Capture failed.");
        return;
    }

    if (!Personnel::saveFaceIdByMail(m_currentUserMail, faceData)) {
        QMessageBox::critical(this, "Face ID", "Failed to save Face ID.");
        return;
    }

    updateFaceIdStatusLabel();
    QMessageBox::information(this, "Face ID", "Face ID registered successfully.");
}


void SignIn::on_userprofiledetails_A_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_userprofiledetails_W_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_userprofiledetails_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_userprofiledetails_U_clicked()
{
    openCurrentUserAccountPage();
}




void SignIn::on_userprofiledetails_D_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_staffmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_logOutBTNZ_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_Z_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_fishingzonemanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}



void SignIn::on_fishingzonemanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_stockmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_userprofiledetails_stock_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_fishingzonemanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_stock_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_stockmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_staffmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}



void SignIn::on_stockmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_stockmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_stockmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_stockmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_stockmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_logOutBTNe_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_fishingzonemanagementBTNe_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_stockmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_staffmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_userprofiledetailsE_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_backWbtnE_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    loadEmployeeCount();
}


void SignIn::on_equipmentmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_staffmanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_stockmanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_equipmentmanagementBTNA_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_fishingzonemanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTNA_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofileC_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    loadEmployeeCount();
}


void SignIn::on_clientdashboardbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->dashC);
}


void SignIn::on_staffmanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_stockmanagementBTN_D_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_equipmentmanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_fishingzonemanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_DC_clicked()
{
    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_DC_clicked()
{
    openCurrentUserAccountPage();
}


void SignIn::on_backtoclientbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}





void SignIn::on_addstaffbtn_clicked()
{
    QString fullName = ui->staffnameedit->text().trimmed();
    QString adresse  = ui->staffaddressedit->text().trimmed();
    QString tel      = ui->teledit->text().trimmed();
    QString mail     = ui->mailedit->text().trimmed();
    QString mdp      = ui->passlab_2->text();
    QString role     = ui->role->currentText();
    QString cvStatus = ui->cvstat->currentText();
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Full name is required.");
        return;
    }
    QRegularExpression reName("^[\\p{L}]+(?:\\s+[\\p{L}]+)*$");
    if (!reName.match(fullName).hasMatch()) {
        QMessageBox::warning(this,
                             "Invalid name",
                             "Full name must contain only letters and spaces (no numbers or special characters).");
        ui->staffnameedit->setFocus();
        ui->staffnameedit->selectAll();
        return;
    }
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Warning", "adress is required.");
        return;
    }
    if (mail.isEmpty()) {
        QMessageBox::warning(this, "Warning", "mail is required.");
        return;
    }
    QRegularExpression reMail("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$");
    if (!reMail.match(mail).hasMatch()) {
        QMessageBox::warning(this, "Invalid email",
                             "Email must be like: name@example.com");
        ui->mailedit->setFocus();
        ui->mailedit->selectAll();
        return;
    }
    if (tel.isEmpty()) {
        QMessageBox::warning(this, "Warning", "phone number is required.");
        return;
    }
    QString telClean = tel;
    telClean.remove(' ');

    QRegularExpression reTel("^\\d{8}$");
    if (!telClean.isEmpty() && !reTel.match(telClean).hasMatch()) {
        QMessageBox::warning(this, "Invalid phone number",
                             "The phone number should contain at least 8 numbers .\n"
                             "Example : 22123456");
        ui->teledit->setFocus();
        ui->teledit->selectAll();
        return;
    }
    if (mdp.isEmpty()) {
        QMessageBox::warning(this, "Warning", "password is required.");
        return;
    }
    QRegularExpression reMdp("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$");

    if (!reMdp.match(mdp).hasMatch()) {
        QMessageBox::warning(this,
                             "Invalid password",
                             "Password must be at least 8 characters and contain:\n"
                             "-at least one uppercase letter (A-Z)\n"
                             "- at least one lowercase letter (a-z)\n"
                             "- at least one number (0-9)\n"
                             "- at least special character (ex: !@#$%^&*)");
        ui->passlab_2->setFocus();
        ui->passlab_2->selectAll();
        return;
    }
    if (role == "Staff Role") {
        QMessageBox::warning(this,
                             "Role is required",
                             "Choose an item from the list.");
        ui->role->setFocus();
        return;
    }

    if (cvStatus == "CvStatus") {
        QMessageBox::warning(this,
                             "CV Status is required",
                             "choose one item from the list.");
        ui->cvstat->setFocus();
        return;
    }
    if (m_cvBlob.isEmpty()) {
        QMessageBox::warning(this,
                             "CV required",
                             "Please upload a CV file before adding staff.");
        ui->cvpathEdit->setFocus();
        return;
    }

    if (m_avatarBlob.isEmpty()) {
        QMessageBox::warning(this,
                             "Avatar required",
                             "Please upload an avatar image before adding staff.");
        ui->avatarpathEdit->setFocus();
        return;
    }
    QStringList parts = fullName.split(' ', Qt::SkipEmptyParts);
    QString nom, prenom;
    if (parts.size() == 1) {
        nom = parts[0];
        prenom = "";
    } else {
        nom = parts.last();
        parts.removeLast();
        prenom = parts.join(" ");
    }


     Personnel p(nom, prenom, adresse, tel, mail, role, mdp, cvStatus, m_cvBlob, m_avatarBlob);
    if (p.ajouterStaff()) {
        QMessageBox::information(this, "Success", "Staff added successfully!");

        ui->staffnameedit->clear();
        ui->staffaddressedit->clear();
        ui->teledit->clear();
        ui->mailedit->clear();
        ui->passlab_2->clear();
        ui->cvpathEdit->clear();
        ui->avatarpathEdit->clear();
        ui->role->setCurrentText("Staff Role");
        ui->cvstat->setCurrentText("CvStatus");
        m_cvBlob.clear();
        m_avatarBlob.clear();
        refreshStaffTable();
        refreshStaffTable_U();

    } else {
        QMessageBox::critical(this, "Error", "Add staff failed!");

    }
}


void SignIn::on_deletestaffbtn_clicked()
{
    int row = ui->tablestaff->currentRow();
    if (row < 0) {
        QMessageBox::warning(this,
                             "No selection",
                             "Please select a staff row to delete.");
        return;
    }
    QTableWidgetItem *idItem = ui->tablestaff->item(row, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Error", "Cannot read staff ID.");
        return;
    }

    bool ok = false;
    int idPers = idItem->text().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Error", "Invalid staff ID.");
        return;
    }
    QString fullName = "";
    QTableWidgetItem *nameItem = ui->tablestaff->item(row, 1);
    if (nameItem) fullName = nameItem->text();
    auto rep = QMessageBox::question(
        this,
        "Confirm deletion",
        "Are you sure you want to delete this staff?\n\n" + fullName,
        QMessageBox::Yes | QMessageBox::No
        );

    if (rep != QMessageBox::Yes)
        return;
    Personnel p;
    if (p.supprimerStaff(idPers)) {
        QMessageBox::information(this, "Deleted", "Staff deleted successfully.");
        refreshStaffTable();
    } else {
        QMessageBox::critical(this, "Error", "Delete failed. Check database constraints.");
    }
}


void SignIn::refreshStaffTable_U()
{
    QStringList headers = {
        "Staff Id",
        "Staff Full Name",
        "Staff Address",
        "Phone Number",
        "Staff Mail",
        "Staff Password",
        "Staff Role",
        "Cv Status",
        "Cv",
        "Avatar"
    };

    ui->tablestaff_U->clear();
    ui->tablestaff_U->setColumnCount(headers.size());
    ui->tablestaff_U->setHorizontalHeaderLabels(headers);
    ui->tablestaff_U->setRowCount(0);

    QString selectedSort = ui->sortstaff_U->currentText();
    QString searchText = ui->staffsearchbarre_U->text().trimmed();

    Personnel p;
    QVector<QStringList> rows = p.getStaffRows(selectedSort, searchText);

    ui->tablestaff_U->setRowCount(rows.size());

    for (int r = 0; r < rows.size(); ++r) {
        for (int c = 0; c < headers.size(); ++c) {
            QTableWidgetItem *item = new QTableWidgetItem(rows[r][c]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablestaff_U->setItem(r, c, item);
        }
    }

    ui->tablestaff_U->setColumnHidden(0, true);
    ui->tablestaff_U->resizeColumnsToContents();
}
void SignIn::clearUpdateStaffForm()
{
    ui->staffnameedit_U->clear();
    ui->staffaddressedit_U->clear();
    ui->teledit_U->clear();
    ui->mailedit_U->clear();
    ui->passlab_U_2->clear();

    ui->role_U->setCurrentText("Staff Role");
    ui->cvstat_U->setCurrentText("CvStatus");

    ui->cvpathEdit_U->clear();
    ui->avatarpathEdit_U->clear();

    m_cvBlob.clear();
    m_avatarBlob.clear();

    ui->tablestaff_U->clearSelection();
    ui->tablestaff_U->setCurrentCell(-1, -1);
}

void SignIn::on_tablestaff_U_itemSelectionChanged()
{
    int row = ui->tablestaff_U->currentRow();
    if (row < 0) return;
    m_cvBlob.clear();
    m_avatarBlob.clear();


    QString fullName = ui->tablestaff_U->item(row, 1)->text();
    ui->staffnameedit_U->setText(fullName);

    ui->staffaddressedit_U->setText(ui->tablestaff_U->item(row, 2)->text());
    ui->teledit_U->setText(ui->tablestaff_U->item(row, 3)->text());
    ui->mailedit_U->setText(ui->tablestaff_U->item(row, 4)->text());
    ui->passlab_U_2->clear();
    ui->role_U->setCurrentText(ui->tablestaff_U->item(row, 6)->text());
    ui->cvstat_U->setCurrentText(ui->tablestaff_U->item(row, 7)->text());
    QString hasCv = ui->tablestaff_U->item(row, 8)->text();
    QString hasAv = ui->tablestaff_U->item(row, 9)->text();

    ui->cvpathEdit_U->setText(hasCv == "Yes" ? "CV already uploaded" : "No CV uploaded");
    ui->avatarpathEdit_U->setText(hasAv == "Yes" ? "Avatar already uploaded" : "No avatar uploaded");
}


void SignIn::on_addstaffbtn_U_clicked()
{
    int row = ui->tablestaff_U->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No selection", "Please select a staff to modify.");
        return;
    }
    int idPers = ui->tablestaff_U->item(row, 0)->text().toInt();

    QString fullName = ui->staffnameedit_U->text().trimmed();
    QString adresse  = ui->staffaddressedit_U->text().trimmed();
    QString tel      = ui->teledit_U->text().trimmed();
    QString mail     = ui->mailedit_U->text().trimmed();
    QString mdp      = ui->passlab_U_2->text();
    QString role     = ui->role_U->currentText();
    QString cvStatus = ui->cvstat_U->currentText();
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Full name is required.");
        return;
    }

    QRegularExpression reName("^[\\p{L}]+(?:\\s+[\\p{L}]+)*$");
    if (!reName.match(fullName).hasMatch()) {
        QMessageBox::warning(this,
                             "Invalid name",
                             "Full name must contain only letters and spaces (no numbers or special characters).");
        ui->staffnameedit_U->setFocus();
        ui->staffnameedit_U->selectAll();
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Warning", "adress is required.");
        return;
    }

    if (mail.isEmpty()) {
        QMessageBox::warning(this, "Warning", "mail is required.");
        return;
    }

    QRegularExpression reMail("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$");
    if (!reMail.match(mail).hasMatch()) {
        QMessageBox::warning(this, "Invalid email",
                             "Email must be like: name@example.com");
        ui->mailedit_U->setFocus();
        ui->mailedit_U->selectAll();
        return;
    }

    if (tel.isEmpty()) {
        QMessageBox::warning(this, "Warning", "phone number is required.");
        return;
    }

    QString telClean = tel;
    telClean.remove(' ');

    QRegularExpression reTel("^\\d{8}$");
    if (!reTel.match(telClean).hasMatch()) {
        QMessageBox::warning(this, "Invalid phone number",
                             "The phone number should contain exactly 8 digits.\n"
                             "Example : 22123456");
        ui->teledit_U->setFocus();
        ui->teledit_U->selectAll();
        return;
    }
    tel = telClean;
    if (!mdp.trimmed().isEmpty()) {
        QRegularExpression reMdp("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$");
        if (!reMdp.match(mdp).hasMatch()) {
            QMessageBox::warning(this,
                                 "Invalid password",
                                 "Password must be at least 8 characters and contain:\n"
                                 "- at least one uppercase letter (A-Z)\n"
                                 "- at least one lowercase letter (a-z)\n"
                                 "- at least one number (0-9)\n"
                                 "- at least one special character (ex: !@#$%^&*)");
            ui->passlab_U_2->setFocus();
            ui->passlab_U_2->selectAll();
            return;
        }
    }

    if (role == "Staff Role") {
        QMessageBox::warning(this, "Role is required", "Choose an item from the list.");
        ui->role_U->setFocus();
        return;
    }

    if (cvStatus == "CvStatus") {
        QMessageBox::warning(this, "CV Status is required", "choose one item from the list.");
        ui->cvstat_U->setFocus();
        return;
    }


    QString hasCv = ui->tablestaff_U->item(row, 8)->text();
    QString hasAv = ui->tablestaff_U->item(row, 9)->text();
    if (m_cvBlob.isEmpty() && hasCv != "Yes") {
        QMessageBox::warning(this,
                             "CV required",
                             "Please upload a CV file before updating staff.");
        ui->cvpathEdit_U->setFocus();
        return;
    }
    if (m_avatarBlob.isEmpty() && hasAv != "Yes") {
        QMessageBox::warning(this,
                             "Avatar required",
                             "Please upload an avatar image before updating staff.");
        ui->avatarpathEdit_U->setFocus();
        return;
    }

    auto rep = QMessageBox::question(
        this,
        "Confirm update",
        "Do you want to save changes for:\n\n" + fullName,
        QMessageBox::Yes | QMessageBox::No
        );
    if (rep != QMessageBox::Yes) return;
    QStringList parts = fullName.split(' ', Qt::SkipEmptyParts);
    QString nom, prenom;
    if (parts.size() == 1) { nom = parts[0]; prenom = ""; }
    else { nom = parts.last(); parts.removeLast(); prenom = parts.join(" "); }

    Personnel p(nom, prenom, adresse, tel, mail, role, mdp, cvStatus, m_cvBlob, m_avatarBlob);

    if (p.modifierStaff(idPers)) {
        QMessageBox::information(this, "Success", "Staff updated successfully.");
        ui->passlab_U_2->clear();
        refreshStaffTable_U();
        refreshStaffTable();
        clearUpdateStaffForm();
    } else {
        QMessageBox::critical(this, "Error", "Update failed.");
    }


}




void SignIn::on_deletestaffbtn_U_clicked()
{
    int row = ui->tablestaff_U->currentRow();
    if (row < 0) {
        QMessageBox::warning(this,
                             "No selection",
                             "Please select a staff row to delete.");
        return;
    }
    QTableWidgetItem *idItem = ui->tablestaff_U->item(row, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Error", "Cannot read staff ID.");
        return;
    }

    bool ok = false;
    int idPers = idItem->text().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Error", "Invalid staff ID.");
        return;
    }
    QString fullName = "";
    QTableWidgetItem *nameItem = ui->tablestaff_U->item(row, 1);
    if (nameItem) fullName = nameItem->text();
    auto rep = QMessageBox::question(
        this,
        "Confirm deletion",
        "Are you sure you want to delete this staff?\n\n" + fullName,
        QMessageBox::Yes | QMessageBox::No
        );

    if (rep != QMessageBox::Yes)
        return;
    Personnel p;
    if (p.supprimerStaff(idPers)) {
        QMessageBox::information(this, "Deleted", "Staff deleted successfully.");
        refreshStaffTable_U();
        refreshStaffTable();
        ui->staffnameedit_U->clear();
        ui->staffaddressedit_U->clear();
        ui->teledit_U->clear();
        ui->mailedit_U->clear();
        ui->passlab_U_2->clear();
        ui->role_U->setCurrentText("Staff Role");
        ui->cvstat_U->setCurrentText("CvStatus");

        m_cvBlob.clear();
        m_avatarBlob.clear();
        ui->cvpathEdit_U->clear();
        ui->avatarpathEdit_U->clear();

    } else {
        QMessageBox::critical(this, "Error", "Delete failed. Check database constraints.");
    }
}


void SignIn::on_ubploacvbtn_U_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select a CV",
        QDir::homePath(),
        "CV (*.pdf *.doc *.docx);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open CV file.");
        return;
    }

    m_cvBlob = f.readAll();
    f.close();

    ui->cvpathEdit_U->setText(QFileInfo(filePath).fileName());

}


void SignIn::on_ubploavatarbtn_U_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select an avatar",
        QDir::homePath(),
        "Images (*.jpg *.jpeg *.png *.webp);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open avatar file.");
        return;
    }

    m_avatarBlob = f.readAll();
    f.close();

    ui->avatarpathEdit_U->setText(QFileInfo(filePath).fileName());

}

void SignIn::setModuleAccess(const QString& prefix, bool allowed, bool hide)
{
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton* b : buttons) {
        if (!b) continue;
        if (b->objectName().startsWith(prefix)) {
            b->setEnabled(allowed);
            if (hide) b->setVisible(allowed);
        }
    }
}

void SignIn::applyRolePermissions(const QString& role)
{
    setModuleAccess("staffmanagementBTN", false);
    setModuleAccess("clientsmanagementBTN", false);
    setModuleAccess("stockmanagementBTN", false);
    setModuleAccess("equipmentmanagementBTN", false);
    setModuleAccess("fishingzonemanagementBTN", false);
    if (role == "Admin") {
        setModuleAccess("staffmanagementBTN", true);
        setModuleAccess("clientsmanagementBTN", true);
        setModuleAccess("stockmanagementBTN", true);
        setModuleAccess("equipmentmanagementBTN", true);
        setModuleAccess("fishingzonemanagementBTN", true);
    }
    else if (role == "Human resource") {
        setModuleAccess("staffmanagementBTN", true);
    }
    else if (role == "An accountant") {
        setModuleAccess("stockmanagementBTN", true);
        setModuleAccess("clientsmanagementBTN", true);
        setModuleAccess("equipmentmanagementBTN", true);
    }
    else if (role == "Regulatory manager") {
        setModuleAccess("fishingzonemanagementBTN", true);
    }
    else if (role == "Fisherman") {
        setModuleAccess("fishingzonemanagementBTN", true);
    }
    else if (role == "Security") {
        setModuleAccess("equipmentmanagementBTN", true);
    }
}
void SignIn::updateUserProfileUI(const QString& fullName, const QByteArray& avatarBytes)
{

    const auto profileBtns = this->findChildren<QCommandLinkButton*>();
    for (QCommandLinkButton* btn : profileBtns) {
        if (!btn) continue;
        if (btn->objectName().startsWith("userprofiledetails")) {
            btn->setText(fullName);
        }
    }

    if (!avatarBytes.isEmpty()) {
        QPixmap px;
        px.loadFromData(avatarBytes);

        if (!px.isNull()) {
            const auto avatarLabels = this->findChildren<QLabel*>();
            for (QLabel* lab : avatarLabels) {
                if (!lab) continue;

                if (lab->objectName().startsWith("avatar") &&
                    lab->objectName() != "avatarpathEdit" &&
                    lab->objectName() != "avatarpathEdit_U")
                {
                    QPixmap scaled = px.scaled(
                        lab->size(),
                        Qt::KeepAspectRatioByExpanding,
                        Qt::SmoothTransformation
                        );

                    QPixmap circular(lab->size());
                    circular.fill(Qt::transparent);

                    QPainter painter(&circular);
                    painter.setRenderHint(QPainter::Antialiasing, true);
                    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

                    QPainterPath path;
                    path.addEllipse(0, 0, lab->width(), lab->height());
                    painter.setClipPath(path);
                    painter.drawPixmap(0, 0, scaled);

                    lab->setPixmap(circular);
                    lab->setAlignment(Qt::AlignCenter);
                    lab->setScaledContents(false);
                }
            }
        }
    }
}

void SignIn::on_newbtn_clicked()
{
    QString token = ui->tokenlineEdit->text().trimmed();
    QString newPassword = ui->NewEdit->text();

    if (token.isEmpty()) {
        ui->tokenlabel->setText("Please enter your reset code.");
        return;
    }

    if (newPassword.isEmpty()) {
        ui->Newlabel->setText("Please enter your new password.");
        return;
    }

    QRegularExpression reMdp("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$");
    if (!reMdp.match(newPassword).hasMatch()) {
        QMessageBox::warning(this, "Invalid Password","Password must be at least 8 characters and contain uppercase, lowercase, number and special character.");
        return;
    }

    if (!Personnel::resetPasswordByToken(token, newPassword)) {
        ui->tokenlabel->setText("Invalid or expired reset code.");
        return;
    }

    QMessageBox::information(this, "Success", "Your password has been reset successfully.");

    ui->tokenlineEdit->clear();
    ui->NewEdit->clear();
    ui->tokenlabel->clear();
    clearSignInForm(false);

    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backsigninBTNR_clicked()
{
    clearSignInForm(false);
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_showPassCheckR_toggled(bool checked)
{
    ui->NewEdit->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}


void SignIn::on_sortstaff_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshStaffTable();
}


void SignIn::on_sortstaff_U_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshStaffTable_U();
}


void SignIn::on_staffsearchbarre_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshStaffTable();
}


void SignIn::on_staffsearchbarre_U_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshStaffTable_U();
}
void SignIn::loadStaffDashboardStats()
{
    if (ui->numberemp) {
        ui->numberemp->setText(QString::number(Personnel::getTotalStaffCount()));
    }

    buildRoleChart();
    buildCvStatusChart();
}

void SignIn::buildRoleChart()
{
    QMap<QString, int> stats = Personnel::getRoleStatistics();

    if (m_roleChartView) {
        delete m_roleChartView;
        m_roleChartView = nullptr;
    }

    if (m_roleLegendWidget) {
        delete m_roleLegendWidget;
        m_roleLegendWidget = nullptr;
    }

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.58);
    series->setPieSize(0.75);

    int total = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        total += it.value();
    }

    QList<QColor> colors = {
        QColor(QString("#58B8F6")),
        QColor(QString("#2D9CDB")),
        QColor(QString("#22C1C3")),
        QColor(QString("#3DD598")),
        QColor(QString("#4A90E2")),
        QColor(QString("#1ABC9C")),
        QColor(QString("#6FCF97")),
        QColor(QString("#56CCF2"))
    };

    int colorIndex = 0;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        if (it.value() <= 0)
            continue;

        QPieSlice *slice = series->append(it.key(), it.value());

        QColor c = colors[colorIndex % colors.size()];
        slice->setBrush(c);
        slice->setPen(QPen(Qt::transparent));
        slice->setLabelVisible(false);

        QObject::connect(slice, &QPieSlice::hovered, this, [slice](bool state) {
            slice->setExploded(state);
            slice->setPen(QPen(Qt::white, state ? 2 : 0));
        });

        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Staff Distribution by Role");
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setBackgroundVisible(false);
    chart->setPlotAreaBackgroundVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();

    QFont titleFont;
    titleFont.setPointSize(11);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);
    m_roleChartView = new QChartView(chart, ui->statRole);
    m_roleChartView->setRenderHint(QPainter::Antialiasing);
    m_roleChartView->setStyleSheet("background: transparent; border: none;");
    m_roleChartView->setGeometry(10, 35, 250, ui->statRole->height() - 50);
    m_roleChartView->show();
    m_roleLegendWidget = new QWidget(ui->statRole);
    m_roleLegendWidget->setGeometry(270, 70, ui->statRole->width() - 280, ui->statRole->height() - 90);
    m_roleLegendWidget->setStyleSheet("background: transparent;");

    QVBoxLayout *legendLayout = new QVBoxLayout(m_roleLegendWidget);
    legendLayout->setContentsMargins(0, 0, 0, 0);
    legendLayout->setSpacing(10);

    colorIndex = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        if (it.value() <= 0)
            continue;

        double percent = (total > 0) ? (100.0 * it.value() / total) : 0.0;
        QColor c = colors[colorIndex % colors.size()];

        QWidget *itemWidget = new QWidget(m_roleLegendWidget);
        itemWidget->setStyleSheet("background: transparent;");
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(0, 0, 0, 0);
        itemLayout->setSpacing(8);

        QLabel *colorBox = new QLabel(itemWidget);
        colorBox->setFixedSize(12, 12);
        colorBox->setStyleSheet(QString(
                                    "background-color: %1; border: 1px solid white; border-radius: 2px;"
                                    ).arg(c.name()));

        QString roleName = it.key();
        QString text;
        QString percentText = QString::number(percent, 'f', 1);

        if (roleName.length() > 14) {
            text = QString("%1\n%2%")
            .arg(roleName.left(14) + "...", percentText);
        } else {
            text = QString("%1\n%2%")
            .arg(roleName, percentText);
        }
        QLabel *textLabel = new QLabel(text, itemWidget);
        textLabel->setStyleSheet(
            "color: #E0E0E0;"
            "font-size: 7.5pt;"
            "font-weight: 500;"
            "background: transparent;"
            );
        textLabel->setWordWrap(true);

        itemLayout->addWidget(colorBox, 0, Qt::AlignTop);
        itemLayout->addWidget(textLabel);

        legendLayout->addWidget(itemWidget);

        colorIndex++;
    }

    legendLayout->addStretch();
    m_roleLegendWidget->show();
}

void SignIn::buildCvStatusChart()
{
    QMap<QString, int> stats = Personnel::getCvStatusStatistics();

    if (m_cvChartView) {
        delete m_cvChartView;
        m_cvChartView = nullptr;
    }

    if (m_cvLegendWidget) {
        delete m_cvLegendWidget;
        m_cvLegendWidget = nullptr;
    }

    QHorizontalBarSeries *series = new QHorizontalBarSeries();

    int maxValue = 0;

    QColor acceptedColor(QString("#46B5F4"));
    QColor pendingColor(QString("#A8D96F"));
    QColor rejectedColor(QString("#F5A623"));

    auto addStatusBar = [&](const QString& statusName, const QColor& color)
    {
        int value = stats.value(statusName, 0);

        QBarSet *set = new QBarSet(statusName);
        *set << value;
        set->setColor(color);
        set->setBorderColor(Qt::transparent);

        series->append(set);

        if (value > maxValue)
            maxValue = value;
    };

    addStatusBar("Accepted", acceptedColor);
    addStatusBar("Pending", pendingColor);
    addStatusBar("Rejected", rejectedColor);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("CV Review Status");
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setBackgroundVisible(false);
    chart->setPlotAreaBackgroundVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->setMargins(QMargins(8, 8, 8, 8));

    QFont titleFont;
    titleFont.setPointSize(11);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);


    QValueAxis *axisX = new QValueAxis();

    int maxAxis = ((maxValue + 4) / 5) * 5;

    axisX->setRange(0, maxAxis);
    axisX->setTickCount(6);
    axisX->setLabelFormat("%d");

    axisX->setLabelsBrush(QBrush(Qt::white));
    axisX->setGridLineColor(QColor(255, 255, 255, 45));
    axisX->setLinePen(QPen(Qt::white));


    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(QStringList() << "" );
    axisY->setVisible(false);
    axisY->setGridLineVisible(false);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    m_cvChartView = new QChartView(chart, ui->statcvstatus);
    m_cvChartView->setRenderHint(QPainter::Antialiasing);
    m_cvChartView->setStyleSheet("background: transparent; border: none;");
    m_cvChartView->setGeometry(120, 28, ui->statcvstatus->width() - 130, ui->statcvstatus->height() - 38);
    m_cvChartView->show();


    m_cvLegendWidget = new QWidget(ui->statcvstatus);
    m_cvLegendWidget->setGeometry(12, 78, 105, 95);
    m_cvLegendWidget->setStyleSheet("background: transparent;");

    QVBoxLayout *legendLayout = new QVBoxLayout(m_cvLegendWidget);
    legendLayout->setContentsMargins(0, 0, 0, 0);
    legendLayout->setSpacing(10);
    legendLayout->setAlignment(Qt::AlignVCenter);

    auto createLegendItem = [&](const QString& text, const QColor& color) -> QWidget*
    {
        QWidget *item = new QWidget(m_cvLegendWidget);
        item->setStyleSheet("background: transparent;");

        QHBoxLayout *layout = new QHBoxLayout(item);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(7);

        QLabel *colorBox = new QLabel(item);
        colorBox->setFixedSize(10, 10);
        colorBox->setStyleSheet(QString(
                                    "background-color: %1;"
                                    "border: 1px solid rgba(255,255,255,0.75);"
                                    "border-radius: 2px;"
                                    ).arg(color.name()));

        QLabel *label = new QLabel(text, item);
        label->setStyleSheet(
            "color: #E8EEF5;"
            "font-size: 8.5pt;"
            "font-weight: 500;"
            "background: transparent;"
            );

        layout->addWidget(colorBox);
        layout->addWidget(label);
        layout->addStretch();

        return item;
    };

    legendLayout->addStretch();
    legendLayout->addWidget(createLegendItem("Accepted", acceptedColor));
    legendLayout->addWidget(createLegendItem("Pending", pendingColor));
    legendLayout->addWidget(createLegendItem("Rejected", rejectedColor));
    legendLayout->addStretch();

    m_cvLegendWidget->show();
}
QPixmap SignIn::captureWidgetScaled(QWidget *widget, double scaleFactor)
{
    if (!widget)
        return QPixmap();

    const QSize sourceSize = widget->size();
    const QSize targetSize(sourceSize.width() * scaleFactor,
                           sourceSize.height() * scaleFactor);

    QPixmap pixmap(targetSize);
    pixmap.fill(Qt::transparent);

    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.scale(scaleFactor, scaleFactor);
    widget->render(&p, QPoint(), QRegion(),
                   QWidget::DrawWindowBackground | QWidget::DrawChildren);
    p.end();

    return pixmap;
}

void SignIn::drawRoundedCard(QPainter &painter, const QRect &rect, const QColor &fillColor,
                             const QColor &borderColor, int radius)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(borderColor, 2));
    painter.setBrush(fillColor);
    painter.drawRoundedRect(rect, radius, radius);
    painter.restore();
}
static QFont pdfFont(const QString &family, int pixelSize, bool bold = false)
{
    QFont f(family);
    f.setPixelSize(pixelSize);
    f.setBold(bold);
    return f;
}
void SignIn::exportStaffDashboardToPdf()
{
    loadStaffDashboardStats();
    qApp->processEvents();

    QString defaultName = QDir::homePath() + "/Staff_Dashboard_Report.pdf";

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Staff Dashboard as PDF",
        defaultName,
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setResolution(300);
    pdf.setPageMargins(QMarginsF(8, 8, 8, 8), QPageLayout::Millimeter);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "PDF Error", "Unable to create PDF file.");
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    const int pageW = pdf.width();
    const int pageH = pdf.height();

    const int margin = 55;
    const int pageInnerW = pageW - 2 * margin;
    painter.fillRect(0, 0, pageW, pageH,QColor(QStringLiteral("#071826")));

    QLinearGradient bgGrad(0, 0, pageW, pageH);
    bgGrad.setColorAt(0.0, QColor(8, 34, 52, 80));
    bgGrad.setColorAt(1.0, QColor(3, 15, 28, 0));
    painter.fillRect(0, 0, pageW, pageH, bgGrad);
    const int headerH = 240;
    QRect headerRect(margin, margin, pageInnerW, headerH);

    drawRoundedCard(painter, headerRect,
                    QColor(8, 33, 52, 235),
                    QColor(72, 170, 255, 90),
                    22);

    QPixmap logo(":/Images/logo.png");


    int logoSize = headerRect.height() - 5;

    QRect logoRect(
        headerRect.left() + 30,
        headerRect.top() + (headerRect.height() - logoSize) / 2,
        logoSize,
        logoSize
        );

    if (!logo.isNull()) {
        painter.drawPixmap(
            logoRect,
            logo.scaled(logoRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
    }

    const int textLeft = logoRect.right() + 40;
    const int textW = headerRect.right() - textLeft - 24;

    painter.setPen(Qt::white);
    painter.setFont(pdfFont("Arial", 44, true));
    painter.drawText(QRect(textLeft, headerRect.top() + 40, textW, 50),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "BORT - Smart Fishing Port Application");

    painter.setPen(QColor(QStringLiteral("#5CC8FF")));
    painter.setFont(pdfFont("Arial", 36, true));
    painter.drawText(QRect(textLeft, headerRect.top() + 105, textW, 40),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "Staff Dashboard Report");

    painter.setPen(QColor(QStringLiteral("#DCEBFA")));
    painter.setFont(pdfFont("Arial", 22, false));
    painter.drawText(QRect(textLeft, headerRect.top() + 160, textW, 30),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "Generated on " + QDateTime::currentDateTime().toString("dd/MM/yyyy  hh:mm"));

    painter.setPen(QPen(QColor(80, 180, 255, 90), 2));
    painter.drawLine(headerRect.left() + 18, headerRect.bottom() - 18,
                     headerRect.right() - 18, headerRect.bottom() - 18);

    const int topGap = 22;
    const int totalCardH = 145;
    QRect totalRect(margin, headerRect.bottom() + topGap, 360, totalCardH);

    drawRoundedCard(painter, totalRect,
                    QColor(10, 40, 63, 235),
                    QColor(72, 170, 255, 80),
                    20);

    painter.setPen(QColor(QStringLiteral("#8FD8FF")));
    painter.setFont(pdfFont("Arial", 34, true));
    painter.drawText(QRect(totalRect.left() + 24, totalRect.top() + 16,
                           totalRect.width() - 48, 30),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "Total Accepted Staff");

    painter.setPen(Qt::white);
    painter.setFont(pdfFont("Arial", 54, true));
    painter.drawText(QRect(totalRect.left() + 24, totalRect.top() + 46,
                           totalRect.width() - 48, 56),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     ui->numberemp->text());


    const int chartsTop = totalRect.bottom() + 28;
    const int footerReserved = 36;
    const int chartGap = 24;
    const int chartCardW = (pageInnerW - chartGap) / 2;
    const int chartCardH = pageH - chartsTop - margin - footerReserved;

    QRect roleCard(margin, chartsTop, chartCardW, chartCardH);
    QRect cvCard(margin + chartCardW + chartGap, chartsTop, chartCardW, chartCardH);

    drawRoundedCard(painter, roleCard,
                    QColor(8, 30, 48, 235),
                    QColor(72, 170, 255, 65),
                    24);

    drawRoundedCard(painter, cvCard,
                    QColor(8, 30, 48, 235),
                    QColor(72, 170, 255, 65),
                    24);

    painter.setPen(Qt::white);
    painter.setFont(pdfFont("Arial", 46, true));

    painter.drawText(QRect(roleCard.left() + 22, roleCard.top() + 18,
                           roleCard.width() - 44, 36),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "Staff Distribution by Role");

    painter.drawText(QRect(cvCard.left() + 22, cvCard.top() + 18,
                           cvCard.width() - 44, 36),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "CV Review Status");


    QPixmap rolePixmap = captureWidgetScaled(ui->statRole, 3.2);
    QPixmap cvPixmap   = captureWidgetScaled(ui->statcvstatus, 3.2);

    QRect roleTarget = roleCard.adjusted(14, 62, -14, -14);
    QRect cvTarget   = cvCard.adjusted(14, 62, -14, -14);
    if (!rolePixmap.isNull()) {
        painter.drawPixmap(roleTarget, rolePixmap.scaled(roleTarget.size(),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation));
    }

    if (!cvPixmap.isNull()) {
        painter.drawPixmap(cvTarget, cvPixmap.scaled(cvTarget.size(),
                                                     Qt::IgnoreAspectRatio,
                                                     Qt::SmoothTransformation));
    }


    painter.setPen(QColor(205, 225, 240, 190));
    painter.setFont(pdfFont("Arial", 16, false));
    painter.drawText(QRect(margin, pageH - margin + 2, pageInnerW, 22),
                     Qt::AlignCenter,
                     "BORT - Smart Fishing Port Application | Staff Dashboard Analytics");

    painter.end();

    QMessageBox::information(this, "Export PDF", "Staff dashboard PDF exported successfully.");
}
void SignIn::on_exportbtn_clicked()
{
    exportStaffDashboardToPdf();
}
void SignIn::exportStaffTableToPdf(QTableWidget *table,
                                   const QString &reportTitle,
                                   const QString &defaultFileName)
{
    if (!table) {
        QMessageBox::warning(this, "Export PDF", "Staff table not found.");
        return;
    }

    if (table->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "There is no staff data to export.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Staff List as PDF",
        QDir::homePath() + "/" + defaultFileName,
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setResolution(300);
    pdf.setPageMargins(QMarginsF(8, 8, 8, 8), QPageLayout::Millimeter);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "PDF Error", "Unable to create PDF file.");
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    const int pageW = pdf.width();
    const int pageH = pdf.height();

    const int margin = 55;
    const int contentW = pageW - (2 * margin);

    const QColor bgColor(QStringLiteral("#071826"));
    const QColor cardColor = QColor::fromRgb(8, 33, 52, 235);
    const QColor borderColor = QColor::fromRgb(72, 170, 255, 85);
    const QColor accentColor(QStringLiteral("#5CC8FF"));
    const QColor softText(QStringLiteral("#DCEBFA"));
    const QColor headerCellColor(QStringLiteral("#0E5A8A"));
    const QColor rowEvenColor(QStringLiteral("#0B2740"));
    const QColor rowOddColor(QStringLiteral("#0D314F"));
    const QColor lineColor = QColor::fromRgb(90, 170, 230, 70);

    auto drawPageBackground = [&]() {
        painter.fillRect(0, 0, pageW, pageH, bgColor);

        QLinearGradient bgGrad(0, 0, pageW, pageH);
        bgGrad.setColorAt(0.0, QColor(8, 34, 52, 85));
        bgGrad.setColorAt(1.0, QColor(3, 15, 28, 0));
        painter.fillRect(0, 0, pageW, pageH, bgGrad);
    };

    auto drawHeader = [&](int pageNumber) -> int {
        const int headerH = 285;
        QRect headerRect(margin, margin, contentW, headerH);

        drawRoundedCard(painter, headerRect, cardColor, borderColor, 22);

        QPixmap logo(":/Images/logo.png");
        int logoSize = headerRect.height() - 5;

        QRect logoRect(
            headerRect.left() + 30,
            headerRect.top() + 20,
            logoSize,
            logoSize
            );
        if (!logo.isNull()) {
            painter.drawPixmap(
                logoRect,
                logo.scaled(logoRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
                );
        }

        const int textLeft = logoRect.right() + 24;
        const int textW = headerRect.right() - textLeft - 24;

        painter.setPen(Qt::white);
        painter.setFont(pdfFont("Arial", 54, true));
        painter.drawText(QRect(textLeft, headerRect.top() + 40, textW, 50),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         "BORT - Smart Fishing Port Application");

        painter.setPen(accentColor);
        painter.setFont(pdfFont("Arial", 40, true));
        painter.drawText(QRect(textLeft, headerRect.top() + 105, textW, 40),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         reportTitle);

        painter.setPen(softText);
        painter.setFont(pdfFont("Arial", 28, false));
        painter.drawText(QRect(textLeft, headerRect.top() + 160, textW, 30),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         "Generated on " + QDateTime::currentDateTime().toString("dd/MM/yyyy  hh:mm"));

        painter.setPen(QPen(QColor(80, 180, 255, 90), 2));
        painter.drawLine(headerRect.left() + 18, headerRect.bottom() - 18,
                         headerRect.right() - 18, headerRect.bottom() - 18);

        painter.setPen(QColor(190, 220, 240, 180));
        painter.setFont(pdfFont("Arial", 15, false));
        painter.drawText(QRect(headerRect.right() - 120, headerRect.top() + 18, 95, 20),
                         Qt::AlignRight | Qt::AlignVCenter,
                         QString("Page %1").arg(pageNumber));

        return headerRect.bottom() + 28;
    };

    auto drawFooter = [&]() {
        painter.setPen(QColor(205, 225, 240, 185));
        painter.setFont(pdfFont("Arial", 16, false));
        painter.drawText(QRect(margin, pageH - margin + 2, contentW, 22),
                         Qt::AlignCenter,
                         "BORT - Smart Fishing Port Application | " +
                             QDate::currentDate().toString("dd/MM/yyyy"));
    };

    auto safeItemText = [&](int row, int col) -> QString {
        QTableWidgetItem *item = table->item(row, col);
        return item ? item->text().trimmed() : "";
    };

    auto elideText = [&](const QString &text, const QFont &font, int width) -> QString {
        QFontMetrics fm(font);
        return fm.elidedText(text, Qt::ElideRight, width - 12);
    };

    struct ExportColumn {
        int sourceCol;
        QString title;
        double ratio;
    };

    QList<ExportColumn> columns = {
                                   {1, "Staff Full Name", 0.21},
                                   {2, "Staff Address",   0.22},
                                   {3, "Phone Number",    0.12},
                                   {4, "Staff Mail",      0.25},
                                   {6, "Staff Role",      0.11},
                                   {7, "CV Status",       0.09}

    };

    const int tableTopPadding = 8;
    const int footerReserved = 40;
    const int tableHeaderH = 88;
    const int rowH = 68;

    QVector<int> colWidths;
    int totalAssigned = 0;
    for (int i = 0; i < columns.size(); ++i) {
        int w = int(contentW * columns[i].ratio);
        colWidths.push_back(w);
        totalAssigned += w;
    }
    if (!colWidths.isEmpty()) {
        colWidths.last() += (contentW - totalAssigned);
    }

    int currentPage = 1;
    drawPageBackground();
    int y = drawHeader(currentPage);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(10, 40, 63, 220));
    painter.drawRoundedRect(QRect(margin, y - 6, contentW, pageH - y - margin - footerReserved), 18, 18);

    auto drawTableHeader = [&](int topY) -> int {
        int x = margin;

        painter.setPen(Qt::NoPen);
        painter.setBrush(headerCellColor);
        painter.drawRoundedRect(QRect(x, topY, contentW, tableHeaderH), 10, 10);

        painter.setFont(pdfFont("Arial", 36, true));
        painter.setPen(Qt::white);

        for (int i = 0; i < columns.size(); ++i) {
            QRect cellRect(x, topY, colWidths[i], tableHeaderH);
            painter.drawText(cellRect.adjusted(10, 0, -10, 0),
                             Qt::AlignLeft | Qt::AlignVCenter,
                             columns[i].title);
            x += colWidths[i];
        }

        return topY + tableHeaderH;
    };

    y = drawTableHeader(y + tableTopPadding);

    QFont bodyFont = pdfFont("Arial", 35, false);
    painter.setFont(bodyFont);

    for (int row = 0; row < table->rowCount(); ++row) {
        if (y + rowH > pageH - margin - footerReserved) {
            drawFooter();
            pdf.newPage();
            currentPage++;

            drawPageBackground();
            y = drawHeader(currentPage);

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(10, 40, 63, 220));
            painter.drawRoundedRect(QRect(margin, y - 6, contentW, pageH - y - margin - footerReserved), 18, 18);

            y = drawTableHeader(y + tableTopPadding);
            painter.setFont(bodyFont);
        }

        int x = margin;
        QRect rowRect(margin, y, contentW, rowH);

        painter.setPen(Qt::NoPen);
        painter.setBrush((row % 2 == 0) ? rowEvenColor : rowOddColor);
        painter.drawRect(rowRect);

        painter.setPen(QPen(lineColor, 1));
        painter.drawLine(rowRect.bottomLeft(), rowRect.bottomRight());

        for (int c = 0; c < columns.size(); ++c) {
            QRect cellRect(x, y, colWidths[c], rowH);

            painter.setPen(QPen(lineColor, 1));
            painter.drawLine(cellRect.topRight(), cellRect.bottomRight());

            QString value = safeItemText(row, columns[c].sourceCol);

            painter.setPen(QColor(QStringLiteral("#EAF6FF")));
            painter.setFont(bodyFont);
            painter.drawText(cellRect.adjusted(12, 6, -12, -6),
                             Qt::AlignLeft | Qt::AlignVCenter,
                             elideText(value, bodyFont, cellRect.width() - 20));

            x += colWidths[c];
        }

        y += rowH;
    }

    drawFooter();
    painter.end();

    QMessageBox::information(this, "Export PDF", "Staff list PDF exported successfully.");
}


void SignIn::on_exportpdfstaffbtn_U_clicked()
{
    exportStaffTableToPdf(
        ui->tablestaff_U,
        "Staff List Report",
        "Staff_List_Report.pdf"
        );
}


void SignIn::on_exportpdfstaffbtn_clicked()
{
    exportStaffTableToPdf(
        ui->tablestaff,
        "Staff List Report",
        "Staff_List_Report.pdf"
        );
}
bool SignIn::loadCurrentUserAccountData()
{
    if (m_currentUserMail.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Profile", "No connected user found.");
        return false;
    }

    Personnel::AccountProfile acc;
    if (!Personnel::fetchAccountProfileByMail(m_currentUserMail, &acc)) {
        QMessageBox::critical(this, "Profile", "Unable to load account data.");
        return false;
    }

    m_currentUserId = acc.idPers;
    m_currentUserMail = acc.mail;
    m_currentAccountAvatar = acc.avatar;

    ui->staffnameedit_A->setText((acc.prenom + " " + acc.nom).trimmed());
    ui->staffaddressedit_A->setText(acc.adresse);
    ui->teledit_A->setText(acc.tel);
    ui->mailedit_A->setText(acc.mail);
    ui->passlab_A->clear();


    updateFaceIdStatusLabel();

    return true;
}

void SignIn::openCurrentUserAccountPage()
{
    if (loadCurrentUserAccountData()) {
        ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
    }
}

void SignIn::on_addstaffbtn_A_clicked()
{
    if (m_currentUserId < 0) {
        QMessageBox::warning(this, "Update account", "No connected user found.");
        return;
    }

    QString fullName = ui->staffnameedit_A->text().trimmed();
    QString adresse  = ui->staffaddressedit_A->text().trimmed();
    QString tel      = ui->teledit_A->text().trimmed();
    QString mail     = ui->mailedit_A->text().trimmed();
    QString newPass  = ui->passlab_A->text();

    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Full name is required.");
        return;
    }

    QRegularExpression reName("^[\\p{L}]+(?:\\s+[\\p{L}]+)*$");
    if (!reName.match(fullName).hasMatch()) {
        QMessageBox::warning(this,
                             "Invalid name",
                             "Full name must contain only letters and spaces.");
        ui->staffnameedit_A->setFocus();
        ui->staffnameedit_A->selectAll();
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Address is required.");
        return;
    }

    if (mail.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Mail is required.");
        return;
    }

    QRegularExpression reMail("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$");
    if (!reMail.match(mail).hasMatch()) {
        QMessageBox::warning(this, "Invalid email",
                             "Email must be like: name@example.com");
        ui->mailedit_A->setFocus();
        ui->mailedit_A->selectAll();
        return;
    }

    if (tel.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Phone number is required.");
        return;
    }

    QString telClean = tel;
    telClean.remove(' ');

    QRegularExpression reTel("^\\d{8}$");
    if (!reTel.match(telClean).hasMatch()) {
        QMessageBox::warning(this,
                             "Invalid phone number",
                             "The phone number should contain exactly 8 digits.\nExample: 22123456");
        ui->teledit_A->setFocus();
        ui->teledit_A->selectAll();
        return;
    }
    tel = telClean;

    if (!newPass.trimmed().isEmpty()) {
        QRegularExpression reMdp("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$");
        if (!reMdp.match(newPass).hasMatch()) {
            QMessageBox::warning(this,
                                 "Invalid password",
                                 "Password must be at least 8 characters and contain:\n"
                                 "- at least one uppercase letter\n"
                                 "- at least one lowercase letter\n"
                                 "- at least one number\n"
                                 "- at least one special character");
            ui->passlab_A->setFocus();
            ui->passlab_A->selectAll();
            return;
        }
    }

    auto rep = QMessageBox::question(
        this,
        "Confirm update",
        "Do you want to save your account changes?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (rep != QMessageBox::Yes)
        return;

    QStringList parts = fullName.split(' ', Qt::SkipEmptyParts);
    QString nom, prenom;

    if (parts.size() == 1) {
        nom = parts[0];
        prenom = "";
    } else {
        nom = parts.last();
        parts.removeLast();
        prenom = parts.join(" ");
    }

    if (!Personnel::updateOwnAccount(
            m_currentUserId,
            nom,
            prenom,
            adresse,
            tel,
            mail,
            newPass,
            m_currentAccountAvatar,
            true)) {
        QMessageBox::critical(this, "Error", "Failed to update your account.");
        return;
    }

    m_currentUserMail = mail;

    if (!loadCurrentUserAccountData()) {
        QMessageBox::warning(this, "Update account", "Account updated, but refresh failed.");
        return;
    }

    QString refreshedFullName = ui->staffnameedit_A->text().trimmed();
    updateUserProfileUI(refreshedFullName, m_currentAccountAvatar);

    refreshStaffTable();
    refreshStaffTable_U();

    QMessageBox::information(this, "Success", "Your account has been updated successfully.");
}


void SignIn::on_browbtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select your profile photo",
        QDir::homePath(),
        "Images (*.jpg *.jpeg *.png *.webp);;All files (*.*)"
        );

    if (filePath.isEmpty())
        return;

    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open image file.");
        return;
    }

    m_currentAccountAvatar = f.readAll();
    f.close();

    m_currentAvatarPath = filePath;

    if (ui->profile_A) {
        ui->profile_A->setText(QFileInfo(filePath).fileName());

    }


}
void SignIn::loadEmployeeCount()
{
    int total = Personnel::getTotalStaffCount();

    ui->numberstaff->setText(QString::number(total));
}
void SignIn::updateFaceIdStatusLabel()
{
    if (m_currentUserMail.trimmed().isEmpty()) {
        ui->registerlabel->setText("Face ID status: unknown");
        return;
    }

    const bool registered = Personnel::hasFaceIdRegistered(m_currentUserMail);

    if (registered) {
        ui->registerlabel->setText("Face ID status: Registered");
    } else {
        ui->registerlabel->setText("Face ID status: Not registered");
    }
}

void SignIn::on_facebtn_clicked()
{
    if (m_currentUserMail.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Face ID", "No connected user found.");
        return;
    }

    const QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Reset Face ID",
        "Are you sure you want to remove your registered Face ID?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes) {
        return;
    }

    if (!Personnel::removeFaceIdByMail(m_currentUserMail)) {
        QMessageBox::critical(this, "Face ID", "Failed to reset Face ID.");
        return;
    }

    updateFaceIdStatusLabel();
    QMessageBox::information(this, "Face ID", "Face ID has been removed successfully.");

}
QByteArray SignIn::captureFaceFromCamera()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        QMessageBox::warning(this, "Camera", "Unable to open the camera.");
        return QByteArray();
    }

    cv::Mat frame;
    cv::Mat capturedFrame;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            QMessageBox::warning(this, "Camera", "Failed to read frame from camera.");
            cap.release();
            cv::destroyAllWindows();
            return QByteArray();
        }

        cv::imshow("Face ID Camera - Press SPACE to capture / ESC to cancel", frame);

        int key = cv::waitKey(30);

        if (key == 32) {
            capturedFrame = frame.clone();
            break;
        } else if (key == 27) {
            cap.release();
            cv::destroyAllWindows();
            return QByteArray();
        }
    }

    cap.release();
    cv::destroyAllWindows();

    if (capturedFrame.empty()) {
        QMessageBox::warning(this, "Camera", "No image was captured.");
        return QByteArray();
    }

    cv::Mat face = detectAndCropFace(capturedFrame);
    if (face.empty()) {
        return QByteArray();
    }

    std::vector<uchar> buffer;
    if (!cv::imencode(".jpg", face, buffer)) {
        QMessageBox::warning(this, "Camera", "Failed to encode detected face.");
        return QByteArray();
    }

    return QByteArray(reinterpret_cast<const char*>(buffer.data()),
                      static_cast<int>(buffer.size()));
}
QString SignIn::ensureFaceCascadeFile()
{
    const QString tempPath = QDir::temp().filePath("haarcascade_frontalface_default.xml");

    if (QFile::exists(tempPath)) {
        return tempPath;
    }

    QFile resourceFile(":/haarcascade_frontalface_default.xml");
    if (!resourceFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Face ID", "Unable to open face cascade resource file.");
        return QString();
    }

    QFile tempFile(tempPath);
    if (!tempFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Face ID", "Unable to create temporary cascade file.");
        resourceFile.close();
        return QString();
    }

    tempFile.write(resourceFile.readAll());
    tempFile.close();
    resourceFile.close();

    return tempPath;
}

cv::Mat SignIn::detectAndCropFace(const cv::Mat& frame)
{
    QString cascadePath = ensureFaceCascadeFile();
    if (cascadePath.isEmpty()) {
        QMessageBox::warning(this, "Face ID", "Cascade path is empty.");
        return cv::Mat();
    }

    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(cascadePath.toStdString())) {
        QMessageBox::warning(this, "Face ID", "Failed to load face cascade.");
        return cv::Mat();
    }

    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(
        gray,
        faces,
        1.1,
        3,
        0,
        cv::Size(80, 80)
        );

    if (faces.empty()) {
        QMessageBox::warning(this, "Face ID", "No face detected.");
        return cv::Mat();
    }


    cv::Rect bestFace = faces[0];
    for (const auto& r : faces) {
        if (r.area() > bestFace.area()) {
            bestFace = r;
        }
    }

    cv::Mat face = frame(bestFace).clone();
    cv::resize(face, face, cv::Size(200, 200));

    return face;
}
double SignIn::compareFacesDistance(const cv::Mat& face1, const cv::Mat& face2)
{
    if (face1.empty() || face2.empty()) {
        return 1e12;
    }

    cv::Mat resized1, resized2;
    cv::resize(face1, resized1, cv::Size(200, 200));
    cv::resize(face2, resized2, cv::Size(200, 200));

    cv::Mat gray1, gray2;
    cv::cvtColor(resized1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(resized2, gray2, cv::COLOR_BGR2GRAY);

    cv::equalizeHist(gray1, gray1);
    cv::equalizeHist(gray2, gray2);

    return cv::norm(gray1, gray2, cv::NORM_L2);
}


bool SignIn::authenticateWithFaceId()
{
    QByteArray capturedData = captureFaceFromCamera();
    if (capturedData.isEmpty()) {
        registerFaceAuthFailure("No face captured");
        QMessageBox::warning(this, "Face ID", "No face captured.");
        return false;
    }

    std::vector<uchar> buffer(capturedData.begin(), capturedData.end());
    cv::Mat capturedFace = cv::imdecode(buffer, cv::IMREAD_COLOR);

    if (capturedFace.empty()) {
        registerFaceAuthFailure("Invalid face data");
        QMessageBox::warning(this, "Face ID", "Unable to decode captured face.");
        return false;
    }

    auto faces = Personnel::getAllRegisteredFaceIds();
    if (faces.isEmpty()) {
        QMessageBox::warning(this, "Face ID", "No registered Face ID found in database.");
        return false;
    }

    double bestDistance = 1e12;
    Personnel::FaceRecord bestRecord;
    bool foundCandidate = false;

    for (const auto& rec : faces) {
        std::vector<uchar> dbBuffer(rec.faceData.begin(), rec.faceData.end());
        cv::Mat dbFace = cv::imdecode(dbBuffer, cv::IMREAD_COLOR);

        if (dbFace.empty())
            continue;

        double distance = compareFacesDistance(capturedFace, dbFace);

        qDebug() << "Face ID compare with" << rec.mail << "distance =" << distance;

        if (distance < bestDistance) {
            bestDistance = distance;
            bestRecord = rec;
            foundCandidate = true;
        }
    }

    if (!foundCandidate) {
        registerFaceAuthFailure("No valid registered face found");
        QMessageBox::warning(this, "Face ID", "No valid registered face found.");
        return false;
    }

    qDebug() << "Best Face ID match =" << bestRecord.mail
             << "| distance =" << bestDistance;

    // seuil plus strict
    if (bestDistance > 30000.0) {
        registerFaceAuthFailure("Face not recognized");
        QMessageBox::warning(this, "Face ID", "Face ID not recognized.");
        return false;
    }

    QString authMail;
    QString authRole;
    QString authCvStatus;

    Personnel::FaceLoginResult result =
        Personnel::authenticateByFaceIdMail(bestRecord.mail, &authMail, &authRole, &authCvStatus);

    switch (result) {
    case Personnel::FaceLoginResult::Ok: {
        resetFaceAuthFailureCounter();

        m_currentUserMail = authMail;
        m_currentRole = authRole;

        Personnel::UserProfile profile;
        if (Personnel::fetchProfileByMail(authMail, &profile)) {
            m_currentUserId = profile.idPers;
            m_currentAccountAvatar = profile.avatar;
            updateUserProfileUI((profile.prenom + " " + profile.nom).trimmed(), profile.avatar);
        }

        applyRolePermissions(m_currentRole);
        loadCurrentUserAccountData();
        loadStaffDashboardStats();
        loadEmployeeCount();
        ui->stackedWidget->setCurrentWidget(ui->pageWelcome);

        QMessageBox::information(this, "Face ID", "Face recognized successfully.");
        return true;
    }

    case Personnel::FaceLoginResult::AccountBlocked:
        QMessageBox::critical(this, "Face ID",
                              "This account is temporarily blocked due to suspicious activity.");
        return false;

    case Personnel::FaceLoginResult::FaceNotEnabled:
        registerFaceAuthFailure("Face ID is disabled for this account");
        QMessageBox::warning(this, "Face ID", "Face ID is disabled for this account.");
        return false;

    case Personnel::FaceLoginResult::CvNotAccepted:
        QMessageBox::warning(this, "Face ID", "Your CV is not accepted. Access denied.");
        return false;

    case Personnel::FaceLoginResult::SuspiciousActivity:
        registerFaceAuthFailure("Suspicious Face ID activity");
        QMessageBox::warning(this, "Face ID", "Suspicious Face ID activity detected.");
        return false;

    case Personnel::FaceLoginResult::FaceNotRecognized:
        registerFaceAuthFailure("Face not recognized");
        QMessageBox::warning(this, "Face ID", "Face ID not recognized.");
        return false;

    case Personnel::FaceLoginResult::DbError:
        registerFaceAuthFailure("Database error during Face ID authentication");
        QMessageBox::critical(this, "Face ID", "Database error during Face ID authentication.");
        return false;
    }

    return false;
}

void SignIn::on_withfacebtn_clicked()
{
    authenticateWithFaceId();
}


QString SignIn::extractTextFromPdfBlob(const QByteArray& pdfBlob) const
{
    if (pdfBlob.isEmpty()) {
        return QString();
    }

    QBuffer buffer;
    buffer.setData(pdfBlob);
    if (!buffer.open(QIODevice::ReadOnly)) {
        return QString();
    }

    QPdfDocument doc;
    doc.load(&buffer);

    if (doc.status() != QPdfDocument::Status::Ready) {
        return QString();
    }

    QString fullText;
    const int pageCount = doc.pageCount();

    for (int i = 0; i < pageCount; ++i) {
        fullText += doc.getAllText(i).text();
        fullText += "\n";
    }

    fullText.replace(QRegularExpression(R"(\s+)"), " ");
    return fullText.simplified();
}

QStringList SignIn::generalCvKeywords() const
{
    return {
        "experience", "experiences",
        "project", "projects",
        "internship", "internships",
        "training", "formation",
        "skills", "skill",
        "certificate", "certification",
        "university", "bachelor", "master",
        "teamwork", "communication", "organization"
    };
}
QStringList SignIn::roleKeywords(const QString& role) const
{
    const QString r = role.trimmed().toLower();

    if (r == "admin") {
        return {
            "management", "manager", "leadership", "administration",
            "planning", "coordination", "reporting", "organization"
        };
    }
    if (r == "human resource") {
        return {
            "human resources", "hr", "recruitment", "interview",
            "onboarding", "training", "employee", "payroll"
        };
    }
    if (r == "an accountant") {
        return {
            "accounting", "accountant", "finance", "financial",
            "excel", "budget", "invoice", "audit", "bookkeeping"
        };
    }
    if (r == "regulatory manager") {
        return {
            "compliance", "regulation", "regulatory", "audit",
            "policy", "quality", "inspection", "certification"
        };
    }
    if (r == "fisherman") {
        return {
            "fishing", "boat", "sea", "net",
            "navigation", "marine", "port", "safety"
        };
    }
    if (r == "security") {
        return {
            "security", "surveillance", "patrol", "incident",
            "protection", "guard", "access control", "cctv"
        };
    }

    return {
        "experience", "project", "skill", "training",
        "university", "internship"
    };
}

SignIn::CvAnalysisResult SignIn::analyzeCvAdvanced(const QByteArray& cvBlob, const QString& role) const
{
    CvAnalysisResult result;

    const QString text = extractTextFromPdfBlob(cvBlob).toLower();
    const QStringList roleKws = roleKeywords(role);
    const QStringList generalKws = generalCvKeywords();

    if (text.trimmed().isEmpty()) {
        result.score = 0;
        result.decision = "Rejected";
        result.summary = "No readable text found in CV.";
        return result;
    }

    int score = 0;

    for (const QString& kw : roleKws) {
        if (text.contains(kw.toLower())) {
            result.matchedRoleKeywords << kw;
            score += 12;
        }
    }

    for (const QString& kw : generalKws) {
        if (text.contains(kw.toLower())) {
            result.matchedGeneralKeywords << kw;
            score += 4;
        }
    }

    if (text.contains("year") || text.contains("years")) {
        score += 8;
    }

    if (text.contains("assistant") || text.contains("manager") || text.contains("specialist")) {
        score += 6;
    }

    if (text.contains("responsible") || text.contains("managed") || text.contains("conducted")) {
        score += 6;
    }

    result.score = qMin(score, 100);

    if (result.score >= 60) {
        result.decision = "Accepted";
    } else {
        result.decision = "Rejected";
    }

    QString rolePart = result.matchedRoleKeywords.isEmpty()
                           ? "None"
                           : result.matchedRoleKeywords.join(", ");

    QString generalPart = result.matchedGeneralKeywords.isEmpty()
                              ? "None"
                              : result.matchedGeneralKeywords.join(", ");

    result.summary =
        "Score: " + QString::number(result.score) + "/100\n"
                                                    "Matched role keywords: " + rolePart + "\n"
                     "Matched general keywords: " + generalPart + "\n"
                        "Final decision: " + result.decision;

    return result;
}
void SignIn::runCvAnalysisForSelectedRow(QTableWidget *table)
{
    if (!table) {
        QMessageBox::warning(this, "AI CV analysis", "Staff table not found.");
        return;
    }

    const int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "AI CV analysis", "Please select a staff first.");
        return;
    }

    QTableWidgetItem *idItem = table->item(row, 0);
    if (!idItem) {
        QMessageBox::critical(this, "AI CV analysis", "Unable to read selected staff ID.");
        return;
    }

    bool ok = false;
    const int idPers = idItem->text().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "AI CV analysis", "Invalid staff ID.");
        return;
    }

    Personnel::CvAnalysisInput input;
    if (!Personnel::fetchCvAnalysisInputById(idPers, &input)) {
        QMessageBox::critical(this, "AI CV analysis", "Unable to load CV data from database.");
        return;
    }

    if (input.cvStatus.compare("Pending", Qt::CaseInsensitive) != 0) {
        QMessageBox::information(
            this,
            "AI CV analysis",
            "Only pending CVs can be analyzed.\nCurrent status: " + input.cvStatus
            );
        return;
    }

    if (input.cv.isEmpty()) {
        QMessageBox::warning(this, "AI CV analysis", "No CV file found for this staff.");
        return;
    }

    CvAnalysisResult result = analyzeCvAdvanced(input.cv, input.role);

    if (!Personnel::updateCvStatusById(idPers, result.decision)) {
        QMessageBox::critical(this, "AI CV analysis", "Unable to update CV status in database.");
        return;
    }

    refreshStaffTable();
    refreshStaffTable_U();
    loadStaffDashboardStats();
    loadEmployeeCount();

    showCvAnalysisDialog(input.fullName, input.role, result);
}
void SignIn::showCvAnalysisDialog(const QString& fullName,
                                  const QString& role,
                                  const CvAnalysisResult& result)
{
    QDialog dialog(this);
    dialog.setWindowTitle("AI CV Analysis Result");
    dialog.setFixedSize(520, 420);

    QString decisionColor = (result.decision == "Accepted") ? "#16A34A" : "#DC2626";
    QString scoreColor = (result.score >= 60) ? "#22C55E" : "#EF4444";

    dialog.setStyleSheet(R"(
        QDialog {
            background-color: #071826;
            border: 1px solid #1E90FF;
            border-radius: 16px;
        }
        QLabel {
            color: white;
            font-size: 14px;
        }
        QTextEdit {
            background-color: #0B2239;
            color: white;
            border: 1px solid #1E90FF;
            border-radius: 10px;
            padding: 8px;
            font-size: 13px;
        }
        QPushButton {
            background-color: #1D4ED8;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 10px 18px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #2563EB;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(12);

    QLabel *title = new QLabel("AI CV Analysis Result");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #38BDF8;");

    QLabel *nameLabel = new QLabel("Staff: " + fullName);
    nameLabel->setStyleSheet("font-size: 15px; font-weight: bold;");

    QLabel *roleLabel = new QLabel("Role: " + role);
    roleLabel->setStyleSheet("font-size: 15px;");

    QLabel *scoreLabel = new QLabel("Score: " + QString::number(result.score) + "/100");
    scoreLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: " + scoreColor + ";");

    QLabel *decisionLabel = new QLabel("Decision: " + result.decision);
    decisionLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: " + decisionColor + ";");

    QTextEdit *details = new QTextEdit;
    details->setReadOnly(true);
    details->setText(result.summary);

    QPushButton *closeBtn = new QPushButton("Close");
    connect(closeBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    mainLayout->addWidget(title);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(roleLabel);
    mainLayout->addWidget(scoreLabel);
    mainLayout->addWidget(decisionLabel);
    mainLayout->addWidget(details);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignCenter);

    dialog.exec();
}
void SignIn::registerFaceAuthFailure(const QString& reason)
{
    m_faceAuthFailureCount++;

    if (m_faceAuthFailureCount >= m_faceFraudThreshold) {
        showFaceFraudAlert(reason);
    }
}

void SignIn::resetFaceAuthFailureCounter()
{
    m_faceAuthFailureCount = 0;
}

void SignIn::showFaceFraudAlert(const QString& reason)
{
    QMessageBox::critical(
        this,
        "Face ID Fraud Detection",
        "Suspicious Face ID activity detected.\n\n"
        "Multiple failed Face ID attempts were recorded.\n"
        "Last reason: " + reason + "\n\n"
                       "Please verify the user identity before trying again."
        );
}
void SignIn::on_cvanalysebtn_clicked()
{
    runCvAnalysisForSelectedRow(ui->tablestaff);
}

void SignIn::on_cvanalysebtn_U_clicked()
{
    runCvAnalysisForSelectedRow(ui->tablestaff_U);
}
void SignIn::clearSignInForm(bool keepRememberedMail)
{
    if (!keepRememberedMail) {
        ui->UserNameEdit->clear();
    }

    ui->PasswordEdit->clear();

    if (!keepRememberedMail) {
        ui->remembercheck->setChecked(false);
    }

    ui->showPassCheck->setChecked(false);
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);
}

void SignIn::saveRememberedUser()
{
    QSettings settings("BORT", "SmartFishingPort");

    if (ui->remembercheck->isChecked()) {
        settings.setValue("rememberMe", true);
        settings.setValue("rememberedMail", ui->UserNameEdit->text().trimmed());
    } else {
        settings.setValue("rememberMe", false);
        settings.remove("rememberedMail");
    }
}

void SignIn::loadRememberedUser()
{
    QSettings settings("BORT", "SmartFishingPort");

    const bool remember = settings.value("rememberMe", false).toBool();
    const QString mail = settings.value("rememberedMail").toString();

    ui->remembercheck->setChecked(remember);

    if (remember && !mail.trimmed().isEmpty()) {
        ui->UserNameEdit->setText(mail);
        ui->PasswordEdit->clear();
        ui->UserNameEdit->setFocus();
    } else {
        ui->UserNameEdit->clear();
        ui->PasswordEdit->clear();
    }

    ui->showPassCheck->setChecked(false);
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);
}

void SignIn::on_staffmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}



void SignIn::on_staffmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}
void SignIn::loadEmployeeOfMonth()
{
    Personnel::EmployeeOfMonth emp;

    if (!Personnel::getEmployeeOfMonth(&emp)) {
        if (ui->namebest)
            ui->namebest->setText("No employee available");
        if (ui->rolebest)
            ui->rolebest->setText("Role: -");
        if (ui->rewardbest)
            ui->rewardbest->setText("Reward: -");
        if (ui->bestEmployeeAvatar)
            ui->bestEmployeeAvatar->clear();

        return;
    }

    if (ui->titlebest) {
        ui->titlebest->setText("Best Employee of this month");
    }

    if (ui->namebest) {
        ui->namebest->setText("Full Name: " + emp.fullName);
    }

    if (ui->rolebest) {
        ui->rolebest->setText("Role: " + emp.role);
    }

    if (ui->rewardbest) {
        ui->rewardbest->setText("Reward: 100dt");
    }

    if (ui->bestEmployeeAvatar) {
        QPixmap px;
        px.loadFromData(emp.avatar);

        if (!px.isNull()) {
            ui->bestEmployeeAvatar->setPixmap(
                px.scaled(ui->bestEmployeeAvatar->size(),
                          Qt::KeepAspectRatio,
                          Qt::SmoothTransformation)
                );
            ui->bestEmployeeAvatar->setAlignment(Qt::AlignCenter);
        } else {
            ui->bestEmployeeAvatar->clear();
        }
    }
}
