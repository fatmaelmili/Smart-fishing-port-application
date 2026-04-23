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
#include <QInputDialog>
#include <QVector>
#include <algorithm>
#include <QToolTip>
#include <QtCharts/QLineSeries>

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
    QSqlQuery query;

    query.exec(
        "SELECT TO_CHAR(DATECL,'MM'), SUM(MONTANT) "
        "FROM CLIENTS "
        "GROUP BY TO_CHAR(DATECL,'MM') "
        "ORDER BY TO_CHAR(DATECL,'MM')"
        );

    QBarSet *set = new QBarSet("Gains");
    QLineSeries *predictionLine = new QLineSeries();

    QStringList categories;
    QList<double> values;

    int index = 0;

    while(query.next())
    {
        double val = query.value(1).toDouble();
        *set << val;
        values.append(val);

        categories << query.value(0).toString();

        predictionLine->append(index, val); // connect real data
        index++;
    }

    // 🔮 PREDICTION (same logic as before)
    double predicted = 0;

    if(values.size() >= 4)
    {
        double avg = (values.last()
                      + values[values.size()-2]
                      + values[values.size()-3]
                      + values[values.size()-4]) / 4.0;

        double trend = (values.last() - values[values.size()-2]) * 0.5;

        predicted = avg + trend;
    }

    // ➕ ADD prediction point
    *set << predicted;
    categories << "Pred";

    predictionLine->append(index, predicted);

    // 🎨 STYLE
    set->setColor(QColor("#00c6ff"));

    QPen pen = predictionLine->pen();
    pen.setWidth(3);               // ✅ correct way
    pen.setColor(QColor("#00ffb3"));
    pen.setStyle(Qt::DashLine);

    predictionLine->setPen(pen);

    // 📊 SERIES
    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(set);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->addSeries(predictionLine);

    chart->setTitle("Monthly Gains + Prediction");
    chart->setBackgroundBrush(QColor("#0b1e2d"));
    chart->setTitleBrush(QBrush(Qt::white));

    // 📊 AXES
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(Qt::white);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);

    predictionLine->attachAxis(axisX);
    predictionLine->attachAxis(axisY);

    // ✨ ANIMATION
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 🧼 CLEAN
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
        ui->chart1->setLayout(new QVBoxLayout());

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

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

        // 🎨 Color styling
        slice->setBrush(colors[colorIndex % colors.size()]);
        colorIndex++;

        // ✨ Label styling
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelFont(QFont("Segoe UI", 10, QFont::Bold));

        // 💥 Hover animation
        connect(slice, &QPieSlice::hovered, this, [=](bool state)
                {
                    slice->setExploded(state);
                    slice->setExplodeDistanceFactor(0.1);
                });

        // 🖱️ CLICK → SHOW DETAILS
        connect(slice, &QPieSlice::clicked, this, [=]()
                {
                    int total = 0;

                    for(QPieSlice *s : series->slices())
                        total += s->value();

                    double percent = (slice->value() / total) * 100;

                    // 💥 Highlight selected slice
                    slice->setExploded(true);
                    slice->setExplodeDistanceFactor(0.15);

                    QString details =
                        "📊 Item Details\n\n"
                        "Item: " + slice->label() +
                        "\nSold: " + QString::number(slice->value()) +
                        "\nPercentage: " + QString::number(percent, 'f', 1) + "%";

                    showStyledPopup(details);
                });
    }

    // 📊 Chart setup
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Demand Distribution");

    // 🎨 Dark theme
    chart->setBackgroundBrush(QColor("#0b1e2d"));
    chart->setTitleBrush(QBrush(Qt::white));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(Qt::white);

    // ✨ Animations
    chart->setAnimationOptions(QChart::AllAnimations);

    // 🧼 Clean old layout
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
        QString fish = query.value(0).toString().toLower();
        int freq = query.value(1).toInt();

        double learned = Client::fishScores[fish];
        double score = freq + learned;

        if(score > bestScore)
        {
            bestScore = score;
            bestFish = fish;
        }
    }

    if(!bestFish.isEmpty())
    {
        Client::updateFishScore(bestFish, 0.5);
        Client::saveAI();

        QString result =
            "🐟 Smart Prediction\n\n"
            "Best Fish: " + bestFish +
            "\nScore: " + QString::number(bestScore, 'f', 2) +
            "\n(Based on demand)";

        showStyledPopup(result);
    }
    else
    {
        showStyledPopup("No data available.");
    }
}
void SignIn::on_vocalstuffbtn_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Quick Client Input");
    dialog.setLabelText(
        "Enter client information (flexible format):\n\n"
        "Examples:\n"
        "mary ann 16/07/1990 11223344 shrimp 2 cash\n"
        "shrmp 3 card\n"
        "john tuna 5"
        );

    dialog.setStyleSheet(
        "QDialog { background-color:#0b1e2d; }"
        "QLabel { color:white; font-size:13px; }"
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
        "QPushButton:hover { background:#00c6ff; }"
        );

    if(dialog.exec() == QDialog::Accepted)
    {
        QString text = dialog.textValue().trimmed();

        if(!text.isEmpty())
        {
            processQuickInput(text);
            showStyledPopup("✔ Information filled successfully.");
        }
    }
}
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
void SignIn::processQuickInput(QString text)
{
    text = text.toLower().trimmed();

    QStringList words = text.split(QRegularExpression("\\s+"));

    QString name;
    QString phone;
    QString item;
    QString payment;
    int quantity = -1;
    QDate date;

    QStringList nameParts;

    for(const QString &word : words)
    {
        // 📅 DATE
        QDate d = QDate::fromString(word, "dd/MM/yyyy");
        if(d.isValid())
        {
            date = d;
            continue;
        }

        // 🔢 PHONE (8 digits)
        if(word.length() == 8 && word.toInt() > 0)
        {
            phone = word;
            continue;
        }

        // 🔢 QUANTITY
        bool ok;
        int num = word.toInt(&ok);
        if(ok)
        {
            quantity = num;
            continue;
        }

        // 💳 PAYMENT (flexible)
        if(word.contains("cash")) { payment = "cash"; continue; }
        if(word.contains("card")) { payment = "card"; continue; }
        if(word.contains("transfer")) { payment = "transfer"; continue; }

        // 🐟 ITEM (fuzzy match)
        bool isItem = false;

        for(int j = 0; j < ui->itemsinput->count(); j++)
        {
            QString comboItem = ui->itemsinput->itemText(j).toLower();

            int dist = levenshteinDistance(word, comboItem);

            if(dist <= 2 || comboItem.contains(word))
            {
                item = comboItem;
                isItem = true;
                break;
            }
        }

        // 👤 NAME (only if not recognized)
        if(!isItem && !word.contains("/") && !word.toInt())
        {
            nameParts.append(word);
        }
    }

    // 🔹 MERGE + CAPITALIZE NAME
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

    // 🔹 APPLY VALUES

    if(!name.isEmpty())
        ui->clientnameinput->setText(name);

    if(date.isValid())
        ui->clientdateinput->setDate(date);

    if(!phone.isEmpty())
        ui->phoneinput->setText(phone);

    if(!item.isEmpty())
        ui->itemsinput->setCurrentText(item);

    if(quantity != -1)
        ui->quantityinput->setValue(quantity);

    if(!payment.isEmpty())
        ui->choosepayment->setCurrentText(payment);

    showStyledPopup("✔ Smart input processed.");
}
void SignIn::updateInsights()
{
    QString insight;

    if(ui->monthsgainslabel->text().contains("pred"))
        insight += "📊 Growth trend detected\n";

    insight += "🐟 Demand driven by frequent purchases\n";
    insight += "💡 Consider increasing stock for top items";

    showStyledPopup(insight);
}
