#include "Bort.h"
#include "ui_Bort.h"
#include "personnel.h"
#include "zonepech.h"
#include "client.h"
#include "editclientdialog.h"
#include "stock.h"
#include "equipment.h"
#include "chatbotdialog.h"
#include "predictiondialog.h"
#include "vesselstatsdialog.h"
#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif
#include <QSerialPort>
#include <QRegularExpression>
#include <cstring>
#include <cmath>
#include <QBuffer>
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
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
#include <QTextDocument>
#include <QPageSize>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QPageLayout>
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
#include <QSqlError>
#include <QSortFilterProxyModel>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <QWidget>
#include <QUrl>
#include <QCoreApplication>
#include <QDebug>
#include <QtCore/QBuffer>
#include <QtCore/QIODevice>
#include <QBuffer>
#include<QStyle>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QFileInfo>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QVBoxLayout>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRandomGenerator>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlQuery>
#include <QDateTime>
#include <QBuffer>
#include <QPdfDocument>
#include <QRegularExpression>
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
#include <QTextDocument>
#include <QPageSize>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QPageLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFontMetrics>
#include <QtCore/QBuffer>
#include <QtCore/QIODevice>
#include <QTextOption>
#include <QSet>
#include <QTemporaryFile>
#include <QRegularExpression>
#include <QSet>
#include <QPdfDocument>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QSettings>
#include <QSqlError>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
//nour
#include <QAbstractItemView>
#include <QDateTime>
#include <QDialog>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPageLayout>
#include <QPainter>
#include <QPdfWriter>
#include <QScrollBar>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <algorithm>
#include <QInputDialog>
#include <QVector>
#include <algorithm>
#include <QToolTip>
#include <QtCharts/QLineSeries>

SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    //fatma
    ui->setupUi(this);
    initArduinoConnection();
    setupAccessHistoryTable();
    ui->statrole->hide();
    ui->statcv->hide();
    refreshStaffTable();
    refreshStaffTable_U();

    //dhia
    loadZonesToTable();
    //fatma
    loadStaffDashboardStats();
    loadRememberedUser();
    loadEmployeeOfMonth();
    //sana
    loadClients("", "");
    loadItems();
    //added this
        qDebug() << "Constructor START";
        connect(ui->pdfitembtn, &QPushButton::clicked,
                this, &SignIn::on_pdfitembtn_clicked);
        connect(ui->vocalstuffbtn, &QPushButton::clicked,
                this, &SignIn::on_vocalstuffbtn_clicked);
        loadClients("", "");
        loadItems();
        //added this(elli louta lkoll)
        loadClientsFromDB();
        setupBarChart();
        setupPieChart();
        updateDashboard();
        qDebug() << "Constructor END";

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
    //dhia
    connect(ui->ZoneSearch, &QLineEdit::textChanged,
            this, &SignIn::loadZonesToTable);
    connect(ui->sortzone, &QComboBox::currentTextChanged,
            this, &SignIn::loadZonesToTable);
    //malik
    Stock s;
    QSqlQueryModel* model = s.afficher();

    ui->table_stock->setModel(model);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ui->table_stock->model());
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->table_stock->setModel(proxyModel);

    // 🔥 FORCE DISPLAY FIXES
    ui->table_stock->resizeColumnsToContents();
    ui->table_stock->horizontalHeader()->setStretchLastSection(true);
    ui->table_stock->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_stock->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //nour
    setupFormWidgets();
    setupTableStyle();
    setupSearchBar();
    setupSortCombo();
    setupButtonStyles();
    setupNavHighlight();

    // ── FIX RESIZE : SizePolicy Expanding sur les pages et le stackedWidget ──
        // Sans cela, Qt ne redistribue pas l'espace disponible lors du resize.
        auto expandPolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if (ui->pageEquipmentForm) ui->pageEquipmentForm->setSizePolicy(expandPolicy);
        if (ui->pageEquipmentList) ui->pageEquipmentList->setSizePolicy(expandPolicy);
        if (ui->stackedWidget)     ui->stackedWidget->setSizePolicy(expandPolicy);
        // ── Navigation ────────────────────────────────────────────────────────────
           auto goForm = [this]() {
               ui->stackedWidget->setCurrentWidget(ui->pageEquipmentForm);
           };
           connect(ui->equipmentmanagementBTN_W,  &QPushButton::clicked, this, goForm);
           connect(ui->equipmentmanagementBTN_D,  &QPushButton::clicked, this, goForm);
           connect(ui->equipmentmanagementBTNe_F, &QPushButton::clicked, this, goForm);
           connect(ui->equipmentmanagementBTNe_L, &QPushButton::clicked, this, goForm);

           connect(ui->goToListBtnE, &QPushButton::clicked, this, [this]() {
               loadEquipmentList();
               ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
           });

           connect(ui->goToFormBtnE, &QPushButton::clicked, this, [this]() {
               ui->stackedWidget->setCurrentWidget(ui->pageEquipmentForm);
           });



           // ── Equipment actions ─────────────────────────────────────────────────────
           connect(ui->addEqbtn_F,      &QPushButton::clicked, this, &SignIn::on_addEqbtn_F_clicked);
           connect(ui->exportpdfbtnE_L, &QPushButton::clicked, this, &SignIn::on_exportpdfbtnE_L_clicked);

           connect(ui->chatbotbtn_L, &QPushButton::clicked, this, [this]() {
               ChatBotDialog dlg(this);
               dlg.exec();
           });

           connect(ui->chatbotbtn_2_L, &QPushButton::clicked, this, [this]() {
               PredictionDialog dlg(this);
               dlg.exec();
           });

           connect(ui->staticbtnE_L, &QPushButton::clicked, this, [this]() {
               VesselStatsDialog dlg(this);
               dlg.exec();
           });

           connect(ui->searchbar_L, &QLineEdit::textChanged,
                   this, &SignIn::filterAndSortTable);

           connect(ui->sortEq_L, QOverload<int>::of(&QComboBox::currentIndexChanged),
                   this, &SignIn::filterAndSortTable);

           loadEquipmentList();
           //ARDUINO MALIK ET DHIA




}
//APRESINTEGRATION
QString SignIn::extractAvatarInitials(const QString& fullName) const
{
    QString cleaned = fullName.trimmed();
    if (cleaned.isEmpty()) {
        return "";
    }

    QStringList parts = cleaned.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.isEmpty()) {
        return "";
    }

    QString initials;

    if (parts.size() >= 2) {
        initials += parts.first().left(1).toUpper();
        initials += parts.last().left(1).toUpper();
    } else {
        QString one = parts.first().trimmed();
        initials = one.left(2).toUpper();
    }

    return initials;
}

QColor SignIn::avatarColorFromName(const QString& fullName) const
{
    const QString name = fullName.trimmed().toUpper();

    if (name.isEmpty()) {
        return QColor("#1E3A8A");
    }

    uint hash = 0;
    for (QChar ch : name) {
        hash = (hash * 31u) + ch.unicode();
    }

    QList<QColor> palette = {
        QColor("#0F4C81"),
        QColor("#1565C0"),
        QColor("#1D4ED8"),
        QColor("#0EA5E9"),
        QColor("#0891B2"),
        QColor("#0284C7"),
        QColor("#0369A1"),
        QColor("#1E40AF")
    };

    return palette[int(hash % uint(palette.size()))];
}

QByteArray SignIn::generateInitialsAvatar(const QString& fullName, int size) const
{
    const QString initials = extractAvatarInitials(fullName);
    if (initials.isEmpty()) {
        return QByteArray();
    }

    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QRect rect(0, 0, size, size);

    QColor baseColor = avatarColorFromName(fullName);

    QLinearGradient gradient(0, 0, size, size);
    gradient.setColorAt(0.0, baseColor.lighter(120));
    gradient.setColorAt(1.0, baseColor.darker(125));

    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawEllipse(rect.adjusted(6, 6, -6, -6));

    QPen borderPen(QColor("#38BDF8"));
    borderPen.setWidth(4);
    painter.setPen(borderPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(rect.adjusted(6, 6, -6, -6));

    QFont font("Segoe UI", size / 3, QFont::Bold);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(rect, Qt::AlignCenter, initials);

    painter.end();

    QByteArray bytes;
    QBuffer buffer(&bytes);
    if (!buffer.open(QIODevice::WriteOnly)) {
        return QByteArray();
    }

    pixmap.save(&buffer, "PNG");
    return bytes;
}

void SignIn::generateAvatarForAddStaff()
{
    const QString fullName = ui->staffnameedit->text().trimmed();

    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Avatar", "Please enter the full name first.");
        ui->staffnameedit->setFocus();
        return;
    }

    const QByteArray avatarBytes = generateInitialsAvatar(fullName);
    if (avatarBytes.isEmpty()) {
        QMessageBox::warning(this, "Avatar", "Avatar generation failed.");
        return;
    }

    m_avatarBlob = avatarBytes;
    ui->avatarpathEdit->setText("Generated avatar: " + extractAvatarInitials(fullName));
}

void SignIn::generateAvatarForUpdateStaff()
{
    const QString fullName = ui->staffnameedit_U->text().trimmed();

    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Avatar", "Please enter the full name first.");
        ui->staffnameedit_U->setFocus();
        return;
    }

    const QByteArray avatarBytes = generateInitialsAvatar(fullName);
    if (avatarBytes.isEmpty()) {
        QMessageBox::warning(this, "Avatar", "Avatar generation failed.");
        return;
    }

    m_avatarBlob = avatarBytes;
    ui->avatarpathEdit_U->setText("Generated avatar: " + extractAvatarInitials(fullName));
}
QLabel* SignIn::ensureBestEmployeeHoursLabel()
{
    QLabel *hoursLabel = ui->staffdash->findChild<QLabel*>("hoursbest");
    if (hoursLabel) {
        return hoursLabel;
    }

    QWidget *parentCard = ui->beststaff ? ui->beststaff : ui->staffdash;
    if (!parentCard) {
        return nullptr;
    }

    hoursLabel = new QLabel(parentCard);
    hoursLabel->setObjectName("hoursbest");
    hoursLabel->setGeometry(230, 122, 300, 28);
    hoursLabel->setText("Worked Time: 0h 00m");
    hoursLabel->setStyleSheet(R"(
        QLabel {
            color: #CFEFFF;
            font-size: 15px;
            font-weight: 600;
            background: transparent;
        }
    )");
    hoursLabel->show();
    return hoursLabel;
}

QString SignIn::formatDurationEnglish(qint64 totalSeconds) const
{
    if (totalSeconds < 0) {
        totalSeconds = 0;
    }

    const qint64 hours = totalSeconds / 3600;
    const qint64 minutes = (totalSeconds % 3600) / 60;
    const qint64 seconds = totalSeconds % 60;

    if (hours > 0) {
        return QString("%1h %2m %3s")
        .arg(hours)
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    }

    return QString("%1m %2s")
        .arg(minutes)
        .arg(seconds, 2, 10, QChar('0'));
}

bool SignIn::beginSessionForCurrentUser()
{
    qDebug() << "beginSessionForCurrentUser m_currentUserMail =" << m_currentUserMail;

    if (m_currentUserMail.trimmed().isEmpty()) {
        return false;
    }

    if (!Personnel::startUserSessionByMail(m_currentUserMail)) {
        QMessageBox::warning(this,
                             "Session",
                             "Connected successfully, but the work session could not be started.");
        return false;
    }

    return true;
}

void SignIn::showStyledSessionLogoutMessage(const QString& fullName, qint64 sessionSeconds)
{
    QMessageBox box(this);
    box.setIcon(QMessageBox::Information);
    box.setWindowTitle("Session Summary");
    box.setTextFormat(Qt::RichText);
    box.setStandardButtons(QMessageBox::Ok);
    box.setDefaultButton(QMessageBox::Ok);

    const QString displayName = fullName.trimmed().isEmpty() ? "User" : fullName.trimmed();
    const QString formattedDuration = formatDurationEnglish(sessionSeconds);

    box.setText(
        "<div style='color:#EAF7FF; font-size:18px; font-weight:700; margin-bottom:6px;'>"
        "Goodbye, " + displayName.toHtmlEscaped() + "!"
                                        "</div>"
                                        "<div style='color:#BFE7FF; font-size:14px; margin-bottom:10px;'>"
                                        "See you next time."
                                        "</div>"
                                        "<div style='color:#FFFFFF; font-size:13px;'>"
                                        "You spent <span style='color:#22C55E; font-weight:700;'>" + formattedDuration.toHtmlEscaped() + "</span> "
                                              "in your account during this session."
                                              "</div>"
        );

    box.setStyleSheet(R"(
        QMessageBox {
            background-color: #08233C;
        }
        QMessageBox QLabel {
            color: white;
            min-width: 360px;
        }
        QMessageBox QPushButton {
            background-color: #0EA5E9;
            color: white;
            border: 1px solid #38BDF8;
            border-radius: 10px;
            padding: 8px 18px;
            min-width: 90px;
            font-weight: 700;
        }
        QMessageBox QPushButton:hover {
            background-color: #38BDF8;
        }
    )");

    box.exec();
}

void SignIn::performLogoutFlow()
{
    QString fullName = "User";

    if (!m_currentUserMail.trimmed().isEmpty()) {
        Personnel::UserProfile profile;
        if (Personnel::fetchProfileByMail(m_currentUserMail, &profile)) {
            fullName = (profile.prenom + " " + profile.nom).trimmed();
            if (fullName.isEmpty()) {
                fullName = profile.nom.trimmed();
            }
        }
    }

    qDebug() << "performLogoutFlow m_currentUserMail =" << m_currentUserMail;

    qint64 sessionSeconds = 0;
    qint64 monthlyTotal = 0;
    qDebug() << "performLogoutFlow m_currentUserMail =" << m_currentUserMail;

    const bool ok = Personnel::closeUserSessionByMail(
        m_currentUserMail,
        &sessionSeconds,
        &monthlyTotal
        );

    qDebug() << "close session ok =" << ok;
    qDebug() << "sessionSeconds =" << sessionSeconds;
    qDebug() << "monthlyTotal =" << monthlyTotal;

    if (ok) {
        showStyledSessionLogoutMessage(fullName, sessionSeconds);
    } else {
        QMessageBox::warning(this,
                             "Logout",
                             "The session could not be closed correctly.");
    }

    m_currentUserMail.clear();
    m_currentRole.clear();
    m_currentUserId = -1;
    m_currentAccountAvatar.clear();
    loadRememberedUser();
    loadEmployeeOfMonth();
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
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
    A.close_arduino();
    delete ui;
}




void SignIn::on_btnForgetmdp_clicked()
{
    ui->resetlineEdit->clear();
    ui->resetlabel->clear();
    ui->stackedWidget->setCurrentWidget(ui->pageForgetpass);
    ui->resetlineEdit->setFocus();
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
    generateAvatarForAddStaff();
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
        updateUserProfileUI(fullName, role, prof.avatar);
        beginSessionForCurrentUser();

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
    performLogoutFlow();
}


void SignIn::on_logOutBTN_U_clicked()
{
    performLogoutFlow();
}


void SignIn::on_logOutBTN_D_clicked()
{
    performLogoutFlow();
}


void SignIn::on_logOutBTN_clicked()
{
    performLogoutFlow();
}


void SignIn::on_logOutBTN_A_clicked()
{
    performLogoutFlow();
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
    performLogoutFlow();
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
    performLogoutFlow();
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
    performLogoutFlow();
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
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_equipmentmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
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
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_fishingzonemanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTNA_clicked()
{
    performLogoutFlow();
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
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_fishingzonemanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_DC_clicked()
{
    performLogoutFlow();
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
                             "Please generate an avatar image before adding staff.");
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
                             "Please generate an avatar image before updating staff.");
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
    generateAvatarForUpdateStaff();

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
void SignIn::updateUserProfileUI(const QString& fullName, const QString& role, const QByteArray& avatarBytes)
{
    const auto profileBtns = this->findChildren<QCommandLinkButton*>();
    for (QCommandLinkButton* btn : profileBtns) {
        if (!btn) continue;

        if (btn->objectName().startsWith("userprofiledetails")) {
            btn->setText(fullName);
            btn->setDescription(role);

            btn->setStyleSheet(R"(
                QCommandLinkButton {
                    color: white;
                    font-size: 10px;
                    font-weight: 700;
                    text-align: left;
                    background: transparent;
                    border: none;
                }
                QCommandLinkButton::description {
                    color: #9CCBFF;
                    font-size: 7px;
                    font-weight: 500;
                }
            )");
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
    m_currentRole = acc.role;
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
    updateUserProfileUI(refreshedFullName, m_currentRole, m_currentAccountAvatar);

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
#ifndef USE_OPENCV
    QMessageBox::warning(this, "Face ID", "OpenCV is not enabled in this build.");
    return QByteArray();
#else
    try {
        cv::VideoCapture cap(0, cv::CAP_DSHOW);

        if (!cap.isOpened()) {
            QMessageBox::warning(this, "Camera", "Unable to open the camera.");
            return QByteArray();
        }

        QMessageBox::information(this, "Face ID",
                                 "Look at the camera. Capture will be automatic.");

        cv::Mat frame;
        cv::Mat capturedFrame;

        for (int i = 0; i < 20; ++i) {
            if (!cap.read(frame)) {
                QMessageBox::warning(this, "Camera", "Failed to read frame from camera.");
                cap.release();
                return QByteArray();
            }
            cv::waitKey(30);
        }

        capturedFrame = frame.clone();
        cap.release();

        if (capturedFrame.empty()) {
            QMessageBox::warning(this, "Camera", "Captured frame is empty.");
            return QByteArray();
        }

        cv::Mat face = detectAndCropFace(capturedFrame);

        if (face.empty()) {
            QMessageBox::warning(this, "Face ID",
                                 "No person or no clear face was detected. Please look directly at the camera.");
            return QByteArray();
        }

        std::vector<uchar> buffer;
        if (!cv::imencode(".jpg", face, buffer)) {
            QMessageBox::warning(this, "Camera", "Failed to encode detected face.");
            return QByteArray();
        }

        QByteArray result;
        result.resize(static_cast<int>(buffer.size()));
        memcpy(result.data(), buffer.data(), static_cast<size_t>(buffer.size()));
        return result;
    }
    catch (const cv::Exception& e) {
        QMessageBox::critical(this, "OpenCV Exception", e.what());
        return QByteArray();
    }
    catch (...) {
        QMessageBox::critical(this, "Camera", "Unexpected crash during camera capture.");
        return QByteArray();
    }
#endif
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

#ifdef USE_OPENCV
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
#endif
#ifdef USE_OPENCV
static cv::Mat makeGray200(const cv::Mat& src)
{
    if (src.empty())
        return cv::Mat();

    cv::Mat resized;
    cv::resize(src, resized, cv::Size(200, 200));

    cv::Mat gray;
    if (resized.channels() == 3) {
        cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    } else if (resized.channels() == 4) {
        cv::cvtColor(resized, gray, cv::COLOR_BGRA2GRAY);
    } else if (resized.channels() == 1) {
        gray = resized.clone();
    } else {
        return cv::Mat();
    }

    return gray;
}

static double computeFaceDistanceSafe(const cv::Mat& a, const cv::Mat& b)
{
    cv::Mat g1 = makeGray200(a);
    cv::Mat g2 = makeGray200(b);

    if (g1.empty() || g2.empty())
        return 1e12;

    double sum = 0.0;

    for (int y = 0; y < g1.rows; ++y) {
        const uchar* p1 = g1.ptr<uchar>(y);
        const uchar* p2 = g2.ptr<uchar>(y);

        for (int x = 0; x < g1.cols; ++x) {
            sum += std::abs(int(p1[x]) - int(p2[x]));
        }
    }

    return sum / (g1.rows * g1.cols);
}
#endif
#ifdef USE_OPENCV
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
#endif


bool SignIn::authenticateWithFaceId()
{
#ifndef USE_OPENCV
    QMessageBox::warning(this, "Face ID", "OpenCV is not enabled in this build.");
    return false;
#else
    cv::setUseOptimized(false);

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

        double distance = computeFaceDistanceSafe(capturedFace, dbFace);
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
            updateUserProfileUI((profile.prenom + " " + profile.nom).trimmed(), authRole, profile.avatar);
        }

        applyRolePermissions(m_currentRole);
        beginSessionForCurrentUser();
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
#endif
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
    QLabel *hoursLabel = ensureBestEmployeeHoursLabel();

    if (!Personnel::getEmployeeOfMonth(&emp)) {
        if (ui->namebest)
            ui->namebest->setText("No employee available");
        if (ui->rolebest)
            ui->rolebest->setText("Role: -");
        if (hoursLabel)
            hoursLabel->setText("Worked Time: -");
        if (ui->rewardbest)
            ui->rewardbest->setText("Reward: -");
        if (ui->bestEmployeeAvatar)
            ui->bestEmployeeAvatar->clear();

        return;
    }

    if (ui->beststaff) {
        ui->beststaff->setStyleSheet(R"(
            QFrame#beststaff {
                background:qlineargradient(x1:0,y1:0,x2:1,y2:1,
                    stop:0 rgba(5,28,51,0.96),
                    stop:1 rgba(8,50,88,0.90));
                border:1px solid rgba(56,189,248,0.55);
                border-radius:22px;
            }
        )");
    }

    if (ui->titlebest) {
        ui->titlebest->setText("Best Employee of this Month");
        ui->titlebest->setStyleSheet("color:#F8FAFC; font-size:17px; font-weight:600; background:transparent;");
    }

    if (ui->namebest) {
        ui->namebest->setText("Full Name: " + emp.fullName);
        ui->namebest->setStyleSheet("color:#FFFFFF; font-size:12px; font-weight:400; background:transparent;");
    }

    if (ui->rolebest) {
        ui->rolebest->setText("Role: " + emp.role);
        ui->rolebest->setStyleSheet("color:#CDEBFF; font-size:10px; font-weight:400; background:transparent;");
    }

    if (hoursLabel) {
        hoursLabel->setText("Worked Time: " + formatDurationEnglish(emp.monthlyWorkSeconds));
    }

    if (ui->rewardbest) {
        ui->rewardbest->setText("Reward: 100dt");
        ui->rewardbest->setStyleSheet("color:#22C55E; font-size:10px; font-weight:400; background:transparent;");
    }

    if (ui->bestEmployeeAvatar) {
        ui->bestEmployeeAvatar->setStyleSheet(R"(
        QLabel {
            background-color: rgba(255,255,255,0.05);
            border: 2px solid #38BDF8;
            border-radius: 40px;
            padding: 0px;
        }
    )");

        QPixmap px;
        px.loadFromData(emp.avatar);

        if (!px.isNull()) {
            const QSize labelSize = ui->bestEmployeeAvatar->size();
            QPixmap scaled = px.scaled(labelSize,
                                       Qt::KeepAspectRatioByExpanding,
                                       Qt::SmoothTransformation);

            QPixmap rounded(labelSize);
            rounded.fill(Qt::transparent);

            QPainter painter(&rounded);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

            QPainterPath path;
            path.addRoundedRect(rounded.rect(), 40, 40);
            painter.setClipPath(path);

            const int x = (labelSize.width() - scaled.width()) / 2;
            const int y = (labelSize.height() - scaled.height()) / 2;
            painter.drawPixmap(x, y, scaled);

            ui->bestEmployeeAvatar->setPixmap(rounded);
            ui->bestEmployeeAvatar->setAlignment(Qt::AlignCenter);
        } else {
            ui->bestEmployeeAvatar->clear();
        }
    }
}
QByteArray SignIn::captureVoiceFromMicrophone(int durationMs)
{
    QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
    if (inputDevice.isNull()) {
        QMessageBox::warning(this, "Voice ID", "No microphone detected.");
        return QByteArray();
    }

    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    if (!inputDevice.isFormatSupported(format)) {
        format = inputDevice.preferredFormat();
    }

    m_lastVoiceFormat = format;

    QByteArray recorded;
    QBuffer buffer(&recorded);
    buffer.open(QIODevice::WriteOnly);

    QAudioSource audioSource(inputDevice, format, this);

    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    audioSource.start(&buffer);
    timer.start(durationMs);
    loop.exec();

    audioSource.stop();
    buffer.close();

    if (recorded.isEmpty()) {
        QMessageBox::warning(this, "Voice ID", "No voice captured.");
        return QByteArray();
    }

    return recorded;
}
QVector<double> SignIn::pcm16ToSamples(const QByteArray& audioBytes, const QAudioFormat& format) const
{
    QVector<double> samples;

    if (audioBytes.isEmpty()) {
        return samples;
    }

    if (format.sampleFormat() == QAudioFormat::Int16) {
        const qint16* data = reinterpret_cast<const qint16*>(audioBytes.constData());
        const int count = audioBytes.size() / int(sizeof(qint16));
        samples.reserve(count);

        for (int i = 0; i < count; ++i) {
            samples.push_back(double(data[i]) / 32768.0);
        }
    }
    else if (format.sampleFormat() == QAudioFormat::Float) {
        const float* data = reinterpret_cast<const float*>(audioBytes.constData());
        const int count = audioBytes.size() / int(sizeof(float));
        samples.reserve(count);

        for (int i = 0; i < count; ++i) {
            samples.push_back(double(data[i]));
        }
    }

    return samples;
}

QVector<double> SignIn::extractVoiceFeatures(const QByteArray& audioBytes, const QAudioFormat& format) const
{
    QVector<double> samples = pcm16ToSamples(audioBytes, format);
    QVector<double> features;

    if (samples.isEmpty()) {
        return features;
    }


    double mean = 0.0;
    for (double s : samples) mean += s;
    mean /= samples.size();
    for (double& s : samples) s -= mean;


    QVector<double> trimmed;
    for (double s : samples) {
        if (qAbs(s) > 0.02) {
            trimmed.push_back(s);
        }
    }
    if (trimmed.size() > 4000) {
        samples = trimmed;
    }


    double rms = 0.0;
    for (double s : samples) rms += s * s;
    rms = qSqrt(rms / qMax(1, samples.size()));

    if (rms > 1e-9) {
        for (double& s : samples) s /= rms;
    }


    const int bins = 64;
    features.reserve(80);

    for (int b = 0; b < bins; ++b) {
        int start = (b * samples.size()) / bins;
        int end   = ((b + 1) * samples.size()) / bins;
        if (end <= start) end = start + 1;
        if (end > samples.size()) end = samples.size();

        double acc = 0.0;
        for (int i = start; i < end; ++i) {
            acc += qAbs(samples[i]);
        }
        acc /= qMax(1, end - start);
        features.push_back(acc);
    }


    double zcr = 0.0;
    for (int i = 1; i < samples.size(); ++i) {
        if ((samples[i - 1] >= 0.0 && samples[i] < 0.0) ||
            (samples[i - 1] < 0.0 && samples[i] >= 0.0)) {
            zcr += 1.0;
        }
    }
    zcr /= qMax(1, samples.size() - 1);
    features.push_back(zcr);


    QList<int> lags = {40, 60, 80, 100, 120, 140, 160, 180};
    for (int lag : lags) {
        if (samples.size() <= lag + 1) {
            features.push_back(0.0);
            continue;
        }

        double num = 0.0;
        double den1 = 0.0;
        double den2 = 0.0;

        for (int i = 0; i < samples.size() - lag; ++i) {
            num  += samples[i] * samples[i + lag];
            den1 += samples[i] * samples[i];
            den2 += samples[i + lag] * samples[i + lag];
        }

        double corr = 0.0;
        if (den1 > 1e-9 && den2 > 1e-9) {
            corr = num / qSqrt(den1 * den2);
        }

        features.push_back(corr);
    }

    return features;
}

QString SignIn::voiceFeaturesToJson(const QVector<double>& features) const
{
    QJsonArray arr;
    for (double v : features) {
        arr.append(v);
    }
    return QString::fromUtf8(QJsonDocument(arr).toJson(QJsonDocument::Compact));
}

QVector<double> SignIn::jsonToVoiceFeatures(const QString& json) const
{
    QVector<double> out;
    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isArray()) {
        return out;
    }

    const QJsonArray arr = doc.array();
    out.reserve(arr.size());
    for (const auto& v : arr) {
        out.push_back(v.toDouble());
    }

    return out;
}

double SignIn::compareVoiceFeatures(const QVector<double>& a, const QVector<double>& b) const
{
    if (a.isEmpty() || b.isEmpty() || a.size() != b.size()) {
        return 0.0;
    }

    double dot = 0.0;
    double na = 0.0;
    double nb = 0.0;

    for (int i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        na += a[i] * a[i];
        nb += b[i] * b[i];
    }

    if (na <= 1e-12 || nb <= 1e-12) {
        return 0.0;
    }

    return dot / qSqrt(na * nb);
}

void SignIn::on_Voicebtn_clicked()
{
    if (m_currentUserMail.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Voice ID", "No connected user found.");
        return;
    }

    Personnel::AccountProfile profile;
    if (!Personnel::fetchAccountProfileByMail(m_currentUserMail, &profile)) {
        QMessageBox::warning(this, "Voice ID", "Unable to load current user profile.");
        return;
    }

    if (profile.cvStatus.trimmed().compare("Accepted", Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, "Voice ID", "Only users with an accepted CV can register Voice ID.");
        return;
    }

    const QString phrase = "BORT smart fishing port";
    QMessageBox::information(this, "Voice ID",
                             "Please say clearly:\n\n" + phrase + "\n\nfor about 3 seconds.");

    QByteArray voiceData = captureVoiceFromMicrophone(3000);
    if (voiceData.isEmpty()) {
        return;
    }

    QVector<double> features = extractVoiceFeatures(voiceData, m_lastVoiceFormat);
    if (features.isEmpty()) {
        QMessageBox::warning(this, "Voice ID", "Voice features extraction failed.");
        return;
    }

    if (!Personnel::saveVoiceIdByMail(
            m_currentUserMail,
            voiceData,
            voiceFeaturesToJson(features),
            phrase)) {
        QMessageBox::critical(this, "Voice ID", "Failed to save Voice ID.");
        return;
    }
    ui->voicelabel->setText("Voice ID status: Registered");

    QMessageBox::information(this, "Voice ID", "Voice ID registered successfully.");

}


bool SignIn::authenticateWithVoiceId()
{
    const QString phrase = "BORT smart fishing port";
    QMessageBox::information(this, "Voice Sign In",
                             "Please say clearly:\n\n" + phrase + "\n\nfor about 3 seconds.");

    QByteArray capturedData = captureVoiceFromMicrophone(3000);
    if (capturedData.isEmpty()) {
        QMessageBox::warning(this, "Voice Sign In", "No voice captured.");
        return false;
    }

    QVector<double> capturedFeatures = extractVoiceFeatures(capturedData, m_lastVoiceFormat);
    if (capturedFeatures.isEmpty()) {
        QMessageBox::warning(this, "Voice Sign In", "Unable to extract voice features.");
        return false;
    }

    auto voices = Personnel::getAllRegisteredVoiceIds();
    if (voices.isEmpty()) {
        QMessageBox::warning(this, "Voice Sign In", "No registered Voice ID found in database.");
        return false;
    }

    double bestScore = -1.0;
    Personnel::VoiceRecord bestRecord;
    bool found = false;

    for (const auto& rec : voices) {
        QVector<double> dbFeatures = jsonToVoiceFeatures(rec.voiceFeatures);
        if (dbFeatures.isEmpty()) {
            continue;
        }

        double score = compareVoiceFeatures(capturedFeatures, dbFeatures);
        qDebug() << "Voice compare with" << rec.mail << "| score =" << score;

        if (score > bestScore) {
            bestScore = score;
            bestRecord = rec;
            found = true;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Voice Sign In", "No valid registered voice found.");
        return false;
    }

    qDebug() << "Best voice match =" << bestRecord.mail << "| score =" << bestScore;


    if (bestScore < 0.88) {
        QMessageBox::warning(this, "Voice Sign In", "Voice not recognized.");
        return false;
    }

    QString authMail, authRole, authCvStatus;
    Personnel::FaceLoginResult result =
        Personnel::authenticateByVoiceIdMail(bestRecord.mail, &authMail, &authRole, &authCvStatus);

    switch (result) {
    case Personnel::FaceLoginResult::Ok: {
        m_currentUserMail = authMail;
        m_currentRole = authRole;

        Personnel::UserProfile profile;
        if (Personnel::fetchProfileByMail(authMail, &profile)) {
            m_currentUserId = profile.idPers;
            m_currentAccountAvatar = profile.avatar;
            updateUserProfileUI((profile.prenom + " " + profile.nom).trimmed(), authRole, profile.avatar);
        }

        applyRolePermissions(m_currentRole);
        beginSessionForCurrentUser();
        loadCurrentUserAccountData();
        loadStaffDashboardStats();
        loadEmployeeCount();
        ui->stackedWidget->setCurrentWidget(ui->pageWelcome);

        QMessageBox::information(this, "Voice Sign In", "Voice recognized successfully.");
        return true;
    }

    case Personnel::FaceLoginResult::AccountBlocked:
        QMessageBox::critical(this, "Voice Sign In", "This account is temporarily blocked.");
        return false;

    case Personnel::FaceLoginResult::FaceNotEnabled:
        QMessageBox::warning(this, "Voice Sign In", "Voice ID is disabled for this account.");
        return false;

    case Personnel::FaceLoginResult::CvNotAccepted:
        QMessageBox::warning(this, "Voice Sign In", "Your CV is not accepted. Access denied.");
        return false;

    case Personnel::FaceLoginResult::SuspiciousActivity:
        QMessageBox::warning(this, "Voice Sign In", "Suspicious voice activity detected.");
        return false;

    case Personnel::FaceLoginResult::FaceNotRecognized:
        QMessageBox::warning(this, "Voice Sign In", "Voice not recognized.");
        return false;

    case Personnel::FaceLoginResult::DbError:
    default:
        QMessageBox::critical(this, "Voice Sign In", "Database error during voice authentication.");
        return false;
    }
}

void SignIn::on_withvoicebtn_clicked()
{
    authenticateWithVoiceId();
}

void SignIn::initArduinoConnection()
{
    const int result = A.connect_arduino();

    if (result == 0) {
        qDebug() << "Arduino connected on port:" << A.getarduino_port_name();

        connect(A.getserial(), &QSerialPort::readyRead,
                this, &SignIn::onArduinoReadyRead,
                Qt::UniqueConnection);

    } else {
        qDebug() << "Arduino connection failed, code =" << result;
    }
}
QString SignIn::formatMonthlyHoursForRfid(qint64 totalSeconds) const
{
    if (totalSeconds < 0) totalSeconds = 0;

    const qint64 hours = totalSeconds / 3600;
    const qint64 minutes = (totalSeconds % 3600) / 60;

    return QString("%1h%2")
        .arg(hours)
        .arg(minutes, 2, 10, QChar('0'));
}
void SignIn::onArduinoReadyRead()
{
    serialBuffer += A.read_from_arduino();

    while (serialBuffer.contains('\n')) {

        int index = serialBuffer.indexOf('\n');

        QByteArray line = serialBuffer.left(index).trimmed();

        serialBuffer.remove(0, index + 1);

        QString msg = QString::fromUtf8(line);

        qDebug() << "Arduino -> Qt:" << msg;

        // RFID
        if (msg.startsWith("UID:", Qt::CaseInsensitive)) {

            QString uid = msg.mid(4).trimmed();

            processRfidUid(uid);
        }

        // WATER SENSOR
        else if (msg.startsWith("Distance:", Qt::CaseInsensitive)) {

            QRegularExpression regex("Distance:\\s*(\\d+)");

            QRegularExpressionMatch match = regex.match(msg);

            if (match.hasMatch()) {

                int distance = match.captured(1).toInt();

                updateWaterLevel(distance);
            }
        }
    }
}
void SignIn::processArduinoLine(const QByteArray& line)
{
    const QString msg = QString::fromUtf8(line).trimmed();

    if (msg.isEmpty()) {
        return;
    }

    qDebug() << "Arduino -> Qt:" << msg;

    if (msg.startsWith("UID:", Qt::CaseInsensitive)) {

        QString uid = msg.mid(4).trimmed();
        processRfidUid(uid);
    }

    else if (msg.startsWith("Distance:", Qt::CaseInsensitive)) {

        QRegularExpression regex("Distance:\\s*(\\d+)");
        QRegularExpressionMatch match = regex.match(msg);

        if (match.hasMatch()) {

            int distance = match.captured(1).toInt();

            qDebug() << "Distance detected:" << distance;

            updateWaterLevel(distance);
        }
    }
}
void SignIn::processRfidUid(const QString& uid)
{
    QString cleanUid = uid.trimmed().toUpper();
    cleanUid.replace(QRegularExpression("\\s+"), " ");

    qDebug() << "processRfidUid reached with:" << cleanUid;

    Personnel::RfidUserInfo info;
    if (!Personnel::fetchRfidUserByUid(cleanUid, &info)) {
        qDebug() << "Unknown RFID detected:" << cleanUid;
        logRfidAccess("Unknown card", "Access denied");
        A.write_to_arduino("DENIED\n");
        return;
    }

    QString accountStatus = info.accountStatus.trimmed();

    QString fullName = (info.prenom.trimmed() + " " + info.nom.trimmed()).trimmed();
    if (fullName.isEmpty())
        fullName = info.mail.trimmed();

    if (accountStatus.compare("BLOCKED", Qt::CaseInsensitive) == 0) {
        const QString reply = QString("BLOCKED|%1\n").arg(fullName);
        A.write_to_arduino(reply.toUtf8());
        logRfidAccess(fullName, "Account blocked");
        return;
    }

    Personnel::resetAuthRiskByMail(info.mail, "RFID");

    const QString hoursText = formatMonthlyHoursForRfid(info.monthlyWorkSeconds);
    const QString reply = QString("GRANTED|%1|%2\n").arg(fullName, hoursText);

    A.write_to_arduino(reply.toUtf8());
    logRfidAccess(fullName, "Access granted");
}
void SignIn::logRfidAccess(const QString& user, const QString& status)
{
    addAccessHistoryEntry(user, status, "RFID");
    qDebug() << "RFID history added:" << user << status;
}
void SignIn::setupAccessHistoryTable()
{
    ui->historique->clearContents();
    ui->historique->setRowCount(0);
    ui->historique->setColumnCount(4);

    QStringList headers;
    headers << "Time" << "User" << "Status" << "Method";
    ui->historique->setHorizontalHeaderLabels(headers);

    ui->historique->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->historique->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->historique->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->historique->setShowGrid(false);
    ui->historique->verticalHeader()->setVisible(false);
    ui->historique->horizontalHeader()->setHighlightSections(false);
    ui->historique->horizontalHeader()->setStretchLastSection(true);

    ui->historique->setColumnWidth(0, 95);
    ui->historique->setColumnWidth(1, 220);
    ui->historique->setColumnWidth(2, 170);

    ui->historique->verticalHeader()->setDefaultSectionSize(38);
}
void SignIn::addAccessHistoryEntry(const QString& user,
                                   const QString& status,
                                   const QString& method)
{
    const QString timeText = QDateTime::currentDateTime().toString("HH:mm:ss");

    ui->historique->insertRow(0);

    QTableWidgetItem* timeItem   = new QTableWidgetItem(timeText);
    QTableWidgetItem* userItem   = new QTableWidgetItem(user);
    QTableWidgetItem* statusItem = new QTableWidgetItem(status);
    QTableWidgetItem* methodItem = new QTableWidgetItem(method);

    timeItem->setTextAlignment(Qt::AlignCenter);
    userItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    statusItem->setTextAlignment(Qt::AlignCenter);
    methodItem->setTextAlignment(Qt::AlignCenter);

    ui->historique->setItem(0, 0, timeItem);
    ui->historique->setItem(0, 1, userItem);
    ui->historique->setItem(0, 2, statusItem);
    ui->historique->setItem(0, 3, methodItem);


    while (ui->historique->rowCount() > 20) {
        ui->historique->removeRow(ui->historique->rowCount() - 1);
    }
}




//dhia
void SignIn::on_addZonebtn_clicked()
{
    QString nom = ui->ZoneName->text().trimmed();
    QString longitude = ui->Longitude->text().trimmed();
    QString latitude = ui->Latitude->text().trimmed();
    QString typeZone = ui->zoneEdit->currentText().trimmed();
    QString risque = ui->RiskLevel->currentText().trimmed();
    QString description = ui->DescriptionEdit->toPlainText().trimmed();

    if (nom.isEmpty() || longitude.isEmpty() || latitude.isEmpty()
        || typeZone.isEmpty() || risque.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    ZonePech z(nom, longitude, latitude, typeZone, risque, description);

    if (z.ajouter()) {
        QMessageBox::information(this, "Success", "Zone created successfully.");
        loadZonesToTable();

        ui->ZoneName->clear();
        ui->Longitude->clear();
        ui->Latitude->clear();
        ui->DescriptionEdit->clear();
        ui->zoneEdit->setCurrentIndex(0);
        ui->RiskLevel->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Error", "Insert failed.");
    }
}
void SignIn::on_EditZonebtn_clicked()
{
    if (selectedZoneId == -1) {
        QMessageBox::warning(this, "Edit", "Select a zone from the table first.");
        return;
    }

    QString nom = ui->ZoneName->text().trimmed();
    QString longitude = ui->Longitude->text().trimmed();
    QString latitude = ui->Latitude->text().trimmed();
    QString typeZone = ui->zoneEdit->currentText().trimmed();
    QString risque = ui->RiskLevel->currentText().trimmed();
    QString description = ui->DescriptionEdit->toPlainText().trimmed();

    if (nom.isEmpty() || longitude.isEmpty() || latitude.isEmpty()
        || typeZone.isEmpty() || risque.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Edit", "Please fill in all fields.");
        return;
    }

    if (QMessageBox::question(this, "Confirm", "Apply changes to this zone?")
        != QMessageBox::Yes) {
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    ZonePech z(nom, longitude, latitude, typeZone, risque, description);

    if (z.modifier(selectedZoneId)) {
        QMessageBox::information(this, "Edit", "Zone updated.");
        loadZonesToTable();

        selectedZoneId = -1;
        ui->ZoneName->clear();
        ui->Longitude->clear();
        ui->Latitude->clear();
        ui->DescriptionEdit->clear();
        ui->zoneEdit->setCurrentIndex(0);
        ui->RiskLevel->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Edit", "Update failed.");
    }
}
void SignIn::on_DeleteZone_clicked()
{
    if (selectedZoneId == -1) {
        QMessageBox::warning(this, "Delete", "Select a zone from the table first.");
        return;
    }

    auto rep = QMessageBox::question(
        this,
        "Confirm delete",
        "Delete the selected zone permanently?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (rep != QMessageBox::Yes)
        return;

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    ZonePech z;
    if (z.supprimer(selectedZoneId)) {
        QMessageBox::information(this, "Delete", "Zone deleted.");

        selectedZoneId = -1;
        ui->ZoneName->clear();
        ui->Longitude->clear();
        ui->Latitude->clear();
        ui->DescriptionEdit->clear();
        ui->zoneEdit->setCurrentIndex(0);
        ui->RiskLevel->setCurrentIndex(0);

        loadZonesToTable();
    } else {
        QMessageBox::critical(this, "Delete", "Delete failed.");
    }
}

void SignIn::loadZonesToTable()
{
    QStringList headers = {
        "IDZONE",
        "Name",
        "Latitude",
        "Longitude",
        "Zone Type",
        "Period",
        "Risk Level",
        "Description"
    };

    ui->ZoneTable->clear();
    ui->ZoneTable->setColumnCount(headers.size());
    ui->ZoneTable->setHorizontalHeaderLabels(headers);
    ui->ZoneTable->setRowCount(0);

    ZonePech z;
    QString selectedSort = ui->sortzone->currentText();
    QString searchText = ui->ZoneSearch->text().trimmed();
    QVector<QStringList> rows = z.getZoneRows(selectedSort, searchText);

    ui->ZoneTable->setRowCount(rows.size());

    for (int r = 0; r < rows.size(); ++r) {
        for (int c = 0; c < headers.size(); ++c) {
            QTableWidgetItem *item = new QTableWidgetItem(rows[r][c]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->ZoneTable->setItem(r, c, item);
        }
    }

    ui->ZoneTable->setColumnHidden(0, true); // hide IDZONE
    ui->ZoneTable->resizeColumnsToContents();
}
void SignIn::on_ZoneTable_cellClicked(int row, int)
{
    auto idItem = ui->ZoneTable->item(row, 0);
    if (!idItem) return;

    selectedZoneId = idItem->text().toInt();

    auto nameItem = ui->ZoneTable->item(row, 1);
    auto latItem  = ui->ZoneTable->item(row, 2);
    auto lonItem  = ui->ZoneTable->item(row, 3);
    auto typeItem = ui->ZoneTable->item(row, 4);
    auto riskItem = ui->ZoneTable->item(row, 6);
    auto descItem = ui->ZoneTable->item(row, 7);

    if (nameItem) ui->ZoneName->setText(nameItem->text());
    if (lonItem)  ui->Longitude->setText(lonItem->text());
    if (latItem)  ui->Latitude->setText(latItem->text());
    if (typeItem) ui->zoneEdit->setCurrentText(typeItem->text());
    if (riskItem) ui->RiskLevel->setCurrentText(riskItem->text());
    if (descItem) ui->DescriptionEdit->setPlainText(descItem->text());
}
void SignIn::on_AnalyticsZone_clicked()
{
    showPieChart();
}
QVector<QStringList> ZonePech::getZoneRows(QString sort, QString search)
{
    QVector<QStringList> rows;
    QSqlQuery q;

    QString queryStr =
        "SELECT IDZONE, NOM, LATITUDE, LONGITUDE, TYPEZONE, PERIODEAUTORISEE, NIVEAURISQUE, DESCRIPTION "
        "FROM ZONEPECHES";

    // 🔍 SEARCH
    if (!search.isEmpty()) {
        queryStr += " WHERE LOWER(NOM) LIKE LOWER(:search) "
                    "OR LOWER(NIVEAURISQUE) LIKE LOWER(:search)";
    }

    // 🔽 SORT
    if (sort == "Name") {
        queryStr += " ORDER BY NOM";
    } else if (sort == "Risk") {
        queryStr += " ORDER BY NIVEAURISQUE";
    }

    q.prepare(queryStr);

    if (!search.isEmpty()) {
        q.bindValue(":search", "%" + search + "%");
    }

    q.exec();

    while (q.next()) {
        QStringList row;
        row << q.value(0).toString()
            << q.value(1).toString()
            << q.value(2).toString()
            << q.value(3).toString()
            << q.value(4).toString()
            << q.value(5).toString()
            << q.value(6).toString()
            << q.value(7).toString();

        rows.append(row);
    }

    return rows;
}

void SignIn::on_exportZone_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Zones to PDF",
        "Fishing_Zones_Report.pdf",
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
    pdf.setPageMargins(QMarginsF(12, 12, 12, 12));

    QPainter painter(&pdf);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    int pageWidth = pdf.width();
    int pageHeight = pdf.height();

    // ===== Colors matching your UI =====
    QColor bgColor(7, 27, 44);
    QColor panelColor(11, 45, 74);
    QColor accentColor(29, 161, 242);
    QColor headerTextColor(255, 255, 255);
    QColor bodyTextColor(234, 244, 255);
    QColor gridColor(47, 93, 124);
    QColor rowAltColor(14, 36, 56);
    QColor buttonBlue(22, 74, 115);

    // ===== Background =====
    painter.fillRect(0, 0, pageWidth, pageHeight, bgColor);

    // ===== Main content area =====
    int margin = 80;
    QRect contentRect(margin, margin, pageWidth - 2 * margin, pageHeight - 2 * margin);
    // ===== Top header panel =====
    QRect headerRect(contentRect.left(), contentRect.top(), contentRect.width(), 200);
    painter.fillRect(headerRect, panelColor);

    painter.setPen(accentColor);
    painter.drawRect(headerRect);

    // Define padding
    int leftPadding = 40;
    int topPadding = 25;
    int lineSpacing = 55;

    // ===== Title =====
    QFont titleFont("Arial", 24, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(headerTextColor);

    painter.drawText(
        headerRect.left() + leftPadding,
        headerRect.top() + topPadding + 30,
        "BORT - Smart Fishing Port Application"
        );

    // ===== Subtitle =====
    QFont subFont("Arial", 14);
    painter.setFont(subFont);
    painter.setPen(bodyTextColor);

    painter.drawText(
        headerRect.left() + leftPadding,
        headerRect.top() + topPadding + lineSpacing + 30,
        "Fishing Zones Report"
        );

    // ===== Date =====
    QFont dateFont("Arial", 11);
    painter.setFont(dateFont);

    painter.drawText(
        headerRect.left() + leftPadding,
        headerRect.top() + topPadding + (lineSpacing * 2) + 30,
        "Generated on: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm")
        );
    painter.setPen(QPen(accentColor, 2));
    painter.drawLine(
        headerRect.left() + 20,
        headerRect.bottom() - 10,
        headerRect.right() - 20,
        headerRect.bottom() - 10
        );
    // ===== Table title bar =====
    QRect tableTitleRect(contentRect.left(), headerRect.bottom() + 30, contentRect.width(), 70);
    painter.fillRect(tableTitleRect, buttonBlue);
    painter.setPen(accentColor);
    painter.drawRect(tableTitleRect);

    QFont tableTitleFont("Arial", 14, QFont::Bold);
    painter.setFont(tableTitleFont);
    painter.setPen(headerTextColor);
    painter.drawText(tableTitleRect, Qt::AlignCenter, "Zone List");

    // ===== Table geometry =====
    int tableTop = tableTitleRect.bottom() + 20;
    int tableLeft = contentRect.left();
    int tableWidth = contentRect.width();
    int rowHeight = 55;
    int headerHeight = 60;

    // Visible columns only (skip hidden ID)
    QList<int> visibleCols;
    for (int c = 0; c < ui->ZoneTable->columnCount(); ++c) {
        if (!ui->ZoneTable->isColumnHidden(c))
            visibleCols.append(c);
    }

    if (visibleCols.isEmpty()) {
        QMessageBox::warning(this, "Export PDF", "No visible columns to export.");
        return;
    }

    int colCount = visibleCols.size();
    int tableRows = ui->ZoneTable->rowCount();

    // Dynamic column widths
    QVector<int> colWidths;
    colWidths.resize(colCount);

    // Make Description wider, others balanced
    int remainingWidth = tableWidth;
    for (int i = 0; i < colCount; ++i) {
        QString header = ui->ZoneTable->horizontalHeaderItem(visibleCols[i])
        ? ui->ZoneTable->horizontalHeaderItem(visibleCols[i])->text()
        : "";

        if (header.toLower().contains("description"))
            colWidths[i] = tableWidth * 0.26;
        else if (header.toLower().contains("zone type"))
            colWidths[i] = tableWidth * 0.14;
        else if (header.toLower().contains("risk"))
            colWidths[i] = tableWidth * 0.13;
        else
            colWidths[i] = tableWidth * 0.095;
    }

    int totalWidth = 0;
    for (int w : colWidths) totalWidth += w;

    // Normalize to exact table width
    if (totalWidth != tableWidth && !colWidths.isEmpty()) {
        colWidths[colWidths.size() - 1] += (tableWidth - totalWidth);
    }

    // ===== Header row =====
    int currentX = tableLeft;
    int currentY = tableTop;

    painter.setFont(QFont("Arial", 11, QFont::Bold));

    for (int i = 0; i < colCount; ++i) {
        QRect cellRect(currentX, currentY, colWidths[i], headerHeight);
        painter.fillRect(cellRect, panelColor);
        painter.setPen(gridColor);
        painter.drawRect(cellRect);

        painter.setPen(accentColor);
        QString headerText = ui->ZoneTable->horizontalHeaderItem(visibleCols[i])
                                 ? ui->ZoneTable->horizontalHeaderItem(visibleCols[i])->text()
                                 : "";
        painter.drawText(cellRect.adjusted(8, 4, -8, -4), Qt::AlignCenter | Qt::TextWordWrap, headerText);

        currentX += colWidths[i];
    }

    currentY += headerHeight;

    // ===== Data rows =====
    painter.setFont(QFont("Arial", 10));
    int maxRowsPerPage = (contentRect.bottom() - currentY - 60) / rowHeight;

    int printedRows = 0;
    for (int row = 0; row < tableRows; ++row) {
        if (printedRows == maxRowsPerPage) {
            pdf.newPage();
            painter.fillRect(0, 0, pageWidth, pageHeight, bgColor);

            currentY = margin;
            currentX = tableLeft;

            // Redraw mini header on new page
            QRect newHeader(contentRect.left(), currentY, contentRect.width(), 90);
            painter.fillRect(newHeader, panelColor);
            painter.setPen(accentColor);
            painter.drawRect(newHeader);

            painter.setFont(QFont("Arial", 18, QFont::Bold));
            painter.setPen(headerTextColor);
            painter.drawText(newHeader, Qt::AlignCenter, "Fishing Zones Report");

            currentY = newHeader.bottom() + 20;

            // redraw table headers
            currentX = tableLeft;
            painter.setFont(QFont("Arial", 11, QFont::Bold));
            for (int i = 0; i < colCount; ++i) {
                QRect cellRect(currentX, currentY, colWidths[i], headerHeight);
                painter.fillRect(cellRect, panelColor);
                painter.setPen(gridColor);
                painter.drawRect(cellRect);

                painter.setPen(accentColor);
                QString headerText = ui->ZoneTable->horizontalHeaderItem(visibleCols[i])
                                         ? ui->ZoneTable->horizontalHeaderItem(visibleCols[i])->text()
                                         : "";
                painter.drawText(cellRect.adjusted(8, 4, -8, -4), Qt::AlignCenter | Qt::TextWordWrap, headerText);
                currentX += colWidths[i];
            }

            currentY += headerHeight;
            printedRows = 0;
        }

        currentX = tableLeft;

        QColor rowColor = (row % 2 == 0) ? bgColor : rowAltColor;

        for (int col = 0; col < colCount; ++col) {
            QRect cellRect(currentX, currentY, colWidths[col], rowHeight);
            painter.fillRect(cellRect, rowColor);
            painter.setPen(gridColor);
            painter.drawRect(cellRect);

            painter.setPen(bodyTextColor);
            QTableWidgetItem *item = ui->ZoneTable->item(row, visibleCols[col]);
            QString text = item ? item->text() : "";

            painter.drawText(cellRect.adjusted(8, 6, -8, -6),
                             Qt::AlignCenter | Qt::TextWordWrap,
                             text);

            currentX += colWidths[col];
        }

        currentY += rowHeight;
        printedRows++;
    }

    painter.end();

    QMessageBox::information(this, "Export PDF", "PDF exported successfully.");


}
void SignIn::showPieChart()
{
    // Create the dialog for the pie chart
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Analytics: Risk Levels");

    chartDialog->resize(600, 400);

    // Create the chart view
    QChartView *chartView = new QChartView(chartDialog);
    QPieSeries *series = new QPieSeries();

    // Fetch data for risk levels from the database
    QSqlQuery query;
    query.exec("SELECT NIVEAURISQUE, COUNT(*) FROM ZONEPECHES GROUP BY NIVEAURISQUE");

    // Define colors for the risk levels
    QColor riskyColor("#FF4C4C");  // Red for Risky
    QColor mildColor("#F9A826");   // Yellow for Mild
    QColor safeColor("#4BBF6E");   // Green for Safe

    // Add slices based on data from the query
    while (query.next()) {
        QString riskLevel = query.value(0).toString();
        int count = query.value(1).toInt();

        QPieSlice *slice = series->append(riskLevel, count);
        slice->setLabelVisible(true);

        // Apply custom colors
        if (riskLevel == "Risky") {
            slice->setBrush(riskyColor);
        } else if (riskLevel == "Mild") {
            slice->setBrush(mildColor);
        } else {
            slice->setBrush(safeColor);
        }

        slice->setPen(QPen(QColor("#0B2D4A")));  // Border color for slices
    }

    // Create and configure the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Risk Level Distribution");
    chart->legend()->setVisible(true);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Apply QSS styling to match UI theme
    chart->setBackgroundBrush(QBrush(QColor("#071a2c"))); // Set dark background for chart
    chartView->setChart(chart);  // Apply the chart to the view

    // Layout for the dialog
    chartDialog->setLayout(new QVBoxLayout());
    chartDialog->layout()->addWidget(chartView);
    chartDialog->exec();
}



int SignIn::predictSuitability(const QString& zoneType, const QString& riskLevel, double longitude, double latitude)
{
    int score = 50;

    QString type = zoneType.trimmed().toLower();
    QString risk = riskLevel.trimmed().toLower();

    // zone type effect
    if (type == "open")
        score += 20;
    else if (type == "crowded")
        score -= 15;

    // current stored risk level effect
    if (risk == "safe")
        score += 25;
    else if (risk == "mild")
        score += 5;
    else if (risk == "risky")
        score -= 25;

    // simulated seasonal/environment effect
    score += environmentalWeatherModifier(longitude, latitude);

    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return score;
}
QString SignIn::suitabilityLevel(int score)
{
    if (score >= 80)
        return "EXCELLENT";
    else if (score >= 60)
        return "GOOD";
    else if (score >= 40)
        return "LIMITED";
    else
        return "NOT RECOMMENDED";
}
QString SignIn::suitabilityMessage(int score)
{
    QString season = currentSeason();

    if (score >= 80)
        return "The zone shows strong fishing suitability under the current seasonal and environmental conditions. Operations may proceed normally.";
    else if (score >= 60)
        return "The zone is generally suitable for fishing activity. Current " + season + " conditions suggest moderate environmental stability.";
    else if (score >= 40)
        return "Fishing activity is possible but limited. The current " + season + " environmental pattern suggests extra caution and monitoring.";
    else
        return "Fishing activity is not recommended at this time. Simulated " + season + " conditions and zone characteristics reduce operational suitability.";
}
QString SignIn::suitabilityColor(int score)
{
    if (score >= 80)
        return "#35c46a";
    else if (score >= 60)
        return "#58b8ff";
    else if (score >= 40)
        return "#f5a623";
    else
        return "#ff4d5a";
}
void SignIn::on_RiskPrediction_clicked()
{
    int row = ui->ZoneTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Select Zone", "Please select a zone from the table first.");
        return;
    }

    QString zoneName = ui->ZoneTable->item(row, 1)->text();
    QString latitudeText = ui->ZoneTable->item(row, 2)->text();
    QString longitudeText = ui->ZoneTable->item(row, 3)->text();
    QString zoneType = ui->ZoneTable->item(row, 4)->text();
    QString riskLevel = ui->ZoneTable->item(row, 6)->text();

    double longitude = longitudeText.toDouble();
    double latitude = latitudeText.toDouble();

    int score = predictSuitability(zoneType, riskLevel, longitude, latitude);
    QString message = suitabilityMessage(score);
    QString color = suitabilityColor(score);
    QString level = suitabilityLevel(score);
    QString season = currentSeason();

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Fishing Activity Suitability");
    dialog->resize(520, 320);
    dialog->setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(16);

    QWidget *card = new QWidget(dialog);
    card->setObjectName("predictionCard");
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 22, 22, 22);
    cardLayout->setSpacing(14);

    QLabel *titleLabel = new QLabel("Fishing Activity Suitability", card);
    titleLabel->setObjectName("predictionTitle");

    QLabel *zoneLabel = new QLabel("Zone: " + zoneName, card);
    zoneLabel->setObjectName("predictionInfo");

    QLabel *detailsLabel = new QLabel(
        "Type: " + zoneType + "   |   Current Level: " + riskLevel +
            "   |   Season: " + season +
            "   |   Lat: " + latitudeText + "   |   Lon: " + longitudeText,
        card
        );
    detailsLabel->setWordWrap(true);
    detailsLabel->setObjectName("predictionDetails");

    QLabel *percentLabel = new QLabel(QString::number(score) + "%", card);
    percentLabel->setAlignment(Qt::AlignCenter);
    percentLabel->setObjectName("predictionPercent");
    percentLabel->setStyleSheet(
        "QLabel#predictionPercent {"
        "background-color: " + color + ";"
                  "color: white;"
                  "border-radius: 28px;"
                  "font-size: 26px;"
                  "font-weight: 800;"
                  "padding: 14px 24px;"
                  "min-width: 120px;"
                  "max-width: 120px;"
                  "}"
        );

    QLabel *levelLabel = new QLabel(level, card);
    levelLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setObjectName("predictionLevel");

    QLabel *messageLabel = new QLabel(message, card);
    messageLabel->setWordWrap(true);
    messageLabel->setObjectName("predictionMessage");

    QPushButton *closeBtn = new QPushButton("Close", card);
    closeBtn->setObjectName("predictionCloseBtn");
    connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::accept);

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(zoneLabel);
    cardLayout->addWidget(detailsLabel, 0, Qt::AlignLeft);
    cardLayout->addSpacing(6);
    cardLayout->addWidget(percentLabel, 0, Qt::AlignHCenter);
    cardLayout->addWidget(levelLabel, 0, Qt::AlignHCenter);
    cardLayout->addWidget(messageLabel);
    cardLayout->addSpacing(8);
    cardLayout->addWidget(closeBtn, 0, Qt::AlignRight);

    mainLayout->addWidget(card);

    dialog->setStyleSheet(
        "QDialog {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #071a2c, stop:0.35 #082136, stop:0.7 #071c2d, stop:1 #040f1a);"
        "font-family: 'Segoe UI';"
        "color: #EAF0FF;"
        "}"
        "QWidget#predictionCard {"
        "background-color: rgba(8, 30, 55, 0.92);"
        "border: 1px solid rgba(88,184,255,0.35);"
        "border-radius: 18px;"
        "}"
        "QLabel#predictionTitle {"
        "font-size: 22px;"
        "font-weight: 800;"
        "color: #EAF0FF;"
        "}"
        "QLabel#predictionInfo {"
        "font-size: 15px;"
        "font-weight: 700;"
        "color: #9fd8ff;"
        "}"
        "QLabel#predictionDetails {"
        "font-size: 12px;"
        "color: rgba(234,240,255,0.80);"
        "}"
        "QLabel#predictionLevel {"
        "font-size: 15px;"
        "font-weight: 800;"
        "color: #EAF0FF;"
        "letter-spacing: 1px;"
        "}"
        "QLabel#predictionMessage {"
        "font-size: 14px;"
        "color: #EAF0FF;"
        "background-color: rgba(255,255,255,0.04);"
        "border: 1px solid rgba(255,255,255,0.10);"
        "border-radius: 12px;"
        "padding: 12px;"
        "}"
        "QPushButton#predictionCloseBtn {"
        "background-color: rgba(88,184,255,0.18);"
        "border: 1px solid rgba(88,184,255,0.45);"
        "border-radius: 12px;"
        "padding: 10px 18px;"
        "color: #EAF0FF;"
        "font-weight: 700;"
        "min-width: 90px;"
        "}"
        "QPushButton#predictionCloseBtn:hover {"
        "background-color: rgba(88,184,255,0.28);"
        "}"
        "QPushButton#predictionCloseBtn:pressed {"
        "background-color: rgba(88,184,255,0.38);"
        "}"
        );

    dialog->exec();
}
QString SignIn::currentSeason()
{
    int month = QDate::currentDate().month();

    if (month == 12 || month == 1 || month == 2)
        return "winter";
    else if (month >= 3 && month <= 5)
        return "spring";
    else if (month >= 6 && month <= 8)
        return "summer";
    else
        return "autumn";
}
int SignIn::environmentalWeatherModifier(double longitude, double latitude)
{
    int modifier = 0;
    QString season = currentSeason();

    // seasonal effect
    if (season == "winter")
        modifier -= 15;
    else if (season == "spring")
        modifier += 5;
    else if (season == "summer")
        modifier += 10;
    else if (season == "autumn")
        modifier -= 5;

    // simulated geographic exposure
    // larger abs values = slightly harsher environment
    int latEffect = static_cast<int>(qAbs(latitude)) % 12;
    int lonEffect = static_cast<int>(qAbs(longitude)) % 12;

    modifier -= latEffect / 2;
    modifier -= lonEffect / 3;

    return modifier;
}

struct RegulationCase
{
    QString zoneType;
    QString riskLevel;
    double longitude;
    double latitude;
    QString staffRule;
    QString equipmentRule;
    QString cautionRule;
    QString accessRule;
};
double SignIn::calculateSimilarity(const QString& zoneType1, const QString& riskLevel1, double lon1, double lat1,
                                   const QString& zoneType2, const QString& riskLevel2, double lon2, double lat2)
{
    double score = 0.0;

    if (zoneType1.trimmed().toLower() == zoneType2.trimmed().toLower())
        score += 30.0;

    if (riskLevel1.trimmed().toLower() == riskLevel2.trimmed().toLower())
        score += 40.0;

    double lonDiff = qAbs(lon1 - lon2);
    double latDiff = qAbs(lat1 - lat2);

    double lonScore = qMax(0.0, 15.0 - lonDiff);
    double latScore = qMax(0.0, 15.0 - latDiff);

    score += lonScore;
    score += latScore;

    return score;
}
QString SignIn::generateRegulationsAI(const QString& zoneType, const QString& riskLevel, double longitude, double latitude)
{
    QVector<RegulationCase> cases = {
        {"open", "safe", 10, 10, "1 staff supervisor required.", "Basic fishing equipment allowed.", "Standard monitoring is sufficient.", "Zone remains fully accessible."},
        {"open", "mild", 12, 14, "2 staff members required.", "Safety kit and communication radio required.", "Weather and movement checks every 2 hours.", "Partial supervision required during activity."},
        {"open", "risky", 15, 20, "3 trained staff members required.", "Protective gear and emergency flotation devices required.", "High-alert monitoring must be active.", "Restricted access for inexperienced personnel."},

        {"crowded", "safe", 9, 11, "2 staff supervisors required.", "Equipment issue must be logged before use.", "Crowd flow must be monitored.", "Access allowed with supervision."},
        {"crowded", "mild", 18, 16, "3 staff members required.", "Protective equipment and signaling tools required.", "Continuous observation of crowd density is required.", "Entry must be regulated by staff approval."},
        {"crowded", "risky", 25, 25, "4 experienced staff members required.", "Full protective equipment mandatory.", "Emergency readiness protocol must remain active.", "Zone access restricted to authorized personnel only."},

        {"open", "safe", 30, 8, "1 staff supervisor required.", "Routine equipment inspection required.", "Low-risk monitoring mode.", "Open access permitted."},
        {"crowded", "risky", 28, 13, "4 staff members required.", "Emergency and protective equipment mandatory.", "Maximum caution protocol enforced.", "Temporary access limitation required."},
        {"open", "mild", 22, 6, "2 staff members required.", "Inspection of hooks, nets, and radio required.", "Moderate caution protocol.", "Access controlled during peak periods."},
        {"crowded", "mild", 35, 18, "3 staff supervisors required.", "Protective and communication equipment required.", "Environmental and density checks required.", "Supervised access only."}
    };

    QVector<QPair<double, RegulationCase>> scoredCases;

    for (const RegulationCase& c : cases) {
        double similarity = calculateSimilarity(zoneType, riskLevel, longitude, latitude,
                                                c.zoneType, c.riskLevel, c.longitude, c.latitude);
        scoredCases.append(qMakePair(similarity, c));
    }

    std::sort(scoredCases.begin(), scoredCases.end(),
              [](const QPair<double, RegulationCase>& a, const QPair<double, RegulationCase>& b) {
                  return a.first > b.first;
              });

    QString result;
    result += "AI-based regulation synthesis generated from similar fishing zone cases.\n\n";

    if (!scoredCases.isEmpty()) {
        const RegulationCase& best = scoredCases[0].second;

        result += "Recommended Staff Regulation\n";
        result += "• " + best.staffRule + "\n\n";

        result += "Recommended Equipment Regulation\n";
        result += "• " + best.equipmentRule + "\n\n";

        result += "Operational Caution\n";
        result += "• " + best.cautionRule + "\n\n";

        result += "Access Control\n";
        result += "• " + best.accessRule + "\n\n";
    }

    if (latitude >= 20)
        result += "Geographic Note\n• Northern-position zone: reinforce wildlife and environmental observation.\n\n";
    else
        result += "Geographic Note\n• Lower-latitude zone: standard marine surveillance remains sufficient.\n\n";

    if (longitude >= 15)
        result += "Location Advisory\n• Offshore-style position detected: require stronger communication preparedness.\n";
    else
        result += "Location Advisory\n• Near-access position detected: standard response logistics apply.\n";

    return result;
}
void SignIn::on_Regulations_clicked()
{
    int row = ui->ZoneTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Select Zone", "Please select a zone from the table first.");
        return;
    }

    QString zoneName = ui->ZoneTable->item(row, 1)->text();
    QString latitudeText = ui->ZoneTable->item(row, 2)->text();
    QString longitudeText = ui->ZoneTable->item(row, 3)->text();
    QString zoneType = ui->ZoneTable->item(row, 4)->text();
    QString riskLevel = ui->ZoneTable->item(row, 6)->text();

    double longitude = longitudeText.toDouble();
    double latitude = latitudeText.toDouble();

    QString regulations = generateRegulationsAI(zoneType, riskLevel, longitude, latitude);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Fishing Zone Regulations");
    dialog->resize(650, 460);
    dialog->setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(16);

    QWidget *card = new QWidget(dialog);
    card->setObjectName("regulationsCard");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 22, 22, 22);
    cardLayout->setSpacing(14);

    QLabel *titleLabel = new QLabel("AI Zone Regulations", card);
    titleLabel->setObjectName("regulationsTitle");

    QLabel *zoneLabel = new QLabel("Zone: " + zoneName, card);
    zoneLabel->setObjectName("regulationsInfo");

    QLabel *detailsLabel = new QLabel(
        "Type: " + zoneType + "   |   Current Level: " + riskLevel +
            "   |   Lat: " + latitudeText + "   |   Lon: " + longitudeText,
        card
        );
    detailsLabel->setWordWrap(true);
    detailsLabel->setObjectName("regulationsDetails");

    QLabel *badgeLabel = new QLabel("AI GENERATED", card);
    badgeLabel->setAlignment(Qt::AlignCenter);
    badgeLabel->setObjectName("regulationsBadge");

    QLabel *regulationsLabel = new QLabel(regulations, card);
    regulationsLabel->setWordWrap(true);
    regulationsLabel->setObjectName("regulationsText");

    QPushButton *closeBtn = new QPushButton("Close", card);
    closeBtn->setObjectName("regulationsCloseBtn");
    connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::accept);

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(zoneLabel);
    cardLayout->addWidget(detailsLabel);
    cardLayout->addSpacing(4);
    cardLayout->addWidget(badgeLabel, 0, Qt::AlignHCenter);
    cardLayout->addWidget(regulationsLabel);
    cardLayout->addSpacing(8);
    cardLayout->addWidget(closeBtn, 0, Qt::AlignRight);

    mainLayout->addWidget(card);

    dialog->setStyleSheet(
        "QDialog {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #071a2c, stop:0.35 #082136, stop:0.7 #071c2d, stop:1 #040f1a);"
        "font-family: 'Segoe UI';"
        "color: #EAF0FF;"
        "}"
        "QWidget#regulationsCard {"
        "background-color: rgba(8, 30, 55, 0.92);"
        "border: 1px solid rgba(88,184,255,0.35);"
        "border-radius: 18px;"
        "}"
        "QLabel#regulationsTitle {"
        "font-size: 22px;"
        "font-weight: 800;"
        "color: #EAF0FF;"
        "}"
        "QLabel#regulationsInfo {"
        "font-size: 15px;"
        "font-weight: 700;"
        "color: #9fd8ff;"
        "}"
        "QLabel#regulationsDetails {"
        "font-size: 12px;"
        "color: rgba(234,240,255,0.80);"
        "}"
        "QLabel#regulationsBadge {"
        "background-color: rgba(88,184,255,0.20);"
        "border: 1px solid rgba(88,184,255,0.45);"
        "border-radius: 16px;"
        "padding: 8px 16px;"
        "font-size: 13px;"
        "font-weight: 800;"
        "color: #EAF0FF;"
        "max-width: 140px;"
        "}"
        "QLabel#regulationsText {"
        "font-size: 14px;"
        "color: #EAF0FF;"
        "background-color: rgba(255,255,255,0.04);"
        "border: 1px solid rgba(255,255,255,0.10);"
        "border-radius: 12px;"
        "padding: 14px;"
        "}"
        "QPushButton#regulationsCloseBtn {"
        "background-color: rgba(88,184,255,0.18);"
        "border: 1px solid rgba(88,184,255,0.45);"
        "border-radius: 12px;"
        "padding: 10px 18px;"
        "color: #EAF0FF;"
        "font-weight: 700;"
        "min-width: 90px;"
        "}"
        "QPushButton#regulationsCloseBtn:hover {"
        "background-color: rgba(88,184,255,0.28);"
        "}"
        "QPushButton#regulationsCloseBtn:pressed {"
        "background-color: rgba(88,184,255,0.38);"
        "}"
        );

    dialog->exec();
}








//sana
// ==================all mo7sen jaballah loads==================
void SignIn::loadClients(QString search, QString sort)
{
    ui->clienttable->setRowCount(0);

    QSqlQuery query;

    QString orderBy = "";

    // 🔤 CASE-INSENSITIVE SORTING
    if(sort == "client's name ↑")
        orderBy = "ORDER BY LOWER(TYPE) ASC";

    else if(sort == "client's name ↓")
        orderBy = "ORDER BY LOWER(TYPE) DESC";

    else if(sort == "article ↑")
        orderBy = "ORDER BY LOWER(ARTICLE) ASC";

    else if(sort == "article ↓")
        orderBy = "ORDER BY LOWER(ARTICLE) DESC";

    else if(sort == "quantity ↑")
        orderBy = "ORDER BY QTE ASC";

    else if(sort == "quantity ↓")
        orderBy = "ORDER BY QTE DESC";

    QString queryStr =
        "SELECT IDCLIENTS, TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE "
        "FROM CLIENTS ";

    // 🔍 SEARCH
    if(!search.trimmed().isEmpty())
    {
        queryStr +=
            "WHERE LOWER(TYPE) LIKE LOWER('%" +
            search.trimmed() +
            "%') ";
    }

    // 📊 SORT
    if(!orderBy.isEmpty())
        queryStr += orderBy;
    else
        queryStr += "ORDER BY IDCLIENTS DESC";

    qDebug() << "FINAL QUERY =" << queryStr;

    // 🚀 EXECUTE
    if(!query.exec(queryStr))
    {
        qDebug() << "Query error:" << query.lastError();
        return;
    }

    int row = 0;

    while(query.next())
    {
        ui->clienttable->insertRow(row);

        for(int col = 0; col < 9; col++)
        {
            ui->clienttable->setItem(
                row,
                col,
                new QTableWidgetItem(
                    query.value(col).toString()
                )
            );
        }

        row++;
    }
}
// =================add a mos7sinon==================

void SignIn::on_clientaddbtn_clicked()
{
    QString name = ui->clientnameinput->text().trimmed();
    QString phone = ui->phoneinput->text().trimmed();
    QString payment = ui->choosepayment->currentText();
    QString item = ui->itemsinput->currentText();

    int quantity = ui->quantityinput->value();

    // 💰 PRICE
    bool ok;
    double price = ui->priceinput->text().toDouble(&ok);

    QDate birthDate = ui->clientdateinput->date();
    QDate today = QDate::currentDate();

    // ================= VALIDATION =================

    if(name.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Client name is required");
        return;
    }

    QRegularExpression nameRegex("^[A-Za-z ]+$");

    if(!nameRegex.match(name).hasMatch())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Name must contain only letters");
        return;
    }

    if(!phone.isEmpty())
    {
        QRegularExpression phoneRegex("^\\d{8}$");

        if(!phoneRegex.match(phone).hasMatch())
        {
            QMessageBox::warning(this,
                                 "Error",
                                 "Phone must be exactly 8 digits");
            return;
        }
    }

    if(payment.isEmpty())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Select a payment method");
        return;
    }

    if(item.isEmpty())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Select an item");
        return;
    }

    if(quantity <= 0)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Quantity must be greater than 0");
        return;
    }

    // 💰 PRICE VALIDATION
    if(!ok || price <= 0)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Enter a valid price");
        return;
    }

    if(birthDate > today)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Date of birth cannot be in the future");
        return;
    }

    int age = today.year() - birthDate.year();

    if(today.month() < birthDate.month() ||
       (today.month() == birthDate.month() &&
        today.day() < birthDate.day()))
    {
        age--;
    }

    if(age < 18)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Client must be at least 18 years old");
        return;
    }
    Client C(
        name,
        birthDate.toString("yyyy-MM-dd"),
        price,
        payment,
        "Paid",
        phone,
        item,
        quantity
    );

    if(C.ajouterClient())
    {
        QMessageBox::information(this,
                                 "Success",
                                 "Client added successfully");

        loadClients("", "");
        loadClientsFromDB();

        updateDashboard();
        setupBarChart();
        setupPieChart();

        ui->clientnameinput->clear();
        ui->phoneinput->clear();

        ui->quantityinput->setValue(0);

        ui->priceinput->clear();

        ui->itemsinput->setCurrentIndex(0);
        ui->choosepayment->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::critical(this,
                              "Error",
                              "Add failed");
    }
}
// ==================delete the mo7sinon :c==================

void SignIn::on_deleteclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    int id = ui->clienttable->item(row,0)->text().toInt();

    if(QMessageBox::question(this, "Confirm",
                              "Delete this client?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;

    Client C;

    if(C.supprimerClient(id))
    {
        QMessageBox::information(this, "Deleted", "Client deleted");
        loadClients("", "");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Delete failed");
    }
    loadClientsFromDB();
}

// ==================update the mo7sinon :DD==================

void SignIn::on_updateclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Select a client");
        return;
    }

    if(!ui->clienttable->item(row,0))
        return;

    int id =
        ui->clienttable->item(row,0)->text().toInt();

    EditClientDialog dialog(this);

    dialog.setClientData(
        ui->clienttable->item(row,1)->text(), // name
        ui->clienttable->item(row,2)->text(), // date
        ui->clienttable->item(row,6)->text(), // phone
        ui->clienttable->item(row,7)->text(), // article
        ui->clienttable->item(row,8)->text().toInt(), // quantity
        ui->clienttable->item(row,4)->text(), // payment
        ui->clienttable->item(row,3)->text().toDouble(), // price
        id
    );

    if(dialog.exec() == QDialog::Accepted)
    {
        loadClients("", "");
        loadClientsFromDB();

        updateDashboard();
        setupBarChart();
        setupPieChart();
    }
}

// ==================pdf file ama the good kind==================
void SignIn::on_clientpdfbtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "clients.pdf", "*.pdf");
    if(fileName.isEmpty()) return;
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);
    QPainter painter(&pdf);
    int margin = 100;
    int y = margin;
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(margin, y, "Clients Report");
    painter.setFont(QFont("Arial", 9));
    painter.drawText(pdf.width() - 1500, y, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    y += 200;
    int cols = ui->clienttable->columnCount();
    int rows = ui->clienttable->rowCount();
    int tableWidth = pdf.width() - 2 * margin;
    int colWidth = tableWidth / cols;
    int rowHeight = 200;
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for(int col = 0; col < cols; col++)
    {
        QRect rect(margin + col * colWidth, y, colWidth, rowHeight);
        painter.fillRect(rect, QColor(200, 200, 200));
        painter.drawRect(rect);

        QString header = ui->clienttable->horizontalHeaderItem(col)->text();
        painter.drawText(rect, Qt::AlignCenter, header);
    }
    y += rowHeight;
    painter.setFont(QFont("Arial", 9));
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            QRect rect(margin + col * colWidth, y, colWidth, rowHeight);
            if(row % 2 == 0)
                painter.fillRect(rect, QColor(245, 245, 245));
            painter.drawRect(rect);
            QTableWidgetItem *item = ui->clienttable->item(row, col);
            if(item)
                painter.drawText(rect.adjusted(5, 5, -5, -5), Qt::AlignLeft | Qt::AlignVCenter, item->text());
        }
        y += rowHeight;
        if(y > pdf.height() - margin)
        {
            pdf.newPage();
            y = margin;
        }
    }
    painter.end();
    QMessageBox::information(this, "Success", "PDF generated successfully");
    loadClientsFromDB();
}

// ==================searching for the one piece==================
void SignIn::on_searchclient_textChanged(const QString &text)
{
    loadClients(text, ui->clientsort->currentText());
    qDebug() << "Searching:" << text;
}
//==================sorting the one piece==================
void SignIn::on_clientsort_currentTextChanged(const QString &text)
{
    loadClients(ui->searchclient->text(), text);
}
//==================showing the goods==================
void SignIn::loadItems()
{
    ui->itemsinput->clear();

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);

    ui->itemsinput->addItem("----- STOCKS -----");

    if(q.exec("SELECT TYPEPOISSON FROM STOCKS"))
    {
        while(q.next())
        {
            QString val = q.value(0).toString();
            qDebug() << "STOCK:" << val;
            ui->itemsinput->addItem(val);
        }
    }
    else
    {
        qDebug() << "STOCK ERROR:" << q.lastError();
    }

    ui->itemsinput->addItem("----- EQUIPEMENTS -----");
    q.finish();

    if(q.exec("SELECT NOMEQ FROM EQUIPEMENTS"))
    {
        while(q.next())
        {
            QString val = q.value(0).toString();
            qDebug() << "EQUIPEMENT:" << val;
            ui->itemsinput->addItem(val);
        }
    }
    else
    {
        qDebug() << "EQUIPEMENTS ERROR:" << q.lastError();
    }
}
//==================maxing brrr==================
int SignIn::getMaxQuantity(QString item)
{
    QSqlQuery q;
    q.prepare("SELECT QTE FROM STOCKS WHERE TYPEPOISSON = :item");
    q.bindValue(":item", item);
    if(q.exec() && q.next())
        return q.value(0).toInt();
    q.prepare("SELECT QTE FROM EQUIPEMENTS WHERE NOMEQ = :item");
    q.bindValue(":item", item);
    if(q.exec() && q.next())
        return q.value(0).toInt();
    return 0;
}

void SignIn::on_itemsinput_currentTextChanged(const QString &text)
{
    int max = getMaxQuantity(text);
    ui->quantityinput->setMaximum(max);
    if(ui->quantityinput->value() > max)
        ui->quantityinput->setValue(max);
}

//added this elli louta lkoll
//==========================showing all the mo7sens and jaballahs mel DB=============================
void SignIn::loadClientsFromDB()
{
    ui->clienttable->setRowCount(0);

    QSqlQuery query;

    if(!query.exec("SELECT IDCLIENTS, TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE FROM CLIENTS"))
    {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    int row = 0;

    while(query.next())
    {
        ui->clienttable->insertRow(row);

        for(int col = 0; col < 9; col++)
        {
            ui->clienttable->setItem(row, col,
                                     new QTableWidgetItem(query.value(col).toString()));
        }

        row++;
    }

    qDebug() << "Loaded rows:" << row;
}
//==========================popup animation==========================
void SignIn::showAnimatedPopup(QString prediction, double confidence)
{
    QMessageBox *msg = new QMessageBox(this);

    QString text = "<div style='color:white;'>"
                   "<h3>🤖 AI Prediction</h3>";

    if(prediction.contains("No"))
        text += "<p style='color:red;'>No prediction available</p>";
    else
    {
        text += "<p><b>Item:</b> " + prediction + "</p>";
        text += "<p><b>Confidence:</b> " + QString::number(confidence, 'f', 2) + "%</p>";
    }

    text += "</div>";

    msg->setTextFormat(Qt::RichText);
    msg->setText(text);

    msg->setStyleSheet(
        "QMessageBox { background-color:#0b1e2d; }"
        "QLabel { color:white; }"
        "QPushButton { background:#1f6aa5; color:white; border-radius:6px; padding:5px; }"
        );


    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(msg);
    msg->setGraphicsEffect(effect);

    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(400);
    anim->setStartValue(0);
    anim->setEndValue(1);

    msg->show();
    anim->start();
}
//========================== smart recommendation kinda?=====================
void SignIn::on_aiclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    int clientId = ui->clienttable->item(row, 0)->text().toInt();

    loadingMsg = new QMessageBox(this);

    loadingMsg->setWindowTitle("Recommendation System");
    loadingMsg->setText("<div style='color:white;'><h3>🤖 Analyzing...</h3><p>Please wait...</p></div>");
    loadingMsg->setTextFormat(Qt::RichText);

    loadingMsg->setStyleSheet(
        "QMessageBox { background-color:#0b1e2d; }"
        "QLabel { color:white; font-size:14px; }"
        );

    loadingMsg->setStandardButtons(QMessageBox::NoButton);
    loadingMsg->show();

    QTimer::singleShot(1200, this, [=]()
                       {
                           runAIPrediction(clientId);
                       });
}
//====================loading animation==========================
void SignIn::runAIPrediction(int clientId)
{
    if(loadingMsg)
    {
        loadingMsg->close();
        delete loadingMsg;
        loadingMsg = nullptr;
    }

    Client c;
    QList<QPair<QString, double>> predictions = c.predictTop3(clientId);

    QString text = "<div style='color:white;'><h3>🤖 Smart Recommendations</h3>";

    if(predictions.isEmpty())
    {
        text += "<p style='color:red;'>No prediction available</p>";
    }
    else
    {
        for(int i = 0; i < predictions.size(); i++)
        {
            text += QString("<p>%1. <b>%2</b> (%3%)</p>")
            .arg(i + 1)
                .arg(predictions[i].first)
                .arg(QString::number(predictions[i].second, 'f', 1));
        }
    }

    text += "</div>";

    QMessageBox *msg = new QMessageBox(this);

    msg->setTextFormat(Qt::RichText);
    msg->setText(text);

    msg->setStyleSheet(
        "QMessageBox { background-color:#0b1e2d; }"
        "QLabel { color:white; font-size:14px; }"
        "QPushButton { background:#1f6aa5; color:white; border-radius:6px; padding:5px; }"
        );

    msg->show();
}


//==========flouuuuuuuuuuuuuuuuuus---------
double SignIn::getMonthlyGains()
{
    QSqlQuery query;

    query.exec(
        "SELECT NVL(SUM(MONTANT),0) "
        "FROM CLIENTS"
    );

    if(query.next())
        return query.value(0).toDouble();

    return 0;
}


//====akther 7aja tb3et========
QString SignIn::getMostSoldItem(int &quantity)
{
    QSqlQuery query;

    query.exec(
        "SELECT ARTICLE, SUM(QTE) as total "
        "FROM CLIENTS "
        "GROUP BY ARTICLE "
        "ORDER BY total DESC"
        );

    if(query.next())
    {
        quantity = query.value(1).toInt();
        return query.value(0).toString();
    }

    quantity = 0;
    return "None";
}
//---------moneeeeeeeeeeeeeeeeeeeeeeeeeeyyyyyyyyyyy===
int SignIn::getTotalPurchases()
{
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM CLIENTS");

    if(query.next())
        return query.value(0).toInt();

    return 0;
}

//===========================dashboard stuff==========================
void SignIn::updateDashboard()
{
    double gains = getMonthlyGains();
    ui->monthsgainslabel->setText(QString::number(gains, 'f', 2) + " DT");
    int qty;
    QString item = getMostSoldItem(qty);

    ui->mostsolditemlabel->setText(
        item + "\nQuantity: " + QString::number(qty)
        );
}


//=======================================classic stats========================
void SignIn::setupBarChart()
{
    QSqlQuery query;

    // 📊 gains per item
    query.exec(
        "SELECT ARTICLE, SUM(MONTANT) "
        "FROM CLIENTS "
        "GROUP BY ARTICLE "
        "ORDER BY SUM(MONTANT) DESC"
    );

    QBarSet *set = new QBarSet("Gains");

    QStringList categories;

    while(query.next())
    {
        QString item = query.value(0).toString();
        double gains = query.value(1).toDouble();

        *set << gains;
        categories << item;
    }

    // 🎨 STYLE
    set->setColor(QColor("#00c6ff"));

    // 🖱️ CLICK → DETAILS
    connect(set, &QBarSet::clicked, this,
            [=](int index)
    {
        QString item = categories[index];
        double value = set->at(index);

        QString details =
            "📊 Item Revenue\n\n"
            "Item: " + item +
            "\nTotal Gains: " +
            QString::number(value, 'f', 2) + " DT";

        showStyledPopup(details);
    });

    // 📊 SERIES
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // 📈 CHART
    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("Revenue by Item");

    chart->setBackgroundBrush(QColor("#0b1e2d"));
    chart->setTitleBrush(QBrush(Qt::white));

    chart->legend()->setVisible(true);
    chart->legend()->setLabelColor(Qt::white);

    // 📊 AXES
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(Qt::white);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // ✨ ANIMATION
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 🧼 CLEAN OLD
    if(ui->chart1->layout())
    {
        QLayout *layout = ui->chart1->layout();

        while(layout->count())
        {
            QWidget *w = layout->itemAt(0)->widget();
            layout->removeWidget(w);
            delete w;
        }
    }
    else
    {
        ui->chart1->setLayout(new QVBoxLayout());
    }

    // 🖼️ DISPLAY
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent");

    ui->chart1->layout()->addWidget(view);
}
//==============================stats the round type=======================================
void SignIn::setupPieChart()
{
    QSqlQuery query;

    query.exec(
        "SELECT ARTICLE, COUNT(*) "
        "FROM CLIENTS "
        "GROUP BY ARTICLE"
        );

    QPieSeries *series = new QPieSeries();

    // 🎨 Modern color palette
    QList<QColor> colors = {
        QColor("#00c6ff"),
        QColor("#0072ff"),
        QColor("#00ffb3"),
        QColor("#ff7b00"),
        QColor("#ff3c3c"),
        QColor("#a855f7")
    };

    int colorIndex = 0;

    while(query.next())
    {
        QString item = query.value(0).toString();
        int count = query.value(1).toInt();

        QPieSlice *slice = series->append(item, count);
        slice->setBrush(colors[colorIndex % colors.size()]);
        colorIndex++;
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelFont(QFont("Segoe UI", 10, QFont::Bold));
        connect(slice, &QPieSlice::hovered, this, [=](bool state)
                {
                    slice->setExploded(state);
                    slice->setExplodeDistanceFactor(0.1);
                });
        connect(slice, &QPieSlice::clicked, this, [=]()
                {
                    int total = 0;

                    for(QPieSlice *s : series->slices())
                        total += s->value();

                    double percent = (slice->value() / total) * 100;
                    slice->setExploded(true);
                    slice->setExplodeDistanceFactor(0.15);

                    QString details =
                        "Item Details\n\n"
                        "Item: " + slice->label() +
                        "\nSold: " + QString::number(slice->value()) +
                        "\nPercentage: " + QString::number(percent, 'f', 1) + "%";

                    showStyledPopup(details);
                });
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Demand Distribution");
    chart->setBackgroundBrush(QColor("#0b1e2d"));
    chart->setTitleBrush(QBrush(Qt::white));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(Qt::white);
    chart->setAnimationOptions(QChart::AllAnimations);
    if(ui->chart2->layout())
    {
        QLayout *layout = ui->chart2->layout();

        while(layout->count())
        {
            QWidget *w = layout->itemAt(0)->widget();
            layout->removeWidget(w);
            delete w;
        }
    }
    else
    {
        ui->chart2->setLayout(new QVBoxLayout());
    }

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent");

    ui->chart2->layout()->addWidget(view);
}
//=======================dashboard pdf file good kind version============================================
void SignIn::on_pdfitembtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save PDF", "dashboard.pdf", "*.pdf");

    if(fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);

    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    int width = pdf.width();
    int height = pdf.height();
    int margin = 60;

    // ===================== PAGE 1 =====================
    painter.fillRect(0, 0, width, height, QColor("#0b1e2d"));

    int y = margin;
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 24, QFont::Bold));
    painter.drawText(QRect(0, y, width, 100),
                     Qt::AlignCenter,
                     "Client Dashboard Report");

    y += 200;
    painter.setPen(QColor("#aaaaaa"));
    painter.setFont(QFont("Segoe UI", 11));
    painter.drawText(QRect(0, y, width, 40),
                     Qt::AlignCenter,
                     QDateTime::currentDateTime().toString("dd MMM yyyy - hh:mm"));

    y += 250;

    int cardWidth = (width - 3 * margin) / 2;
    int cardHeight = 500;
    QRect gainsCard(margin, y, cardWidth, cardHeight);

    painter.setBrush(QColor("#132f4c"));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(gainsCard, 15, 15);
    painter.setPen(QColor("#00c6ff"));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(gainsCard.adjusted(20, 15, -20, -60),
                     Qt::TextWordWrap,
                     "This Month's Gains");
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 20, QFont::Bold));
    painter.drawText(gainsCard.adjusted(20, 45, -20, -10),
                     Qt::TextWordWrap,
                     ui->monthsgainslabel->text());
    QRect soldCard(2 * margin + cardWidth, y, cardWidth, cardHeight);

    painter.setBrush(QColor("#132f4c"));
    painter.drawRoundedRect(soldCard, 15, 15);
    painter.setPen(QColor("#00c6ff"));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(soldCard.adjusted(20, 15, -20, -60),
                     Qt::TextWordWrap,
                     "Most Sold Item");
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 18, QFont::Bold));
    painter.drawText(soldCard.adjusted(20, 45, -20, -10),
                     Qt::TextWordWrap,
                     ui->mostsolditemlabel->text());
    painter.setPen(QColor("#888888"));
    painter.setFont(QFont("Segoe UI", 9));
    painter.drawText(QRect(0, height - 50, width, 30),
                     Qt::AlignCenter,
                     "Generated by BORT System");

    // ===================== PAGE 2 =====================
    pdf.newPage();

    painter.fillRect(0, 0, width, height, QColor("#0b1e2d"));

    y = margin;
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 20, QFont::Bold));
    painter.drawText(QRect(0, y, width, 100),
                     Qt::AlignCenter,
                     "Charts Overview");

    y += 60;
    QPixmap chart1 = ui->chart1->grab();
    QPixmap chart2 = ui->chart2->grab();
    int chartWidth = (width - 3 * margin) / 2;
    int chartHeight = height - y - 60;
    QPixmap scaled1 = chart1.scaled(chartWidth, chartHeight,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    QPixmap scaled2 = chart2.scaled(chartWidth, chartHeight,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);
    int x1 = margin;
    int x2 = 2 * margin + chartWidth;
    int yCentered1 = y + (chartHeight - scaled1.height()) / 2;
    int yCentered2 = y + (chartHeight - scaled2.height()) / 2;
    QRect bg1(x1 - 10, yCentered1 - 10,
              scaled1.width() + 20, scaled1.height() + 20);

    QRect bg2(x2 - 10, yCentered2 - 10,
              scaled2.width() + 20, scaled2.height() + 20);

    painter.setBrush(QColor("#132f4c"));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bg1, 15, 15);
    painter.drawRoundedRect(bg2, 15, 15);
    painter.drawPixmap(
        x1 + (chartWidth - scaled1.width()) / 2,
        yCentered1,
        scaled1
        );

    painter.drawPixmap(
        x2 + (chartWidth - scaled2.width()) / 2,
        yCentered2,
        scaled2
        );
    painter.setPen(QColor("#888888"));
    painter.setFont(QFont("Segoe UI", 9));
    painter.drawText(QRect(0, height - 40, width, 30),
                     Qt::AlignCenter,
                     "Charts generated dynamically from database");

    painter.end();
    QMessageBox::information(this, "Success",
                             "PDF exported!");
}


//===================styyle
void SignIn::showStyledPopup(QString text)
{
    QMessageBox *msg = new QMessageBox(this);

    msg->setWindowTitle("AI Prediction");
    msg->setText(text);

    msg->setStyleSheet(
        "QMessageBox {"
        " background-color:#0b1e2d;"
        " color:white;"
        " font-size:14px;"
        "}"
        "QLabel { color:white; }"
        "QPushButton {"
        " background-color:#1f6aa5;"
        " color:white;"
        " padding:8px 16px;"
        " border-radius:6px;"
        "}"
        "QPushButton:hover { background-color:#00c6ff; }"
        );

    msg->exec();
}

//==========================dashboard jannet l3arrafa 7out w flous ya baba==============================================
void SignIn::on_aipredictionbtndashboard_clicked()
{
    showAIPopup();
}
//======kaboom kablaw kaboom===============
void SignIn::showAIPopup()
{
    QMessageBox msg(this);
    msg.setWindowTitle("AI System");
    msg.setText("Choose prediction type:");

    QPushButton *gainsBtn = msg.addButton("📊 Gains / Losses", QMessageBox::ActionRole);
    QPushButton *fishBtn = msg.addButton("🐟 Best Fish", QMessageBox::ActionRole);

    msg.setStyleSheet(
        "QMessageBox { background-color:#0b1e2d; }"
        "QPushButton { background:#1f6aa5; color:white; padding:8px; border-radius:6px; }"
        "QLabel { color:white; font-size:14px; }"
        );

    msg.exec();

    if(msg.clickedButton() == gainsBtn)
        predictGains();
    else if(msg.clickedButton() == fishBtn)
        predictBestFish();
}

//==================ai like system ljannet l3arrafa lel money
void SignIn::predictGains()
{
    QSqlQuery query;

    query.exec(
        "SELECT TO_CHAR(DATECL,'MM'), SUM(MONTANT) "
        "FROM CLIENTS "
        "GROUP BY TO_CHAR(DATECL,'MM') "
        "ORDER BY TO_CHAR(DATECL,'MM')"
        );

    QList<double> months;

    while(query.next())
        months.append(query.value(1).toDouble());

    if(months.size() < 4)
    {
        showStyledPopup("Not enough data for reliable prediction.");
        return;
    }
    double avg = 0;
    for(int i = months.size()-4; i < months.size(); i++)
        avg += months[i];
    avg /= 4.0;
    double trend1 = months[months.size()-1] - months[months.size()-2];
    double trend2 = months[months.size()-2] - months[months.size()-3];
    double trend = (trend1 + trend2) / 2.0;
    double predicted = avg + trend * 0.6;
    double learned = Client::fishScores["global_gain"];
    predicted += learned * 0.1;
    double minLimit = months.last() * 0.7;
    double maxLimit = months.last() * 1.3;
    predicted = qBound(minLimit, predicted, maxLimit);
    Client::updateFishScore("global_gain", trend * 0.03);
    Client::saveAI();
    double variation = abs(trend1 - trend2);
    double confidence = qMax(60.0, 100 - variation * 5);
    double rangeMin = predicted * 0.9;
    double rangeMax = predicted * 1.1;
    QString trendText;
    if(trend > 0)
        trendText = "Growth";
    else if(trend < 0)
        trendText = "Decline";
    else
        trendText = "Stable";

    QString result =
        "Advanced Financial Prediction\n\n"
        "Average (4 months): " + QString::number(avg, 'f', 2) + " DT\n"
                                         "Predicted: " + QString::number(predicted, 'f', 2) + " DT\n\n"
                                               "Range: " + QString::number(rangeMin, 'f', 2) +
        " → " + QString::number(rangeMax, 'f', 2) + " DT\n\n"
                                                    "Trend: " + trendText +
        "\nConfidence: " + QString::number(confidence, 'f', 1) + "%";

    showStyledPopup(result);
}
//===============bel 7out 3lik yazzayn=======================
void SignIn::predictBestFish()
{
    QSqlQuery query;

    query.exec(
        "SELECT ARTICLE, COUNT(*) AS freq "
        "FROM CLIENTS "
        "GROUP BY ARTICLE"
    );

    QString bestFish;

    double bestScore = -1;

    while(query.next())
    {
        QString fish =
            query.value(0)
                .toString()
                .toLower()
                .trimmed();

        // 🐟 CHECK IF ARTICLE EXISTS IN STOCKS
        QSqlQuery stockQuery;

        stockQuery.prepare(
            "SELECT COUNT(*) "
            "FROM STOCKS "
            "WHERE LOWER(TYPEPOISSON) = :fish"
        );

        stockQuery.bindValue(
            ":fish",
            fish
        );

        stockQuery.exec();

        bool existsInStocks = false;

        if(stockQuery.next())
        {
            existsInStocks =
                stockQuery.value(0).toInt() > 0;
        }

        // ❌ ignore equipment
        if(!existsInStocks)
            continue;

        int freq =
            query.value(1).toInt();

        // 🧠 AI learning bonus
        double learned =
            Client::fishScores[fish];

        double score =
            freq + learned;

        if(score > bestScore)
        {
            bestScore = score;
            bestFish = fish;
        }
    }

    // ================= RESULT =================

    if(!bestFish.isEmpty())
    {
        Client::updateFishScore(
            bestFish,
            0.5
        );

        Client::saveAI();

        QString result =
            "🐟 Smart Fish Prediction\n\n"

            "Best Fish: " + bestFish +

            "\nScore: " +
            QString::number(
                bestScore,
                'f',
                2
            ) +

            "\n(Based on demand and AI learning)";

        showStyledPopup(result);
    }
    else
    {
        showStyledPopup(
            "No fish data available."
        );
    }
}
//===============ki nenzel easy input
void SignIn::on_vocalstuffbtn_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Quick Client Input");

    dialog.setLabelText(
        "Enter client information:\n\n"

        "Examples:\n\n"

        "mary ann 16/07/1990 11223344 shrimp 2 150 cash\n\n"

        "shrmp 3 80 card\n\n"

        "john tuna 5 220\n\n"

        "Format:\n"
        "name date phone item quantity price payment"
    );

    dialog.setStyleSheet(
        "QDialog {"
        " background-color:#0b1e2d;"
        "}"

        "QLabel {"
        " color:white;"
        " font-size:13px;"
        "}"

        "QPlainTextEdit {"
        " background:#132f4c;"
        " color:white;"
        " border-radius:6px;"
        " padding:6px;"
        "}"

        "QPushButton {"
        " background:#1f6aa5;"
        " color:white;"
        " padding:6px 12px;"
        " border-radius:6px;"
        "}"

        "QPushButton:hover {"
        " background:#00c6ff;"
        "}"
    );

    if(dialog.exec() == QDialog::Accepted)
    {
        QString text =
            dialog.textValue().trimmed();

        if(!text.isEmpty())
        {
            processQuickInput(text);

            showStyledPopup(
                "✔ Information filled successfully."
            );
        }
    }
}
//-----------------nchouf 9addeh similar lasemi mta3 larticle ken ghlotet y7ott ess7i7======
int SignIn::levenshteinDistance(const QString &s1, const QString &s2)
{
    int len1 = s1.size(), len2 = s2.size();
    QVector<QVector<int>> dp(len1 + 1, QVector<int>(len2 + 1));

    for(int i = 0; i <= len1; i++) dp[i][0] = i;
    for(int j = 0; j <= len2; j++) dp[0][j] = j;

    for(int i = 1; i <= len1; i++)
    {
        for(int j = 1; j <= len2; j++)
        {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            dp[i][j] = std::min({
                dp[i-1][j] + 1,
                dp[i][j-1] + 1,
                dp[i-1][j-1] + cost
            });
        }
    }

    return dp[len1][len2];
}

//==================easy input stuff=========================
void SignIn::processQuickInput(QString text)
{
    text = text.toLower().trimmed();

    QStringList words =
        text.split(QRegularExpression("\\s+"));

    QString name;
    QString phone;
    QString item;
    QString payment;

    int quantity = -1;

    double price = -1;

    QDate date;

    QStringList nameParts;

    for(const QString &word : words)
    {
        // ================= DATE =================
        QDate d =
            QDate::fromString(word, "dd/MM/yyyy");

        if(d.isValid())
        {
            date = d;
            continue;
        }

        // ================= PHONE =================
        if(word.length() == 8 &&
           word.toInt() > 0)
        {
            phone = word;
            continue;
        }

        // ================= NUMBERS =================
        bool ok;

        double num =
            word.toDouble(&ok);

        if(ok)
        {
            // 🔢 quantity
            if(quantity == -1 &&
               word.contains(
                   QRegularExpression("^\\d+$")))
            {
                quantity = (int)num;
            }
            // 💰 price
            else if(price == -1)
            {
                price = num;
            }

            continue;
        }

        // ================= PAYMENT =================
        if(word.contains("cash"))
        {
            payment = "cash";
            continue;
        }

        if(word.contains("card"))
        {
            payment = "card";
            continue;
        }

        if(word.contains("transfer"))
        {
            payment = "transfer";
            continue;
        }

        // ================= ITEM DETECTION =================

        bool isItem = false;

        // 🐟 STOCK ITEMS
        for(int j = 0;
            j < ui->itemsinput->count();
            j++)
        {
            QString comboItem =
                ui->itemsinput
                    ->itemText(j)
                    .toLower()
                    .trimmed();

            int dist =
                levenshteinDistance(
                    word,
                    comboItem
                );

            if(dist <= 2 ||
               comboItem.contains(word))
            {
                item = comboItem;

                isItem = true;

                break;
            }
        }

        // ⚙️ EQUIPMENT ITEMS
        if(!isItem)
        {
            QSqlQuery equipmentQuery;

            equipmentQuery.exec(
                "SELECT NAME FROM EQUIPEMENTS"
            );

            while(equipmentQuery.next())
            {
                QString equipment =
                    equipmentQuery.value(0)
                        .toString()
                        .toLower()
                        .trimmed();

                int dist =
                    levenshteinDistance(
                        word,
                        equipment
                    );

                if(dist <= 2 ||
                   equipment.contains(word))
                {
                    item = equipment;

                    isItem = true;

                    break;
                }
            }
        }

        // ================= NAME =================
        if(!isItem &&
           !word.contains("/") &&
           !word.toInt())
        {
            nameParts.append(word);
        }
    }

    // ================= FORMAT NAME =================

    if(!nameParts.isEmpty())
    {
        QStringList parts = nameParts;

        for(QString &p : parts)
        {
            if(!p.isEmpty())
                p[0] = p[0].toUpper();
        }

        name = parts.join(" ");
    }

    // ================= APPLY VALUES =================

    if(!name.isEmpty())
        ui->clientnameinput->setText(name);

    if(date.isValid())
        ui->clientdateinput->setDate(date);

    if(!phone.isEmpty())
        ui->phoneinput->setText(phone);

    // ⚠️ only set combo if stock item exists
    if(!item.isEmpty())
    {
        int comboIndex =
            ui->itemsinput->findText(
                item,
                Qt::MatchFixedString
            );

        if(comboIndex >= 0)
            ui->itemsinput->setCurrentIndex(comboIndex);
        else
            ui->itemsinput->setEditText(item);
    }

    if(quantity != -1)
        ui->quantityinput->setValue(quantity);

    // 💰 PRICE
    if(price != -1)
    {
        ui->priceinput->setText(
            QString::number(price)
        );
    }

    if(!payment.isEmpty())
        ui->choosepayment->setCurrentText(payment);

    showStyledPopup("✔ Easy input processed.");
}
void SignIn::updateInsights()
{
    QString insight;

    if(ui->monthsgainslabel->text().contains("pred"))
        insight += " Growth trend detected\n";

    insight += "🐟 Demand driven by frequent purchases\n";
    insight += "💡 Consider increasing stock for top items";

    showStyledPopup(insight);
}







//malik

void SignIn::on_visual_stock_clicked()
{
    QModelIndex index = ui->table_stock->currentIndex();
    if (!index.isValid())
        return;

    QString typePoisson = ui->table_stock->model()->data(
                                                      ui->table_stock->model()->index(index.row(), 2)
                                                      ).toString().toLower();

    int qte = ui->table_stock->model()->data(
                                          ui->table_stock->model()->index(index.row(), 1)
                                          ).toInt();

    QString etat = ui->table_stock->model()->data(
                                               ui->table_stock->model()->index(index.row(), 3)
                                               ).toString();

    QString basePath = QCoreApplication::applicationDirPath() + "/Images/";

    QString filePath;

    if(typePoisson == "octopus")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/octo.OBJ";
    }
    else if(typePoisson == "fish")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/fish.obj";
    }
    else if(typePoisson == "squid")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/squid.obj";
    }
    else if(typePoisson == "humpback whale")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/humpback.OBJ";
    }
    else if(typePoisson == "salmon")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/SALMON.OBJ";
    }
    else if(typePoisson == "tuna")
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/TUNA.OBJ";
    }
    else if(typePoisson == "alien") //
    {
        filePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/alien.obj";
    }

    if(filePath.isEmpty())
        return;

    // ---------------- CREATE WINDOW ----------------
    QDialog *viewer = new QDialog(this);
    viewer->setWindowTitle("3D Viewer");
    viewer->resize(900, 600);
    viewer->setStyleSheet("background-color: #1e1e1e; color: white;");

    QHBoxLayout *mainLayout = new QHBoxLayout(viewer);

    // ---------------- 3D VIEW ----------------
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(Qt::black));

    QWidget *container = QWidget::createWindowContainer(view);
    container->setMinimumSize(500, 500);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    view->setRootEntity(rootEntity);

    // Camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 300));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *camController =
        new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);
    camController->setLinearSpeed(400.0f);
    camController->setLookSpeed(200.0f);
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 2000.0f);

    // Light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor(Qt::white);
    light->setIntensity(1.0f);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(QVector3D(0, 0, 100));
    lightEntity->addComponent(lightTransform);

    // ---------------- MODEL ----------------
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(filePath));

    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(200, 100, 100));
    material->setSpecular(QColor(50, 50, 50));
    material->setShininess(1.0f);

    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
    transform->setScale(50.0f);
    transform->setRotation(QQuaternion::fromEulerAngles(30, 180, 0));

    entity->addComponent(mesh);
    entity->addComponent(material);
    entity->addComponent(transform);

    // ---------------- STATS PANEL ----------------
    QWidget *statsPanel = new QWidget();
    statsPanel->setMinimumWidth(250);

    QString bgColor;

    if (etat == "Perfect")
    {
        bgColor = "#2ecc71"; // 🟢 green
    }
    else if (etat == "Passable")
    {
        bgColor = "#f1c40f"; // 🟡 yellow
    }
    else if (etat == "Bad")
    {
        bgColor = "#e74c3c"; // 🔴 red
    }
    else
    {
        bgColor = "#7f8c8d"; // ⚪ fallback (unknown)
    }

    statsPanel->setStyleSheet(QString(
                                  "background-color:%1; border-radius:10px; padding:15px;"
                                  ).arg(bgColor));

    QVBoxLayout *statsLayout = new QVBoxLayout(statsPanel);

    QLabel *title = new QLabel(typePoisson.toUpper());
    title->setStyleSheet("font-size:20px; font-weight:bold; color:white;");

    QLabel *quantity = new QLabel("Quantity: " + QString::number(qte));
    QLabel *status = new QLabel("Status: " + etat);

    quantity->setStyleSheet("font-size:16px;");
    status->setStyleSheet("font-size:16px;");

    statsLayout->addWidget(title);
    statsLayout->addSpacing(20);
    statsLayout->addWidget(quantity);
    statsLayout->addWidget(status);
    statsLayout->addStretch();

    // ---------------- ADD TO WINDOW ----------------
    mainLayout->addWidget(container, 3);
    mainLayout->addWidget(statsPanel, 1);

    viewer->exec();

}
void SignIn::on_addspecies_stock_clicked()
{
    qDebug() << "BUTTON CLICKED";

    bool ok;
    int qte = ui->quantity_stock->text().toInt(&ok);
    QString type = ui->speciesname_stock->text().trimmed();
    QString etat = ui->status_stock->currentText();

    // 🔴 Validate quantity
    if (!ok || ui->quantity_stock->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid input", "Quantity must be a valid number!");
        return;
    }

    // 🔴 Validate name (type)
    if (type.isEmpty())
    {
        QMessageBox::warning(this, "Invalid input", "Name cannot be empty!");
        return;
    }

    // 🔴 Validate status (first item = default placeholder)
    if (ui->status_stock->currentIndex() == 0)
    {
        QMessageBox::warning(this, "Invalid input", "Please select a valid status!");
        return;
    }

    qDebug() << qte << type << etat;

    Stock s(qte, type, etat);

    if(s.ajouter())
    {
        QMessageBox::information(this, "Success", "Stock added!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Insert failed!");
    }
}

void SignIn::on_exportpdf_stock_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    QTableView *table = ui->table_stock;
    QAbstractItemModel *model = table->model();

    if (!model)
        return;

    int rows = model->rowCount();
    int cols = model->columnCount();

    int startX = 100;
    int startY = 200;
    int rowHeight = 80;

    // Title
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.drawText(startX, 100, "Stock Report");

    // 🔥 USE PAINTER FONT METRICS (IMPORTANT FIX)
    painter.setFont(QFont("Arial", 12));
    QFontMetrics metrics = painter.fontMetrics();

    QVector<int> colWidths;

    for (int col = 0; col < cols; col++)
    {
        int maxWidth = 0;

        // Header
        QString header = model->headerData(col, Qt::Horizontal).toString();
        maxWidth = metrics.horizontalAdvance(header);

        // Data
        for (int row = 0; row < rows; row++)
        {
            QString data = model->data(model->index(row, col)).toString();
            int textWidth = metrics.horizontalAdvance(data);

            if (textWidth > maxWidth)
                maxWidth = textWidth;
        }

        // Scale for PDF + padding
        maxWidth = maxWidth * 1.5 + 40;

        // Limits
        if (maxWidth < 150)
            maxWidth = 150;

        if (maxWidth > 400)
            maxWidth = 400;

        colWidths.append(maxWidth);
    }

    // Headers
    painter.setFont(QFont("Arial", 12, QFont::Bold));

    int x = startX;

    for (int col = 0; col < cols; col++)
    {
        QRect rect(x, startY, colWidths[col], rowHeight);
        painter.drawRect(rect);

        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(rect, Qt::AlignCenter, header);

        x += colWidths[col];
    }

    // Data (NO WRAP)
    painter.setFont(QFont("Arial", 11));

    for (int row = 0; row < rows; row++)
    {
        x = startX;

        for (int col = 0; col < cols; col++)
        {
            QRect rect(x,
                       startY + (row + 1) * rowHeight,
                       colWidths[col],
                       rowHeight);

            painter.drawRect(rect);

            QString data = model->data(model->index(row, col)).toString();

            painter.drawText(rect, Qt::AlignCenter, data);

            x += colWidths[col];
        }
    }

    painter.end();

    QMessageBox::information(this, "Export PDF", "Export done.");
}



void SignIn::on_recognition_stock_clicked()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("AI Object Recognition");
    dialog->resize(520, 600);

    dialog->setStyleSheet(R"(
        QDialog {
            background-color: #121212;
        }
        QLabel {
            color: white;
            font-size: 14px;
        }
        QPushButton {
            background-color: #2d89ef;
            color: white;
            border-radius: 8px;
            padding: 8px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #1b6fd1;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    // ===== IMAGE (CENTERED) =====
    QLabel *imageLabel = new QLabel();
    imageLabel->setFixedSize(360, 240);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(R"(
        border: 2px dashed #444;
        border-radius: 10px;
        background-color: #1e1e1e;
    )");

    // force center horizontally
    QHBoxLayout *imageContainer = new QHBoxLayout();
    imageContainer->addStretch();
    imageContainer->addWidget(imageLabel);
    imageContainer->addStretch();

    // ===== RESULT =====
    QLabel *objectLabel = new QLabel("Upload an image to start AI detection...");
    objectLabel->setAlignment(Qt::AlignCenter);
    objectLabel->setWordWrap(true);
    objectLabel->setStyleSheet("font-size: 15px; font-weight: bold;");

    // ===== BUTTONS =====
    QPushButton *uploadButton = new QPushButton("📁 Upload Image");
    QPushButton *correctButton = new QPushButton("🧠 Teach AI");
    correctButton->setVisible(false);

    layout->addLayout(imageContainer);
    layout->addWidget(uploadButton);
    layout->addWidget(objectLabel);
    layout->addWidget(correctButton);

    QString basePath = "C:/Users/Fatma/Desktop/projetbort/integrationCRUD/Images/dataset/";

    // IMPORTANT: keep image accessible outside lambda
    QSharedPointer<QImage> currentImage = QSharedPointer<QImage>::create();

    // ===== UPLOAD + RECOGNITION =====
    QObject::connect(uploadButton, &QPushButton::clicked, dialog, [=]() mutable {

        QString fileName = QFileDialog::getOpenFileName(
            dialog,
            "Select Image",
            "",
            "Images (*.png *.jpg *.jpeg)"
            );

        if(fileName.isEmpty())
            return;

        QPixmap pix(fileName);
        imageLabel->setPixmap(pix.scaled(360, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        objectLabel->setText("🧠 AI analyzing...");
        QCoreApplication::processEvents();

        currentImage->load(fileName);
        if(currentImage->isNull())
        {
            objectLabel->setText("Invalid image.");
            return;
        }

        QImage input = currentImage->scaled(64, 64);

        QDir baseDir(basePath);
        QStringList categories = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

        double bestScore = 1e18;
        QString bestMatch = "Unknown";

        for(const QString &category : categories)
        {
            QDir categoryDir(basePath + category);
            QStringList images = categoryDir.entryList(QStringList() << "*.jpg" << "*.png" << "*.jpeg");

            for(const QString &imgName : images)
            {
                QImage ref(categoryDir.filePath(imgName));
                if(ref.isNull()) continue;

                ref = ref.scaled(64, 64);

                double diff = 0;

                for(int y = 0; y < 64; y++)
                {
                    for(int x = 0; x < 64; x++)
                    {
                        QColor c1 = input.pixelColor(x,y);
                        QColor c2 = ref.pixelColor(x,y);

                        diff += abs(c1.red() - c2.red());
                        diff += abs(c1.green() - c2.green());
                        diff += abs(c1.blue() - c2.blue());
                    }
                }

                if(diff < bestScore)
                {
                    bestScore = diff;
                    bestMatch = category;
                }
            }
        }

        double maxPossible = 64 * 64 * 3 * 255;
        double confidence = 100.0 * (1.0 - (bestScore / maxPossible));

        QString resultText;

        if(bestMatch == "Unknown" || confidence < 40)
        {
            resultText = "❌ Not recognized\nConfidence: " +
                         QString::number(confidence, 'f', 1) + "%";
        }
        else
        {
            resultText = "✅ Detected: " + bestMatch +
                         "\n📊 Confidence: " + QString::number(confidence, 'f', 1) + "%";
        }

        objectLabel->setText(resultText);

        correctButton->setVisible(true);
    });

    // ===== TEACH AI (FIXED BACK TO WORKING STATE) =====
    QObject::connect(correctButton, &QPushButton::clicked, dialog, [=]() mutable {

        if(currentImage->isNull())
            return;

        bool ok;
        QString correctLabel = QInputDialog::getText(
            dialog,
            "Teach AI",
            "What is the correct object?",
            QLineEdit::Normal,
            "",
            &ok
            );

        if(!ok || correctLabel.isEmpty())
            return;

        QString categoryPath = basePath + correctLabel + "/";

        QDir dir;
        if(!dir.exists(categoryPath))
            dir.mkpath(categoryPath);

        QString newFile = categoryPath +
                          "img_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".jpg";

        currentImage->save(newFile);

        QMessageBox::information(dialog, "Learning",
                                 "✅ Learned! Next time it will improve.");

        correctButton->setVisible(false);
    });

    dialog->exec();
}

void SignIn::on_charts_stock_clicked()
{
    qDebug() << "charts_stock clicked!";

    // ===== GET MODEL =====
    QAbstractItemModel *model = ui->table_stock->model();
    int rowCount = model->rowCount();

    if (rowCount == 0)
    {
        qDebug() << "No data in table!";
        return;
    }

    // ===== GROUP DATA =====
    QMap<QString, int> fishTotals;

    for (int i = 0; i < rowCount; ++i)
    {
        int quantity = model->index(i, 1).data().toInt(); // QTE
        QString fishType = model->index(i, 2).data().toString(); // TYPEPOISSON

        fishTotals[fishType] += quantity;
    }

    // ===== CREATE BAR SET =====
    QBarSet *set = new QBarSet("Quantity");

    QStringList categories;

    for (auto it = fishTotals.begin(); it != fishTotals.end(); ++it)
    {
        *set << it.value();
        categories << it.key();
    }

    // ===== SERIES =====
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // ===== CHART =====
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Fish Stock Overview");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // ===== AXES =====
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Fish Type");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantity");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // ===== VIEW =====
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // ===== POPUP WINDOW (QDialog) =====
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Stock Chart Visualization");
    dialog->resize(900, 600);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);

    dialog->setLayout(layout);

    dialog->exec(); // 🔥 This makes it a modal popup
}

void SignIn::on_edit_stock_clicked()
{
    qDebug() << "EDIT BUTTON CLICKED";

    QModelIndex index = ui->table_stock->currentIndex();
    if(!index.isValid())
    {
        QMessageBox::warning(this, "Error", "Select a row!");
        return;
    }

    int row = index.row();
    int id = ui->table_stock->model()->index(row, 0).data().toInt();

    int qte = ui->quantity_stock->text().toInt();
    QString type = ui->speciesname_stock->text();
    QString etat = ui->status_stock->currentText();

    qDebug() << "ID:" << id << "QTE:" << qte << "TYPE:" << type << "ETAT:" << etat;

    Stock s(qte, type, etat);

    if(s.modifier(id))
    {
        QMessageBox::information(this, "Success", "Updated!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Update failed!");
    }
}

void SignIn::on_delete_stock_clicked()
{
    int row = ui->table_stock->currentIndex().row();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a row!");
        return;
    }

    int id = ui->table_stock->model()->index(row, 0).data().toInt();

    Stock s;

    if(s.supprimer(id))
    {
        QMessageBox::information(this, "Success", "Deleted!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Delete failed!");
    }
}

void SignIn::refreshStockTable()
{
    Stock s;
    QSqlQueryModel* model = s.afficher();
    ui->table_stock->setModel(nullptr);
    ui->table_stock->setModel(model);
    ui->table_stock->setModel(s.afficher());
}
void SignIn::on_table_stock_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->quantity_stock->setText(
        ui->table_stock->model()->index(row, 1).data().toString()
        );

    ui->speciesname_stock->setText(
        ui->table_stock->model()->index(row, 2).data().toString()
        );

    ui->status_stock->setCurrentText(
        ui->table_stock->model()->index(row, 3).data().toString()
        );
}
void SignIn::on_search_stock_textChanged(const QString &text)
{
    proxyModel->setFilterKeyColumn(2); // TYPEPOISSON column index
    proxyModel->setFilterFixedString(text);
}
void SignIn::on_sort_stock_currentTextChanged(const QString &text)
{
    if (text == "Name")          // ✅ updated
        proxyModel->sort(2);     // TYPEPOISSON
    else if (text == "Quantity")
        proxyModel->sort(1);     // QTE
    else if (text == "Status")
        proxyModel->sort(3);     // ETAT
}

//nour

// ═══════════════════════════════════════════════════════════════════
//  STYLE CONSTANTS
// ═══════════════════════════════════════════════════════════════════

static const QString kField = R"(
    QLineEdit, QSpinBox, QComboBox {
        background-color: rgba(8,28,52,0.90);
        border: 1.5px solid rgba(79,195,247,0.32);
        border-radius: 10px;
        padding: 7px 14px;
        font-size: 13px;
        color: #EAF0FF;
        min-height: 38px;
        selection-background-color: #0288d1;
    }
    QLineEdit:focus, QSpinBox:focus, QComboBox:focus {
        border: 1.5px solid #29b6f6;
        background-color: rgba(41,182,246,0.07);
    }
    QLineEdit:hover, QSpinBox:hover, QComboBox:hover {
        border: 1.5px solid rgba(79,195,247,0.58);
    }
    QSpinBox::up-button, QSpinBox::down-button {
        background-color: rgba(41,182,246,0.18);
        border: none; width: 24px; border-radius: 5px; margin: 1px;
    }
    QSpinBox::up-button:hover, QSpinBox::down-button:hover {
        background-color: rgba(41,182,246,0.38);
    }
    QSpinBox::up-arrow {
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-bottom: 6px solid #4fc3f7;
    }
    QSpinBox::down-arrow {
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-top: 6px solid #4fc3f7;
    }
    QComboBox::drop-down { border: none; width: 26px; }
    QComboBox::down-arrow {
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-top: 6px solid #4fc3f7;
        margin-right: 6px;
    }
    QComboBox QAbstractItemView {
        background-color: #0d2b45;
        border: 1.5px solid #29b6f6;
        border-radius: 8px;
        color: #EAF0FF;
        selection-background-color: rgba(33,150,243,0.35);
        padding: 4px;
        font-size: 13px;
    }
)";

static const QString kLabel = R"(
    QLabel {
        color: #b3d9ff;
        font-size: 12px;
        font-weight: 800;
        letter-spacing: 0.8px;
        background: transparent;
    }
)";

// ═══════════════════════════════════════════════════════════════════
//  HELPER — cherche récursivement un widget dans tous les layouts
//           et le remplace par newW. Retourne true si trouvé.
// ═══════════════════════════════════════════════════════════════════

static bool replaceWidgetInLayout(QLayout *layout, QWidget *oldW, QWidget *newW)
{
    if (!layout) return false;
    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem *item = layout->itemAt(i);
        if (!item) continue;

        // Remplacement direct
        if (item->widget() == oldW) {
            layout->replaceWidget(oldW, newW);
            oldW->hide();
            return true;
        }

        // Descente récursive dans les sous-layouts
        if (item->layout()) {
            if (replaceWidgetInLayout(item->layout(), oldW, newW))
                return true;
        }

        // Descente dans les QGroupBox / QFrame / QWidget containers
        if (QWidget *w = item->widget()) {
            if (w->layout()) {
                if (replaceWidgetInLayout(w->layout(), oldW, newW))
                    return true;
            }
        }
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════
//  RESIZE EVENT
//  Fallback uniquement si les pages n'ont pas de layout dans le .ui.
//  Dans ce cas on recalcule la géométrie des SpinBoxes à la main.
//  → La vraie solution reste d'appliquer un layout dans Qt Designer.
// ═══════════════════════════════════════════════════════════════════

void SignIn::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // Repositionne les SpinBoxes en mode fallback (page sans layout)
    if (m_qtyFallback && m_qtySpinBox && ui->quantityedit_F)
        m_qtySpinBox->setGeometry(ui->quantityedit_F->geometry());

    if (m_capFallback && m_capSpinBox && ui->capacity_F)
        m_capSpinBox->setGeometry(ui->capacity_F->geometry());
}

// ═══════════════════════════════════════════════════════════════════
//  TABLE STYLE
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupTableStyle() {
    QTableWidget *t = ui->tableeq_L;
    t->setColumnCount(7);
    t->setHorizontalHeaderLabels({"  NAME","  TYPE","  STATE","  QTY","  CAPACITY","",""});

    t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    t->horizontalHeader()->setSectionResizeMode(COL_EDIT, QHeaderView::Fixed);
    t->horizontalHeader()->setSectionResizeMode(COL_DEL,  QHeaderView::Fixed);
    t->setColumnWidth(COL_EDIT, 54);
    t->setColumnWidth(COL_DEL,  54);

    t->verticalHeader()->setDefaultSectionSize(46);
    t->verticalHeader()->setVisible(false);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setSelectionMode(QAbstractItemView::SingleSelection);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setAlternatingRowColors(true);
    t->setShowGrid(false);

    t->setStyleSheet(R"(
        QTableWidget {
            background-color: rgba(6,20,38,0.97);
            alternate-background-color: rgba(12,34,58,0.92);
            color: #EAF0FF;
            border: 1.5px solid rgba(79,195,247,0.20);
            border-radius: 12px;
            font-size: 13px;
            outline: none;
        }
        QTableWidget::item { padding: 6px 10px; border-bottom: 1px solid rgba(79,195,247,0.07); }
        QTableWidget::item:selected { background-color: rgba(33,150,243,0.22); color: #ffffff; }
        QTableWidget::item:hover    { background-color: rgba(33,150,243,0.10); }
        QHeaderView::section {
            background-color: rgba(8,28,52,0.98);
            color: #4fc3f7;
            font-weight: 700;
            font-size: 11px;
            letter-spacing: 1.1px;
            padding: 10px 6px;
            border: none;
            border-right: 1px solid rgba(79,195,247,0.12);
            border-bottom: 2px solid rgba(79,195,247,0.40);
            text-transform: uppercase;
        }
        QHeaderView::section:first { border-top-left-radius: 10px; }
        QHeaderView::section:last  { border-top-right-radius: 10px; border-right: none; }
        QScrollBar:vertical { background: transparent; width: 6px; border-radius: 3px; }
        QScrollBar::handle:vertical { background: rgba(79,195,247,0.45); border-radius: 3px; min-height: 28px; }
        QScrollBar::handle:vertical:hover { background: #4fc3f7; }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; border: none; }
    )");

    auto *sh = new QGraphicsDropShadowEffect(t);
    sh->setBlurRadius(22);
    sh->setColor(QColor(41, 182, 246, 45));
    sh->setOffset(0, 4);
    t->setGraphicsEffect(sh);
}

// ═══════════════════════════════════════════════════════════════════
//  SEARCH BAR
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupSearchBar() {
    auto *sb = ui->searchbar_L;
    sb->setText("");
    sb->setPlaceholderText("🔍  Search by name, type, state…");
    sb->setClearButtonEnabled(true);
    sb->setMinimumHeight(44);
    sb->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(8,28,50,0.95);
            border: 1.5px solid rgba(79,195,247,0.28);
            border-radius: 11px;
            padding: 9px 16px;
            font-size: 13px;
            color: #EAF0FF;
        }
        QLineEdit:focus { border: 1.5px solid #29b6f6; background-color: rgba(41,182,246,0.07); }
        QLineEdit:hover { border: 1.5px solid rgba(79,195,247,0.50); }
    )");
}

// ═══════════════════════════════════════════════════════════════════
//  SORT COMBO
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupSortCombo() {
    auto *cb = ui->sortEq_L;
    cb->clear();
    cb->addItems({"⇅  Sort by…","▲  Name A→Z","▼  Name Z→A","▲  Type A→Z",
                  "▼  Type Z→A","▲  Qty ↑","▼  Qty ↓","●  State"});
    cb->setMinimumHeight(44);
    cb->setStyleSheet(R"(
        QComboBox {
            background-color: rgba(8,28,50,0.95);
            border: 1.5px solid rgba(79,195,247,0.28);
            border-radius: 11px;
            padding: 9px 14px;
            font-size: 13px;
            color: #EAF0FF;
            min-width: 160px;
        }
        QComboBox:hover { border: 1.5px solid rgba(79,195,247,0.52); }
        QComboBox:focus { border: 1.5px solid #29b6f6; }
        QComboBox::drop-down { border: none; width: 28px; }
        QComboBox::down-arrow {
            border-left: 5px solid transparent; border-right: 5px solid transparent;
            border-top: 6px solid #4fc3f7; margin-right: 8px;
        }
        QComboBox QAbstractItemView {
            background-color: #071a2c;
            border: 1.5px solid #29b6f6;
            border-radius: 9px;
            color: #EAF0FF;
            selection-background-color: rgba(33,150,243,0.35);
            font-size: 13px;
            padding: 4px;
        }
    )");
}

// ═══════════════════════════════════════════════════════════════════
//  BUTTON STYLES
// ═══════════════════════════════════════════════════════════════════

QPushButton *SignIn::makeIconBtn(const QString &label, const QString &color,
                               const QString &border, QWidget *parent) {
    auto *btn = new QPushButton(label, parent);
    btn->setFixedSize(38, 34);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background: %1; color: white;
            border: 1px solid %2; border-radius: 8px;
            font-size: 14px; font-weight: 700; padding: 0px;
        }
        QPushButton:hover { background: %2; border: 1px solid white; }
        QPushButton:pressed { opacity: 0.7; }
    )").arg(color, border));
    return btn;
}

void SignIn::setupButtonStyles() {
    struct B { QPushButton *btn; QString c1, c2, bd; };
    QList<B> lb = {
                   {ui->chatbotbtn_L,    "#0d3a8a","#1565c0","#42a5f5"},
                   {ui->goToFormBtnE,    "#1b5e20","#2e7d32","#66bb6a"},
                   {ui->staticbtnE_L,    "#004d40","#00695c","#26a69a"},
                   {ui->exportpdfbtnE_L, "#263238","#37474f","#78909c"},
                   {ui->chatbotbtn_2_L,  "#38006b","#6a1b9a","#ce93d8"},
                   };
    for (auto &b : lb) {
        if (!b.btn) continue;
        b.btn->setStyleSheet(QString(R"(
            QPushButton {
                background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);
                color:white; border:1.5px solid %3; border-radius:11px;
                padding:9px 16px; font-size:13px; font-weight:700; letter-spacing:0.3px;
            }
            QPushButton:hover {
                background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:1 %1);
                border:1.5px solid white;
            }
            QPushButton:pressed { padding-top:11px; padding-bottom:7px; }
        )").arg(b.c1, b.c2, b.bd));
        auto *fx = new QGraphicsDropShadowEffect(b.btn);
        fx->setBlurRadius(10);
        fx->setColor(QColor(b.bd));
        fx->setOffset(0, 3);
        b.btn->setGraphicsEffect(fx);
    }

    if (ui->addEqbtn_F) {
        ui->addEqbtn_F->setStyleSheet(R"(
            QPushButton {
                background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #1e88e5,stop:1 #1565c0);
                color:white; border:1.5px solid #64b5f6; border-radius:13px;
                padding:13px 22px; font-size:15px; font-weight:800; letter-spacing:0.5px;
            }
            QPushButton:hover {
                background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #42a5f5,stop:1 #1e88e5);
                border:1.5px solid #90caf9;
            }
            QPushButton:pressed { background:#0d47a1; padding-top:15px; }
        )");
        auto *fx = new QGraphicsDropShadowEffect(ui->addEqbtn_F);
        fx->setBlurRadius(22);
        fx->setColor(QColor("#1e88e5"));
        fx->setOffset(0, 5);
        ui->addEqbtn_F->setGraphicsEffect(fx);
    }
    if (ui->goToListBtnE) {
        ui->goToListBtnE->setStyleSheet(R"(
            QPushButton {
                background: rgba(33,150,243,0.20); color:#90caf9;
                border:1.5px solid rgba(100,181,246,0.50); border-radius:11px;
                padding:11px 20px; font-size:13px; font-weight:700;
            }
            QPushButton:hover { background:rgba(33,150,243,0.32); color:white; border:1.5px solid #90caf9; }
        )");
    }
}

// ═══════════════════════════════════════════════════════════════════
//  SIDEBAR HIGHLIGHT
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupNavHighlight() {
    QString active = R"(QPushButton{
        background:rgba(33,150,243,0.20); color:#4fc3f7;
        border:none; border-left:4px solid #29b6f6; border-radius:8px;
        padding:10px 14px; font-weight:700; text-align:left;
    })";
    QString normal = R"(QPushButton{
        background:transparent; color:rgba(234,240,255,0.70);
        border:none; border-radius:8px; padding:10px 14px;
        font-weight:600; text-align:left;
    }
    QPushButton:hover{ background:rgba(33,150,243,0.10); color:#EAF0FF; })";

    for (auto *b : {ui->equipmentmanagementBTNe_F, ui->equipmentmanagementBTNe_L})
        if (b) b->setStyleSheet(active);
    for (auto *b : {ui->staffmanagementBTNe_F,    ui->clientsmanagementBTNe_F,
                    ui->stockmanagementBTNe_F,     ui->fishingzonemanagementBTNe_F,
                    ui->staffmanagementBTNe_L,     ui->clientsmanagementBTNe_L,
                    ui->stockmanagementBTNe_L,     ui->fishingzonemanagementBTNe_L})
        if (b) b->setStyleSheet(normal);
}

// ═══════════════════════════════════════════════════════════════════
//  LOAD DATA
// ═══════════════════════════════════════════════════════════════════

void SignIn::loadEquipmentList() {
    m_allEq.clear();
    auto rows = equipment::getAll();
    for (auto &r : rows) {
        EqRow row;
        row.name  = r[0]; row.type  = r[1]; row.state = r[2];
        row.qty   = r[3].toInt(); row.cap = r[4].toInt();
        m_allEq.append(row);
    }
    filterAndSortTable();
}

// ═══════════════════════════════════════════════════════════════════
//  FILTER + SORT → TABLE
// ═══════════════════════════════════════════════════════════════════

void SignIn::filterAndSortTable() {
    QString f  = ui->searchbar_L->text().trimmed().toLower();
    int     si = ui->sortEq_L->currentIndex();

    QList<EqRow> rows;
    for (const auto &r : m_allEq) {
        if (f.isEmpty() || r.name.toLower().contains(f) ||
            r.type.toLower().contains(f) || r.state.toLower().contains(f) ||
            QString::number(r.qty).contains(f) || QString::number(r.cap).contains(f))
            rows.append(r);
    }

    using R = EqRow;
    switch (si) {
    case 1: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.name.toLower()<b.name.toLower();}); break;
    case 2: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.name.toLower()>b.name.toLower();}); break;
    case 3: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.type.toLower()<b.type.toLower();}); break;
    case 4: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.type.toLower()>b.type.toLower();}); break;
    case 5: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.qty<b.qty;}); break;
    case 6: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.qty>b.qty;}); break;
    case 7: std::sort(rows.begin(),rows.end(),[](const R&a,const R&b){return a.state.toLower()<b.state.toLower();}); break;
    default: break;
    }

    QTableWidget *t = ui->tableeq_L;
    t->setRowCount(0);

    if (rows.isEmpty() && !f.isEmpty()) {
        t->insertRow(0);
        auto *it = new QTableWidgetItem("⚠  No results for \"" + ui->searchbar_L->text() + "\"");
        it->setTextAlignment(Qt::AlignCenter);
        it->setForeground(QColor("#ffa726"));
        t->setItem(0, 0, it);
        t->setSpan(0, 0, 1, 7);
        return;
    }

    for (int i = 0; i < rows.size(); ++i) {
        t->insertRow(i);
        auto cell = [&](int col, const QString &val) {
            auto *it = new QTableWidgetItem(val);
            it->setTextAlignment(Qt::AlignCenter);
            if (col == COL_STATE) {
                QString s = val.toLower();
                if      (s.contains("bon")||s.contains("good")||s.contains("ok"))
                    it->setForeground(QColor("#66bb6a"));
                else if (s.contains("repair")||s.contains("maint")||s.contains("entret"))
                    it->setForeground(QColor("#ffa726"));
                else if (s.contains("broken")||s.contains("hors")||s.contains("cass"))
                    it->setForeground(QColor("#ef5350"));
                else
                    it->setForeground(QColor("#EAF0FF"));
            } else {
                it->setForeground(QColor("#EAF0FF"));
            }
            t->setItem(i, col, it);
        };
        cell(COL_NAME,  rows[i].name);
        cell(COL_TYPE,  rows[i].type);
        cell(COL_STATE, rows[i].state);
        cell(COL_QTY,   QString::number(rows[i].qty));
        cell(COL_CAP,   QString::number(rows[i].cap));
        addRowButtons(i);
    }
}

void SignIn::addRowButtons(int row) {
    QTableWidget *t = ui->tableeq_L;

    auto *editBtn = makeIconBtn("✏", "rgba(230,168,23,0.25)", "#e6a817", t);
    connect(editBtn, &QPushButton::clicked, this, [this, row]() { editRowInline(row); });
    auto *ec = new QWidget; auto *el = new QHBoxLayout(ec);
    el->setContentsMargins(4,2,4,2); el->addWidget(editBtn);
    t->setCellWidget(row, COL_EDIT, ec);

    auto *delBtn = makeIconBtn("🗑", "rgba(198,40,40,0.25)", "#c62828", t);
    connect(delBtn, &QPushButton::clicked, this, [this, row]() { deleteRowInline(row); });
    auto *dc = new QWidget; auto *dl = new QHBoxLayout(dc);
    dl->setContentsMargins(4,2,4,2); dl->addWidget(delBtn);
    t->setCellWidget(row, COL_DEL, dc);
}

// ═══════════════════════════════════════════════════════════════════
//  ADD EQUIPMENT
// ═══════════════════════════════════════════════════════════════════

void SignIn::on_addEqbtn_F_clicked() {
    QString name  = ui->Eqnameedit_F    ? ui->Eqnameedit_F->text().trimmed()    : "";
    QString type  = ui->Eqaddressedit_F ? ui->Eqaddressedit_F->text().trimmed() : "";
    QString state = ui->stateedit_F     ? ui->stateedit_F->text().trimmed()     : "Good";
    int qty = m_qtySpinBox ? m_qtySpinBox->value() : 0;
    int cap = m_capSpinBox ? m_capSpinBox->value() : 0;

    auto flash = [](QLineEdit *le, bool err) {
        if (!le) return;
        le->setStyleSheet(err
                              ? "QLineEdit{border:1.5px solid #ef5350;border-radius:10px;"
                                "background:rgba(239,83,80,0.09);padding:7px 14px;color:#EAF0FF;font-size:13px;min-height:38px;}"
                              : "QLineEdit{border:1.5px solid #29b6f6;border-radius:10px;"
                                "background:rgba(41,182,246,0.07);padding:7px 14px;color:#EAF0FF;font-size:13px;min-height:38px;}");
    };

    bool err = false;
    if (name.isEmpty()) { flash(ui->Eqnameedit_F, true);    err = true; } else flash(ui->Eqnameedit_F, false);
    if (type.isEmpty()) { flash(ui->Eqaddressedit_F, true); err = true; } else flash(ui->Eqaddressedit_F, false);

    if (err) {
        QMessageBox::warning(this, "⚠  Missing Fields",
                             "Please fill in:\n\n  • Equipment Name\n  • Equipment Type");
        return;
    }

    equipment e(name, type, state.isEmpty() ? "Good" : state, qty, cap);

    if (e.ajouter()) {
        if (ui->addEqbtn_F) {
            ui->addEqbtn_F->setStyleSheet(
                "QPushButton{background:#2e7d32;color:white;border:1.5px solid #66bb6a;"
                "border-radius:13px;padding:13px 22px;font-size:15px;font-weight:800;}");
            QTimer::singleShot(900, this, [this]() { setupButtonStyles(); });
        }
        QMessageBox::information(this, "✅  Added", "\"" + name + "\" registered successfully!");

        if (ui->Eqnameedit_F)    ui->Eqnameedit_F->clear();
        if (ui->Eqaddressedit_F) ui->Eqaddressedit_F->clear();
        if (ui->stateedit_F)     ui->stateedit_F->clear();
        if (m_qtySpinBox)        m_qtySpinBox->setValue(0);
        if (m_capSpinBox)        m_capSpinBox->setValue(0);

        loadEquipmentList();
    } else {
        QMessageBox::critical(this, "❌  Database Error", "Insert failed.");
    }
}

// ═══════════════════════════════════════════════════════════════════
//  EDIT ROW — QDialog inline
// ═══════════════════════════════════════════════════════════════════

void SignIn::editRowInline(int row) {
    QTableWidget *t = ui->tableeq_L;
    if (row < 0 || row >= t->rowCount() || t->columnSpan(row, 0) > 1) return;

    auto txt = [&](int col) -> QString {
        auto *it = t->item(row, col); return it ? it->text() : "";
    };
    QString oldName  = txt(COL_NAME);
    QString oldType  = txt(COL_TYPE);
    QString oldState = txt(COL_STATE);
    int oldQty = txt(COL_QTY).toInt();
    int oldCap = txt(COL_CAP).toInt();

    QDialog dlg(this);
    dlg.setWindowTitle("✏  Edit Equipment");
    dlg.setFixedSize(460, 430);
    dlg.setStyleSheet("QDialog{background:#071a2c;}");

    auto *vl = new QVBoxLayout(&dlg);
    vl->setContentsMargins(28,22,28,22); vl->setSpacing(6);

    auto *hdr = new QLabel("✏  " + oldName);
    hdr->setStyleSheet("color:#4fc3f7;font-size:16px;font-weight:900;background:transparent;"
                       "border-bottom:2px solid rgba(79,195,247,0.25);padding-bottom:6px;margin-bottom:4px;");
    vl->addWidget(hdr);

    auto *grid = new QWidget; auto *gl = new QGridLayout(grid);
    gl->setColumnStretch(0,0); gl->setColumnStretch(1,1);
    gl->setHorizontalSpacing(14); gl->setVerticalSpacing(10);

    auto addRow = [&](int r, const QString &lbl, QWidget *w) {
        auto *lb = new QLabel(lbl);
        lb->setStyleSheet(kLabel);
        lb->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        gl->addWidget(lb, r, 0); gl->addWidget(w, r, 1);
    };

    auto *leName  = new QLineEdit(oldName);  leName->setStyleSheet(kField);  leName->setMinimumHeight(40);
    auto *leType  = new QLineEdit(oldType);  leType->setStyleSheet(kField);  leType->setMinimumHeight(40);
    auto *leState = new QLineEdit(oldState); leState->setStyleSheet(kField); leState->setMinimumHeight(40);
    auto *spQ = new QSpinBox; spQ->setRange(0,999999); spQ->setValue(oldQty);
    spQ->setStyleSheet(kField+"QSpinBox{color:#4fc3f7;font-weight:800;}"); spQ->setMinimumHeight(40);
    auto *spC = new QSpinBox; spC->setRange(0,9999999); spC->setValue(oldCap);
    spC->setStyleSheet(kField+"QSpinBox{color:#4fc3f7;font-weight:800;}"); spC->setMinimumHeight(40);

    addRow(0,"NAME  *",leName); addRow(1,"TYPE  *",leType); addRow(2,"STATE",leState);
    addRow(3,"QUANTITY",spQ);   addRow(4,"CAPACITY",spC);
    vl->addWidget(grid);

    vl->addSpacing(10);
    auto *btnW = new QWidget; auto *bHl = new QHBoxLayout(btnW);
    bHl->setContentsMargins(0,0,0,0); bHl->setSpacing(10);
    auto *cancel = new QPushButton("Cancel");
    auto *save   = new QPushButton("💾  Save Changes");
    cancel->setStyleSheet("QPushButton{background:rgba(55,71,79,0.6);color:#EAF0FF;"
                          "border:1.5px solid #607d8b;border-radius:10px;padding:10px 20px;font-weight:700;}"
                          "QPushButton:hover{background:#455a64;}");
    save->setStyleSheet("QPushButton{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
                        "stop:0 #1e88e5,stop:1 #1565c0);color:white;"
                        "border:1.5px solid #64b5f6;border-radius:10px;padding:10px 20px;font-weight:700;}"
                        "QPushButton:hover{background:#1e88e5;}");
    bHl->addWidget(cancel,1); bHl->addWidget(save,2);
    vl->addWidget(btnW);

    connect(cancel, &QPushButton::clicked, &dlg, &QDialog::reject);
    connect(save,   &QPushButton::clicked, &dlg, [&]() {
        if (leName->text().trimmed().isEmpty() || leType->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dlg, "Error", "Name and Type are required.");
            return;
        }
        equipment e(leName->text().trimmed(), leType->text().trimmed(),
                    leState->text().trimmed(), spQ->value(), spC->value());
        if (e.modifier(oldName)) dlg.accept();
        else QMessageBox::critical(&dlg, "❌ Error", "Update failed.");
    });

    if (dlg.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "✅  Updated", "Equipment updated successfully.");
        loadEquipmentList();
    }
}

// ═══════════════════════════════════════════════════════════════════
//  DELETE ROW
// ═══════════════════════════════════════════════════════════════════

void SignIn::deleteRowInline(int row) {
    QTableWidget *t = ui->tableeq_L;
    if (row < 0 || row >= t->rowCount() || t->columnSpan(row, 0) > 1) return;

    auto *it = t->item(row, COL_NAME);
    if (!it) return;
    QString name = it->text();

    QMessageBox dlg(this);
    dlg.setWindowTitle("Confirm Delete");
    dlg.setText("Permanently delete:\n\n  🗑  " + name + "  ?");
    dlg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlg.setDefaultButton(QMessageBox::No);
    dlg.setStyleSheet("QMessageBox{background:#0a1929;color:#EAF0FF;}"
                      "QPushButton{min-width:80px;padding:8px 16px;}");

    if (dlg.exec() == QMessageBox::No) return;

    equipment e;
    if (e.supprimer(name)) {
        QMessageBox::information(this, "✅  Deleted", "\"" + name + "\" removed.");
        loadEquipmentList();
    } else {
        QMessageBox::critical(this, "❌  Error", "Delete failed.");
    }
}

// ═══════════════════════════════════════════════════════════════════
//  EXPORT PDF
// ═══════════════════════════════════════════════════════════════════

void SignIn::on_exportpdfbtnE_L_clicked() {
    QString path = QFileDialog::getSaveFileName(
        this, "Export Equipment List", "equipment_list.pdf", "PDF (*.pdf)");
    if (path.isEmpty()) return;

    QPdfWriter w(path);
    w.setPageSize(QPageSize(QPageSize::A4));
    w.setPageOrientation(QPageLayout::Landscape);
    w.setResolution(96);
    QPainter p(&w);

    int rows = ui->tableeq_L->rowCount();
    const int DCOLS=5, colW=200, rowH=55, sx=80, sy=180;

    p.setPen(QColor("#1565c0"));
    p.setFont(QFont("Segoe UI",18,QFont::Bold));
    p.drawText(sx, 110, "BORT — Equipment List");
    p.setFont(QFont("Segoe UI",9));
    p.setPen(QColor("#666"));
    p.drawText(sx, 150, "Exported: " + QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm"));

    p.fillRect(sx, sy, colW*DCOLS, rowH, QColor("#1565c0"));
    p.setPen(Qt::white);
    p.setFont(QFont("Segoe UI",9,QFont::Bold));
    QStringList hdr = {"NAME","TYPE","STATE","QUANTITY","CAPACITY"};
    for (int c=0; c<DCOLS; ++c)
        p.drawText(sx+c*colW+10, sy+35, hdr[c]);

    p.setFont(QFont("Segoe UI",9));
    for (int r=0; r<rows; ++r) {
        p.fillRect(sx, sy+(r+1)*rowH, colW*DCOLS, rowH,
                   (r%2==0) ? QColor("#edf2f7") : QColor("#fff"));
        p.setPen(QColor("#1a202c"));
        for (int c=0; c<DCOLS; ++c) {
            auto *it = ui->tableeq_L->item(r, c);
            if (it) p.drawText(sx+c*colW+10, sy+(r+1)*rowH+35, it->text());
        }
    }
    p.end();
    QMessageBox::information(this, "✅  PDF Exported", "Saved to:\n" + path);
}

// ═══════════════════════════════════════════════════════════════════
//  CHATBOT (slot legacy — géré par lambda dans constructor)
// ═══════════════════════════════════════════════════════════════════

void SignIn::on_chatbotbtn_L_clicked() {}
// ═══════════════════════════════════════════════════════════════════
//  FORM WIDGET INJECTION
//  FIX : replaceWidgetInLayout() au lieu de setGeometry() —
//        les SpinBoxes sont maintenant DANS le layout et suivent
//        le redimensionnement de la fenêtre.
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupFormWidgets() {
    for (auto *le : {ui->Eqnameedit_F, ui->Eqaddressedit_F, ui->stateedit_F}) {
        if (!le) continue;
        le->setStyleSheet(kField);
        le->setMinimumHeight(44);
    }
    if (ui->Eqnameedit_F)    ui->Eqnameedit_F->setPlaceholderText("e.g.  Caterpillar D9");
    if (ui->Eqaddressedit_F) ui->Eqaddressedit_F->setPlaceholderText("e.g.  Hydraulic / Crane");
    if (ui->stateedit_F)     ui->stateedit_F->setPlaceholderText("Good  /  Maintenance  /  Broken");

    for (auto *lb : {ui->Eqnamelabel_F, ui->Eqaddresslabel_F, ui->statelabel_F,
                     ui->quantitylabel_F, ui->capacitylab_F}) {
        if (!lb) continue;
        lb->setStyleSheet(kLabel);
        lb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }

    if (ui->labeladdeq_F) {
        ui->labeladdeq_F->setText("⚓  Register New Equipment");
        ui->labeladdeq_F->setAlignment(Qt::AlignCenter);
        ui->labeladdeq_F->setStyleSheet(
            "QLabel{"
            "  color:#4fc3f7; font-size:20px; font-weight:900;"
            "  letter-spacing:1px; background:transparent;"
            "  border-bottom:2px solid rgba(79,195,247,0.28);"
            "  padding-bottom:6px;"
            "}");
    }

    // ── Remplace quantityedit_F par un QSpinBox ──────────────────────────────
    // FIX : replaceWidgetInLayout() insère le SpinBox dans le layout existant
    //       pour qu'il se redimensionne avec la fenêtre.
    if (ui->quantityedit_F) {
        m_qtySpinBox = new QSpinBox(ui->quantityedit_F->parentWidget());
        m_qtySpinBox->setRange(0, 999999);
        m_qtySpinBox->setValue(0);
        m_qtySpinBox->setAlignment(Qt::AlignCenter);
        m_qtySpinBox->setMinimumHeight(44);
        m_qtySpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_qtySpinBox->setStyleSheet(kField + "QSpinBox{color:#4fc3f7;font-size:16px;font-weight:800;}");

        // Tente l'insertion dans le layout parent (remontée récursive)
        QWidget *formPage = ui->pageEquipmentForm;
        bool replaced = false;
        if (formPage && formPage->layout())
            replaced = replaceWidgetInLayout(formPage->layout(), ui->quantityedit_F, m_qtySpinBox);

        if (!replaced) {
            // Fallback : si la page n'a pas encore de layout (sera corrigé dans .ui),
            // on recopie la géométrie comme avant mais on connecte resizeEvent.
            m_qtySpinBox->setGeometry(ui->quantityedit_F->geometry());
            ui->quantityedit_F->hide();
            m_qtySpinBox->show();
            m_qtyFallback = true;   // flag pour resizeEvent
        }
    }

    // ── Remplace capacity_F par un QSpinBox ──────────────────────────────────
    if (ui->capacity_F) {
        m_capSpinBox = new QSpinBox(ui->capacity_F->parentWidget());
        m_capSpinBox->setRange(0, 9999999);
        m_capSpinBox->setValue(0);
        m_capSpinBox->setAlignment(Qt::AlignCenter);
        m_capSpinBox->setMinimumHeight(44);
        m_capSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_capSpinBox->setStyleSheet(kField + "QSpinBox{color:#4fc3f7;font-size:16px;font-weight:800;}");

        QWidget *formPage = ui->pageEquipmentForm;
        bool replaced = false;
        if (formPage && formPage->layout())
            replaced = replaceWidgetInLayout(formPage->layout(), ui->capacity_F, m_capSpinBox);

        if (!replaced) {
            m_capSpinBox->setGeometry(ui->capacity_F->geometry());
            ui->capacity_F->hide();
            m_capSpinBox->show();
            m_capFallback = true;   // flag pour resizeEvent
        }
    }
}







void SignIn::on_logOutBTNe_L_clicked()
{
    performLogoutFlow();
}




void SignIn::on_clientsmanagementBTNe_L_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_stockmanagementBTNe_L_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_equipmentmanagementBTNe_L_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentList);
}


void SignIn::on_fishingzonemanagementBTNe_L_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_staffmanagementBTNe_L_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}



void SignIn::on_userprofiledetails_D_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}



void SignIn::on_staffmanagementBTNe_F_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_clientsmanagementBTNe_F_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}



void SignIn::on_stockmanagementBTNe_F_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
}


void SignIn::on_fishingzonemanagementBTNe_F_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_userprofiledetails_D_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_logOutBTNe_F_clicked()
{
    performLogoutFlow();
}

//arduino dhia


void SignIn::updateWaterLevel(int distance)
{
    // Example water level calculation based on distance
    double waterLevel = 0.0;  // Use double for precision

    // Maximum water level at distance = 15 cm
    double maxWaterLevel = 500.0;

    // Calculate the water level based on distance (scaled proportionally)
    if (distance <= 8) {
        waterLevel = maxWaterLevel;  // Maximum water level at distance 15 cm
    } else {
        // For distances greater than 15, calculate water level proportionally
        waterLevel = maxWaterLevel * (8.0 / distance);  // As distance increases, water level decreases
    }

    // Update the UI with the calculated water level
    QString waterLevelText = "Water Level: " + QString::number(waterLevel, 'f', 2);  // Show two decimal places
    ui->waterLevelLabel->setText(waterLevelText);  // Update the UI
    updateDatabaseWaterLevel(waterLevel);


    int status = (waterLevel >= 500) ? 1 : 0;

    A.sendBuzzerCommand(status);
}
void SignIn::updateDatabaseWaterLevel(int waterLevel)
{
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection is not open!";
        return;
    }

    QSqlQuery query;

    int status = 0;

    // If water level reaches max → activate status
    if (waterLevel >= 500) {
        status = 1;
    }

    query.prepare("UPDATE ZONEPECHES SET water_level = :waterLevel, status = :status");

    query.bindValue(":waterLevel", waterLevel);
    query.bindValue(":status", status);

    qDebug() << "Updating water level to:" << waterLevel;
    qDebug() << "Updating status to:" << status;

    if (!query.exec()) {
        qDebug() << "Failed to update water level and status!";
    }

}
