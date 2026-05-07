#include "editclientdialog.h"
#include "client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QSqlQuery>
// ==================contructor goes wooo(i choose the wee and the wooo s 7asb el mood)==================
EditClientDialog::EditClientDialog(QWidget *parent)
    : QDialog(parent), clientId(-1)
{
    setWindowTitle("Edit Client");
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout(this);

    nameInput = new QLineEdit(this);

    dateInput = new QDateEdit(this);

    phoneInput = new QLineEdit(this);

    articleInput = new QComboBox(this);

    quantityInput = new QSpinBox(this);

    priceInput = new QLineEdit(this);

    paymentInput = new QComboBox(this);

    paymentInput->addItems(
        {
            "Cash",
            "Debit card"
        });

    loadItems();

    connect(articleInput,
            &QComboBox::currentTextChanged,
            this,
            [=](const QString &text)
            {
                if(text.startsWith("-----"))
                    return;

                int max =
                    getMaxQuantity(text);

                quantityInput->setMaximum(max);
            });

    // ================= UI =================

    layout->addWidget(new QLabel("Name"));
    layout->addWidget(nameInput);

    layout->addWidget(new QLabel("Date"));
    layout->addWidget(dateInput);

    layout->addWidget(new QLabel("Phone"));
    layout->addWidget(phoneInput);

    layout->addWidget(new QLabel("Article"));
    layout->addWidget(articleInput);

    layout->addWidget(new QLabel("Quantity"));
    layout->addWidget(quantityInput);

    // 💰 PRICE
    layout->addWidget(new QLabel("Price"));
    layout->addWidget(priceInput);

    layout->addWidget(new QLabel("Payment"));
    layout->addWidget(paymentInput);

    // ================= BUTTONS =================

    QHBoxLayout *btnLayout =
        new QHBoxLayout();

    saveBtn =
        new QPushButton("Save", this);

    cancelBtn =
        new QPushButton("Cancel", this);

    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);

    layout->addLayout(btnLayout);

    // ================= CONNECTIONS =================

    connect(saveBtn,
            &QPushButton::clicked,
            this,
            &EditClientDialog::onSaveClicked);

    connect(cancelBtn,
            &QPushButton::clicked,
            this,
            &EditClientDialog::onCancelClicked);

    // 📅 max date
    dateInput->setMaximumDate(
        QDate::currentDate()
        );
}

void EditClientDialog::loadItems()
{
    articleInput->clear();

    QSqlQuery q;

    // 🐟 STOCKS
    articleInput->addItem("----- STOCKS -----");

    if(q.exec("SELECT TYPEPOISSON FROM STOCKS"))
    {
        while(q.next())
        {
            articleInput->addItem(
                q.value(0).toString()
                );
        }
    }

    // ⚙️ EQUIPMENTS
    articleInput->addItem("----- EQUIPEMENTS -----");

    q.finish();

    if(q.exec("SELECT NOMEQ FROM EQUIPEMENTS"))
    {
        while(q.next())
        {
            articleInput->addItem(
                q.value(0).toString()
                );
        }
    }
}

int EditClientDialog::getMaxQuantity(QString item)
{
    QSqlQuery q;

    // 🐟 STOCKS
    q.prepare(
        "SELECT QTE "
        "FROM STOCKS "
        "WHERE TYPEPOISSON = :item"
        );

    q.bindValue(":item", item);

    if(q.exec() && q.next())
        return q.value(0).toInt();

    // ⚙️ EQUIPMENTS
    q.prepare(
        "SELECT QTE "
        "FROM EQUIPEMENTS "
        "WHERE NOMEQ = :item"
        );

    q.bindValue(":item", item);

    if(q.exec() && q.next())
        return q.value(0).toInt();

    return 0;
}

// ==================when the data is set==================
void EditClientDialog::setClientData(QString name,
                                     QString date,
                                     QString phone,
                                     QString article,
                                     int qte,
                                     QString modepay,
                                     double price,
                                     int id)
{
    clientId = id;

    nameInput->setText(name);

    dateInput->setDate(
        QDate::fromString(
            date,
            "yyyy-MM-dd"
            )
        );

    phoneInput->setText(phone);

    articleInput->setCurrentText(article);

    quantityInput->setValue(qte);

    paymentInput->setCurrentText(modepay);

    // 💰 PRICE
    priceInput->setText(
        QString::number(price)
        );
}
// ==================tamma tasjil al kerch bi naje7==================
void EditClientDialog::onSaveClicked()
{
    if(clientId == -1)
        return;

    QString name =
        nameInput->text().trimmed();

    QString phone =
        phoneInput->text().trimmed();

    QString article =
        articleInput->currentText();

    QString payment =
        paymentInput->currentText();

    int quantity =
        quantityInput->value();

    QDate birthDate =
        dateInput->date();

    QDate today =
        QDate::currentDate();

    // 💰 PRICE
    bool ok;

    double price =
        priceInput->text().toDouble(&ok);

    // ================= VALIDATION =================

    if(name.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Client name is required"
            );

        return;
    }

    QRegularExpression nameRegex(
        "^[A-Za-z ]+$"
        );

    if(!nameRegex.match(name).hasMatch())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Name must contain only letters"
            );

        return;
    }

    if(!phone.isEmpty())
    {
        QRegularExpression phoneRegex(
            "^\\d{8}$"
            );

        if(!phoneRegex.match(phone).hasMatch())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Phone must be exactly 8 digits"
                );

            return;
        }
    }

    if(article.isEmpty() ||
        article.startsWith("-----"))
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select an item"
            );

        return;
    }

    if(payment.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a payment method"
            );

        return;
    }

    if(quantity <= 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Quantity must be greater than 0"
            );

        return;
    }

    // 💰 PRICE VALIDATION
    if(!ok || price <= 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Enter a valid price"
            );

        return;
    }

    if(birthDate > today)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Date of birth cannot be in the future"
            );

        return;
    }

    int age =
        today.year() - birthDate.year();

    if(today.month() < birthDate.month() ||
        (today.month() == birthDate.month() &&
         today.day() < birthDate.day()))
    {
        age--;
    }

    if(age < 18)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Client must be at least 18 years old"
            );

        return;
    }

    // ================= CONFIRM =================

    if(QMessageBox::question(
            this,
            "Confirm",
            "Save changes?",
            QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::No)
    {
        return;
    }

    // ================= CLIENT =================

    Client C(
        name,

        birthDate.toString(
            "yyyy-MM-dd"
            ),

        price,

        payment,

        "Paid",

        phone,

        article,

        quantity
        );

    // ================= SAVE =================

    if(C.modifierClient(clientId))
    {
        QMessageBox::information(
            this,
            "Success",
            "Client updated"
            );

        accept();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "Update failed"
            );
    }
}

// ==================cancel culture==================
void EditClientDialog::onCancelClicked()
{
    reject();
}
