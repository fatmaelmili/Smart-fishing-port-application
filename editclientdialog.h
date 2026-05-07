#ifndef EDITCLIENTDIALOG_H
#define EDITCLIENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

class EditClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditClientDialog(QWidget *parent = nullptr);

    void setClientData(QString name,
                       QString date,
                       QString phone,
                       QString article,
                       int qte,
                       QString modepay,
                       double price,
                       int id);

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    int clientId;

    QLineEdit *nameInput;

    QDateEdit *dateInput;

    QLineEdit *phoneInput;

    QComboBox *articleInput;

    QSpinBox *quantityInput;

    // 💰 NEW PRICE INPUT
    QLineEdit *priceInput;

    QComboBox *paymentInput;

    QPushButton *saveBtn;

    QPushButton *cancelBtn;

    void loadItems();

    int getMaxQuantity(QString item);
};

#endif // EDITCLIENTDIALOG_H
