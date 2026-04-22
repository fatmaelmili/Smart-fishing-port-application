#include "bort.h"
#include "ui_clients.h"
#include "clients.h"
#include "editclientdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDate>

// ==================constructor goes weeeeee==================
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    loadClients("", "");
    loadItems();
    loadClientsFromDB();
}

// ==================destructor goes wooo==================
SignIn::~SignIn()
{
    delete ui;
}

// ==================wiiiii navigation goes brrr==================

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
    QString input = ui->resetlineEdit->text().trimmed();

    if (input.isEmpty()) {
        ui->resetlabel->setText("Please enter your email or username.");
        return;
    }

    ui->resetlabel->setText("Reset link sent.");
}

void SignIn::on_signinbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}

void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}

void SignIn::on_clientdashboardbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backtoclientbtn_clicked()
    {
        ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
    }


void SignIn::on_clientsmanagementBTN_W_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}

// ==================all mo7sen jaballah loads==================
void SignIn::loadClients(QString search, QString sort)
{
    Client C;
    QVector<QStringList> rows = C.afficherClients(search, sort);

    ui->clienttable->setRowCount(0);

    for(int i = 0; i < rows.size(); i++)
    {
        ui->clienttable->insertRow(i);

        for(int j = 0; j < rows[i].size(); j++)
        {
            ui->clienttable->setItem(i, j, new QTableWidgetItem(rows[i][j]));
        }
    }
    loadClientsFromDB();
}

// =================add a mos7sinon==================

void SignIn::on_clientaddbtn_clicked()
{
    QString name = ui->clientnameinput->text().trimmed();
    QString phone = ui->phoneinput->text().trimmed();
    QString payment = ui->choosepayment->currentText();
    QString item = ui->itemsinput->currentText();
    int quantity = ui->quantityinput->value();
    QDate birthDate = ui->clientdateinput->date();
    QDate today = QDate::currentDate();

    if(name.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Client name is required");
        return;
    }

    QRegularExpression nameRegex("^[A-Za-z ]+$");
    if(!nameRegex.match(name).hasMatch())
    {
        QMessageBox::warning(this, "Error", "Name must contain only letters");
        return;
    }

    if(!phone.isEmpty())
    {
        QRegularExpression phoneRegex("^\\d{8}$");
        if(!phoneRegex.match(phone).hasMatch())
        {
            QMessageBox::warning(this, "Error", "Phone must be exactly 8 digits");
            return;
        }
    }

    if(payment.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Select a payment method");
        return;
    }

    if(item.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Select an item");
        return;
    }

    if(quantity <= 0)
    {
        QMessageBox::warning(this, "Error", "Quantity must be greater than 0");
        return;
    }

    if(birthDate > today)
    {
        QMessageBox::warning(this, "Error", "Date of birth cannot be in the future");
        return;
    }

    int age = today.year() - birthDate.year();

    if(today.month() < birthDate.month() ||
        (today.month() == birthDate.month() && today.day() < birthDate.day()))
    {
        age--;
    }

    if(age < 18)
    {
        QMessageBox::warning(this, "Error", "Client must be at least 18 years old");
        return;
    }

    Client C(
        name,
        birthDate.toString("yyyy-MM-dd"),
        0,
        payment,
        "Paid",
        phone,
        item,
        quantity
        );

    if(C.ajouterClient())
    {
        QMessageBox::information(this, "Success", "Client added");
        loadClients("", "");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Add failed");
    }
    loadClientsFromDB();
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
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    if(!ui->clienttable->item(row,0))
        return;

    int id = ui->clienttable->item(row,0)->text().toInt();

    EditClientDialog dialog(this);

    dialog.setClientData(
        ui->clienttable->item(row,1)->text(),
        ui->clienttable->item(row,2)->text(),
        ui->clienttable->item(row,6)->text(),
        ui->clienttable->item(row,7)->text(),
        ui->clienttable->item(row,8)->text().toInt(),
        ui->clienttable->item(row,4)->text(),
        id
        );

    if(dialog.exec() == QDialog::Accepted)
    {
        loadClients("", "");
    }
    loadClientsFromDB();
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

    qDebug() << "✅ Loaded rows:" << row;
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
//==========================ai prediction kinda?=====================
void SignIn::on_aiclientbtn_clicked()
{
    int row = ui->clienttable->currentRow();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a client");
        return;
    }

    int clientId = ui->clienttable->item(row, 0)->text().toInt();

    // 🔥 Loading popup
    QMessageBox *loading = new QMessageBox(this);

    loading->setWindowTitle("AI System");
    loading->setText("<div style='color:white;'><h3>🤖 AI is analyzing...</h3><p>Please wait...</p></div>");
    loading->setTextFormat(Qt::RichText);

    loading->setStyleSheet(
        "QMessageBox { background-color:#0b1e2d; }"
        "QLabel { color:white; font-size:14px; }"
        );

    loading->setStandardButtons(QMessageBox::NoButton);
    loading->show();

    // ⏳ delay then run AI
    QTimer::singleShot(1200, this, [=]()
                       {
                           loading->close();
                           runAIPrediction(clientId);
                       });
}
//====================loading animation==========================
void SignIn::runAIPrediction(int clientId)
{
    Client c;

    QList<QPair<QString, double>> predictions = c.predictTop3(clientId);

    QString text = "<div style='color:white;'><h3>🤖 AI Recommendations</h3>";

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
                .arg(QString::number(predictions[i].second, 'f', 2));
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

    // 🎬 fade animation
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(msg);
    msg->setGraphicsEffect(effect);

    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(400);
    anim->setStartValue(0);
    anim->setEndValue(1);

    msg->show();
    anim->start();
}
