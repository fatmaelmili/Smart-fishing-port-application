#include "editclientdialog.h"
#include "clients.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QSqlQuery>

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
    paymentInput = new QComboBox(this);

    paymentInput->addItems({"Cash", "Debit card"});

    loadItems();

    connect(articleInput, &QComboBox::currentTextChanged, this, [=](const QString &text){
        if(text.startsWith("-----"))
            return;

        int max = getMaxQuantity(text);
        quantityInput->setMaximum(max);
    });

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

    layout->addWidget(new QLabel("Payment"));
    layout->addWidget(paymentInput);

    QHBoxLayout *btnLayout = new QHBoxLayout();

    saveBtn = new QPushButton("Save", this);
    cancelBtn = new QPushButton("Cancel", this);

    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);

    layout->addLayout(btnLayout);

    connect(saveBtn, &QPushButton::clicked, this, &EditClientDialog::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &EditClientDialog::onCancelClicked);

    dateInput->setMaximumDate(QDate::currentDate());
}
void EditClientDialog::setClientData(QString name, QString date, QString phone,
                                     QString article, int qte, QString modepay, int id)
{
    clientId = id;

    nameInput->setText(name);
    dateInput->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    phoneInput->setText(phone);
    articleInput->setCurrentText(article);
    quantityInput->setValue(qte);
    paymentInput->setCurrentText(modepay);
}

void EditClientDialog::onSaveClicked()
{
    if(clientId == -1)
        return;

    QString name = nameInput->text().trimmed();
    QString phone = phoneInput->text().trimmed();
    QString article = articleInput->currentText();
    QString payment = paymentInput->currentText();
    int quantity = quantityInput->value();
    QDate birthDate = dateInput->date();
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

    if(article.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Select an item");
        return;
    }

    if(payment.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Select a payment method");
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

    if(QMessageBox::question(this, "Confirm",
                              "Save changes?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;

    Client C(
        name,
        birthDate.toString("yyyy-MM-dd"),
        0,
        payment,
        "Paid",
        phone,
        article,
        quantity
        );

    if(C.modifierClient(clientId))
    {
        QMessageBox::information(this, "Success", "Client updated");
        accept();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Update failed");
    }
}

void EditClientDialog::onCancelClicked()
{
    reject();
}
// showing l7out w the other stuff
void EditClientDialog::loadItems()
{
    articleInput->clear();

    QSqlQuery q;

    articleInput->addItem("----- STOCKS -----");

    if(q.exec("SELECT TYPEPOISSON FROM STOCKS"))
    {
        while(q.next())
        {
            articleInput->addItem(q.value(0).toString());
        }
    }

    articleInput->addItem("----- EQUIPEMENTS -----");

    q.finish();

    if(q.exec("SELECT NOMEQ FROM EQUIPEMENTS"))
    {
        while(q.next())
        {
            articleInput->addItem(q.value(0).toString());
        }
    }
}
// puting el max mta3 the goods

int EditClientDialog::getMaxQuantity(QString item)
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
