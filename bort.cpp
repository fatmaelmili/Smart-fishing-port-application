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
    //added this
    qDebug() << "Constructor START";
    ui->setupUi(this);
    connect(ui->pdfitembtn, &QPushButton::clicked,
            this, &SignIn::on_pdfitembtn_clicked);
    loadClients("", "");
    loadItems();
    //added this(elli louta lkoll)
    loadClientsFromDB();
    setupBarChart();
    setupPieChart();
    updateDashboard();
    qDebug() << "Constructor END";
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
    ui->stackedWidget->setCurrentWidget(ui->clientdash);
}


void SignIn::on_backtoclientbtn_clicked()
    {
        ui->stackedWidget->setCurrentWidget(ui->pageClientManagement);
    }


void SignIn::on_clientsmanagementBTN_W_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageClientManagement);
}

// ==================all mo7sen jaballah loads==================
void SignIn::loadClients(QString search, QString sort)
{
    ui->clienttable->setRowCount(0); // clear table

    QSqlQuery query;

    QString orderBy = "";

    if(sort == "client's name ↑")
        orderBy = "ORDER BY TYPE ASC";
    else if(sort == "client's name ↓")
        orderBy = "ORDER BY TYPE DESC";

    else if(sort == "article ↑")
        orderBy = "ORDER BY ARTICLE ASC";
    else if(sort == "article ↓")
        orderBy = "ORDER BY ARTICLE DESC";

    else if(sort == "quantity ↑")
        orderBy = "ORDER BY QTE ASC";
    else if(sort == "quantity ↓")
        orderBy = "ORDER BY QTE DESC";
    QString queryStr =
        "SELECT IDCLIENTS, TYPE, DATECL, MONTANT, MODEPAY, ETAT, DESCRIPTION, ARTICLE, QTE "
        "FROM CLIENTS ";

    if(!search.isEmpty())
    {
        queryStr += "WHERE LOWER(TYPE) LIKE LOWER('%" + search + "%') ";
    }
    if(!orderBy.isEmpty())
        queryStr += orderBy;
    else
        queryStr += "ORDER BY IDCLIENTS DESC";

    // 🔹 Execute
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
            ui->clienttable->setItem(row, col,
                                     new QTableWidgetItem(query.value(col).toString()));
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

    loadingMsg = new QMessageBox(this);

    loadingMsg->setWindowTitle("AI System");
    loadingMsg->setText("<div style='color:white;'><h3>🤖 AI is analyzing...</h3><p>Please wait...</p></div>");
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
    // 🔥 Close loading popup
    if(loadingMsg)
    {
        loadingMsg->close();
        delete loadingMsg;
        loadingMsg = nullptr;
    }

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
                .arg(QString::number(predictions[i].second, 'f', 1)); // 🔥 FIXED %
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
        "SELECT SUM(MONTANT) "
        "FROM CLIENTS "
        "WHERE TO_CHAR(DATECL, 'MM-YYYY') = TO_CHAR(SYSDATE, 'MM-YYYY')"
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

    QSqlQuery query;
    query.exec("SELECT ARTICLE, SUM(QTE) FROM CLIENTS GROUP BY ARTICLE");

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Sales");

    QStringList categories;

    while(query.next())
    {
        QString article = query.value(0).toString();
        int quantity = query.value(1).toInt();

        *set << quantity;
        categories << article;
    }
    QLinearGradient gradient(0, 0, 0, 1);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setColorAt(0.0, QColor("#00c6ff"));
    gradient.setColorAt(1.0, QColor("#0072ff"));
    set->setBrush(gradient);

    series->append(set);
    connect(series, &QBarSeries::clicked, this, [=](int index, QBarSet *set)
            {
                QString item = categories[index];
                int value = set->at(index);

                QMessageBox::information(this, "Details",
                                         "Item: " + item + "\nQuantity: " + QString::number(value));
            });

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sales by Item");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setBackgroundBrush(QBrush(QColor("#0b1e2d")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->legend()->hide();

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(Qt::white);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chart1);
    layout->addWidget(chartView);
}


//==============================stats the round type=======================================
void SignIn::setupPieChart()
{
    if(ui->chart2->layout())
    {
        QLayout *layout = ui->chart1->layout();
        while(layout->count())
        {
            QWidget *w = layout->itemAt(0)->widget();
            layout->removeWidget(w);
            delete w;
        }
    }

    QSqlQuery query;
    query.exec("SELECT ARTICLE, SUM(QTE) FROM CLIENTS GROUP BY ARTICLE");

    QPieSeries *series = new QPieSeries();

    while(query.next())
    {
        QString article = query.value(0).toString();
        int quantity = query.value(1).toInt();

        series->append(article, quantity);
    }

    for(auto slice : series->slices())
    {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::white);

        connect(slice, &QPieSlice::clicked, this, [=]()
                {
                    QString name = slice->label();
                    double percent = slice->percentage() * 100;

                    QMessageBox::information(this, "Details",
                                             "Item: " + name +
                                                 "\nPercentage: " + QString::number(percent, 'f', 1) + "%");
                });

        // Highlight big slices
        if(slice->percentage() > 0.3)
            slice->setExploded(true);
        connect(slice, &QPieSlice::hovered, this, [=](bool state)
                {
                    slice->setExploded(state);
                });
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sales Distribution");
    chart->setBackgroundBrush(QBrush(QColor("#0b1e2d")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->legend()->setLabelColor(Qt::white);

    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chart2);
    layout->addWidget(chartView);
}


//=======================dashboard pdf file good kind version============================================
void SignIn::on_pdfitembtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save PDF", "dashboard.pdf", "*.pdf");

    if(fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);

    // 🔥 LANDSCAPE MODE
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    int width = pdf.width();
    int height = pdf.height();
    int margin = 60;

    // ===================== PAGE 1 =====================

    // 🎨 Background
    painter.fillRect(0, 0, width, height, QColor("#0b1e2d"));

    int y = margin;

    // 🏷️ Title
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 24, QFont::Bold));
    painter.drawText(QRect(0, y, width, 100),
                     Qt::AlignCenter,
                     "Client Dashboard Report");

    y += 200;

    // 📅 Date
    painter.setPen(QColor("#aaaaaa"));
    painter.setFont(QFont("Segoe UI", 11));
    painter.drawText(QRect(0, y, width, 40),
                     Qt::AlignCenter,
                     QDateTime::currentDateTime().toString("dd MMM yyyy - hh:mm"));

    y += 250;

    // 🔷 CARD WIDTHS
    int cardWidth = (width - 3 * margin) / 2;
    int cardHeight = 500;

    // 💰 GAINS CARD
    QRect gainsCard(margin, y, cardWidth, cardHeight);

    painter.setBrush(QColor("#132f4c"));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(gainsCard, 15, 15);

    // Title
    painter.setPen(QColor("#00c6ff"));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(gainsCard.adjusted(20, 15, -20, -60),
                     Qt::TextWordWrap,
                     "This Month's Gains");

    // Value
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 20, QFont::Bold));
    painter.drawText(gainsCard.adjusted(20, 45, -20, -10),
                     Qt::TextWordWrap,
                     ui->monthsgainslabel->text());

    // 🏆 MOST SOLD CARD
    QRect soldCard(2 * margin + cardWidth, y, cardWidth, cardHeight);

    painter.setBrush(QColor("#132f4c"));
    painter.drawRoundedRect(soldCard, 15, 15);

    // Title
    painter.setPen(QColor("#00c6ff"));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(soldCard.adjusted(20, 15, -20, -60),
                     Qt::TextWordWrap,
                     "Most Sold Item");

    // Value
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 18, QFont::Bold));
    painter.drawText(soldCard.adjusted(20, 45, -20, -10),
                     Qt::TextWordWrap,
                     ui->mostsolditemlabel->text());
    // 📝 Footer
    painter.setPen(QColor("#888888"));
    painter.setFont(QFont("Segoe UI", 9));
    painter.drawText(QRect(0, height - 50, width, 30),
                     Qt::AlignCenter,
                     "Generated by BORT System");

    // ===================== PAGE 2 =====================
    pdf.newPage();

    painter.fillRect(0, 0, width, height, QColor("#0b1e2d"));

    y = margin;

    // 🏷️ Title
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 20, QFont::Bold));
    painter.drawText(QRect(0, y, width, 100),
                     Qt::AlignCenter,
                     "Charts Overview");

    y += 60;

    // 📊 GET CHART IMAGES (HIGH RES)
    QPixmap chart1 = ui->chart1->grab();
    QPixmap chart2 = ui->chart2->grab();

    // 🔥 BIGGER AREA FOR CHARTS
    int chartWidth = (width - 3 * margin) / 2;
    int chartHeight = height - y - 60; // less bottom spacing → bigger charts

    // 🔹 SCALE (keep ratio but maximize size)
    QPixmap scaled1 = chart1.scaled(chartWidth, chartHeight,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    QPixmap scaled2 = chart2.scaled(chartWidth, chartHeight,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    // 🔹 POSITIONS
    int x1 = margin;
    int x2 = 2 * margin + chartWidth;

    // 🔥 CENTER VERTICALLY
    int yCentered1 = y + (chartHeight - scaled1.height()) / 2;
    int yCentered2 = y + (chartHeight - scaled2.height()) / 2;

    // 🔹 BACKGROUND CARDS (FIT TO IMAGE SIZE, NOT FULL AREA)
    QRect bg1(x1 - 10, yCentered1 - 10,
              scaled1.width() + 20, scaled1.height() + 20);

    QRect bg2(x2 - 10, yCentered2 - 10,
              scaled2.width() + 20, scaled2.height() + 20);

    painter.setBrush(QColor("#132f4c"));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bg1, 15, 15);
    painter.drawRoundedRect(bg2, 15, 15);

    // 🔹 DRAW CHARTS (centered inside cards)
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

    // 📝 Footer
    painter.setPen(QColor("#888888"));
    painter.setFont(QFont("Segoe UI", 9));
    painter.drawText(QRect(0, height - 40, width, 30),
                     Qt::AlignCenter,
                     "Charts generated dynamically from database");

    painter.end();
    QMessageBox::information(this, "Success",
                             "✨ Beautiful 2-page PDF exported!");
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
        "SELECT SUM(MONTANT) FROM CLIENTS"
        );

    double total = 0;

    if(query.next())
        total = query.value(0).toDouble();

    double learned = Client::fishScores["global_gain"];

    double prediction = total * 1.1 + learned;

    Client::updateFishScore("global_gain", total * 0.05);
    Client::saveAI();

    QString result =
        "📊 AI Financial Prediction\n\n"
        "Estimated Gains: " + QString::number(prediction, 'f', 2) + " DT\n"
                                                "Trend: " + (prediction > total ? "📈 Growing" : "📉 Declining");

    showStyledPopup(result);
}
//===============bel 7out 3lik yazzayn=======================
void SignIn::predictBestFish()
{
    QSqlQuery query;

    query.exec(
        "SELECT ARTICLE, SUM(QTE) as total "
        "FROM CLIENTS "
        "WHERE LOWER(ARTICLE) LIKE '%fish%' "
        "   OR LOWER(ARTICLE) LIKE '%tuna%' "
        "   OR LOWER(ARTICLE) LIKE '%sardine%' "
        "GROUP BY ARTICLE "
        "ORDER BY total DESC"
        );

    if(query.next())
    {
        QString fish = query.value(0).toString();
        int qty = query.value(1).toInt();

        // 🔥 AI LEARNING BOOST
        double score = qty + Client::fishScores[fish];

        Client::updateFishScore(fish, qty * 0.2);
        Client::saveAI();

        QString result =
            "🐟 AI Fish Prediction\n\n"
            "Best Fish: " + fish +
            "\nDemand: " + QString::number(qty) +
            "\nAI Score: " + QString::number(score, 'f', 1);

        showStyledPopup(result);
    }
    else
    {
        showStyledPopup("❌ No fish data available");
    }
}

