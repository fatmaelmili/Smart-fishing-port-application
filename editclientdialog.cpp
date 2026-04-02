#include "editclientdialog.h"

#include "client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDate>

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
    articleInput = new QLineEdit(this);
    quantityInput = new QSpinBox(this);
    paymentInput = new QComboBox(this);

    paymentInput->addItems({"Cash", "Debit card"});

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
}

// ==================when the data is set==================
void EditClientDialog::setClientData(QString name, QString date, QString phone,
                                     QString article, int qte, QString modepay, int id)
{
    clientId = id;

    nameInput->setText(name);
    dateInput->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    phoneInput->setText(phone);
    articleInput->setText(article);
    quantityInput->setValue(qte);
    paymentInput->setCurrentText(modepay);
}

// ==================tamma tasjil al kerch bi naje7==================
void EditClientDialog::onSaveClicked()
{
    if(clientId == -1)
        return;

    if(QMessageBox::question(this, "Confirm",
                              "Save changes?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;

    // ✅ FIX HERE: use Client instead of SignIn
    Client C(
        nameInput->text(),
        dateInput->date().toString("yyyy-MM-dd"),
        0,
        paymentInput->currentText(),
        "Paid",
        phoneInput->text(),
        articleInput->text(),
        quantityInput->value()
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

// ==================cancel culture==================
void EditClientDialog::onCancelClicked()
{
    reject();
}
