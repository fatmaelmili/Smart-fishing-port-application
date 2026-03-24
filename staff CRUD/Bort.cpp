#include "Bort.h"
#include "ui_Bort.h"
#include "personnel.h"
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
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    refreshStaffTable();
    refreshStaffTable_U();
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

    Personnel p;
    QVector<QStringList> rows = p.getStaffRows();

    ui->tablestaff->setRowCount(rows.size());

    for (int r = 0; r < rows.size(); ++r) {
        for (int c = 0; c < headers.size(); ++c) {
            QTableWidgetItem *item = new QTableWidgetItem(rows[r][c]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // read-only
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
        updateUserProfileUI(fullName, prof.avatar);
    }
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
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
}


void SignIn::on_staticbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backWbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);

}


void SignIn::on_staticbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_modifystaffbtn_clicked()
{
    refreshStaffTable_U();
    ui->stackedWidget->setCurrentWidget(ui->pageupdate);

}


void SignIn::on_logOutBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backWbtn_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_userprofiledetails_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}




void SignIn::on_userprofiledetails_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_staffmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_logOutBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_Z_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_fishingzonemanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
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
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_fishingzonemanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_stock_clicked()
{
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
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_backWbtnE_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
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
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofileC_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
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
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
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

    Personnel p;
    QVector<QStringList> rows = p.getStaffRows();

    ui->tablestaff_U->setRowCount(rows.size());

    for (int r = 0; r < rows.size(); ++r) {
        for (int c = 0; c < headers.size(); ++c) {
            auto *item = new QTableWidgetItem(rows[r][c]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablestaff_U->setItem(r, c, item);
        }
    }

    ui->tablestaff_U->setColumnHidden(0, true);
    ui->tablestaff_U->resizeColumnsToContents();
}


void SignIn::on_tablestaff_U_itemSelectionChanged()
{
    int row = ui->tablestaff_U->currentRow();
    if (row < 0) return;


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
        refreshStaffTable_U();
        refreshStaffTable();
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
                if (lab->objectName().startsWith("avatar")) {
                    lab->setPixmap(px.scaled(lab->size(),
                                             Qt::KeepAspectRatioByExpanding,
                                             Qt::SmoothTransformation));
                    lab->setScaledContents(true);
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

    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backsigninBTNR_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_showPassCheckR_toggled(bool checked)
{
    ui->NewEdit->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}

