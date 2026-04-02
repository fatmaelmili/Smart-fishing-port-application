#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SignIn; }
QT_END_NAMESPACE

class SignIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void loadEquipmentList();
    void on_addEqbtn_F_clicked();
    void filterAndSortTable();
    void on_exportpdfbtnE_L_clicked();
    void on_chatbotbtn_L_clicked();
    void editRowInline(int row);
    void deleteRowInline(int row);

private:
    Ui::SignIn *ui;

    QSpinBox  *m_qtySpinBox  = nullptr;
    QSpinBox  *m_capSpinBox  = nullptr;

    struct EqRow { QString name, type, state; int qty = 0, cap = 0; };
    QList<EqRow> m_allEq;

    static constexpr int COL_NAME  = 0;
    static constexpr int COL_TYPE  = 1;
    static constexpr int COL_STATE = 2;
    static constexpr int COL_QTY   = 3;
    static constexpr int COL_CAP   = 4;
    static constexpr int COL_EDIT  = 5;
    static constexpr int COL_DEL   = 6;

    void setupFormWidgets();
    void setupTableStyle();
    void setupSearchBar();
    void setupSortCombo();
    void setupButtonStyles();
    void setupNavHighlight();
    void addRowButtons(int row);
    QPushButton* makeIconBtn(const QString &, const QString &, const QString &, QWidget *);
};

#endif
