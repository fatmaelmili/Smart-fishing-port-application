/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignIn
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *pageSignIn;
    QLineEdit *UserNameEdit;
    QLineEdit *PasswordEdit;
    QLabel *UserNameLabel;
    QLabel *PasswordLabel;
    QPushButton *signinbtn;
    QPushButton *withfacebtn;
    QPushButton *btnForgetmdp;
    QCheckBox *remembercheck;
    QLabel *label_4;
    QWidget *pageForgetpass;
    QLabel *ForgotTitle;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *leftpanelForget;
    QLabel *label;
    QFrame *rightpannelforget;
    QLabel *resetlabel;
    QLineEdit *resetlineEdit;
    QPushButton *resetbtn;
    QPushButton *backsigninBTN;
    QWidget *pageStaffManagement;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QFrame *sidebarMenu;
    QGroupBox *groupBox;
    QPushButton *staffmanagementBTN;
    QPushButton *clientsmanagementBTN;
    QPushButton *stockmanagementBTN;
    QPushButton *fishingzonemanagementBTN;
    QPushButton *equipmentmanagementBTN;
    QLabel *logoheader;
    QPushButton *logOutBTN;
    QFrame *contenumain;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFrame *header;
    QLabel *titreHeader;
    QCommandLinkButton *userprofiledetails;
    QLabel *avatar;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QFrame *liststaff;
    QGroupBox *liststaffff;
    QComboBox *sortstaff;
    QLabel *stafflistlabel;
    QTableWidget *tablestaff;
    QPushButton *modifystaffbtn;
    QPushButton *deletestaffbtn;
    QPushButton *cvanalysebtn;
    QPushButton *staticbtn;
    QPushButton *exportpdfstaffbtn;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignIn)
    {
        if (SignIn->objectName().isEmpty())
            SignIn->setObjectName("SignIn");
        SignIn->resize(1017, 1080);
        SignIn->setStyleSheet(QString::fromUtf8("/* ===== RESET COMPLET ===== */\n"
"* {\n"
"    margin: 0;\n"
"    padding: 0;\n"
"    border: none;\n"
"    background-color: transparent;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"/* ===== FEN\303\212TRE PRINCIPALE ===== */\n"
"QMainWindow {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #0a1929, \n"
"        stop:0.5 #0c2b46,\n"
"        stop:1 #0a2338);\n"
"}\n"
"\n"
"/* ===== CONTENEUR CENTRAL ===== */\n"
"#centralwidget {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ===== STACKED WIDGET ===== */\n"
"QStackedWidget {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    min-width: 400px;\n"
"    min-height: 600px;\n"
"}\n"
"\n"
"/* ===== PAGE DE LOGIN (page_1) ===== */\n"
"#page_1 {\n"
"    background-color: rgba(16, 32, 48, 0.95);\n"
"    border-radius: 20px;\n"
"    border: 2px solid #1e3a5f;\n"
"    width: 380px;\n"
"    height: 580px;\n"
"    margin: 0;\n"
"    padding: 0;\n"
"}\n"
"\n"
"/*"
                        " ===== LOGO - PARFAITEMENT CENTR\303\211 ===== */\n"
"#logo {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"    qproperty-scaledContents: true;\n"
"    margin-top: 25px;\n"
"    margin-bottom: 10px;\n"
"    min-height: 70px;\n"
"    max-height: 70px;\n"
"    min-width: 380px;\n"
"}\n"
"\n"
"/* ===== TITRE PRINCIPAL ===== */\n"
"#title {\n"
"    color: #4fc3f7;\n"
"    font-size: 26px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', 'Arial Rounded MT Bold';\n"
"    qproperty-alignment: 'AlignCenter';\n"
"    margin-top: 0;\n"
"    margin-bottom: 25px;\n"
"    padding-bottom: 8px;\n"
"    border-bottom: 1px solid rgba(79, 195, 247, 0.3);\n"
"    text-shadow: 0 0 8px rgba(79, 195, 247, 0.4);\n"
"    min-width: 380px;\n"
"}\n"
"\n"
"/* ===== LABELS DES CHAMPS ===== */\n"
"#UserNameLabel, \n"
"QLabel[objectName*=\"password\"] {\n"
"    color: #90caf9;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    margin-left: 50px;\n"
"    margin-top: 5px;\n"
"    margin-bottom: 5px;\n"
"    text-align: "
                        "left;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"}\n"
"\n"
"/* ===== CHAMPS DE SAISIE (BIEN ALIGN\303\211S) ===== */\n"
"#UserNameEdit,\n"
"QLineEdit[objectName*=\"password\"] {\n"
"    background-color: rgba(30, 58, 95, 0.8);\n"
"    border: 2px solid #2d5278;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    font-size: 14px;\n"
"    color: #e3f2fd;\n"
"    min-height: 42px;\n"
"    max-height: 42px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 50px;\n"
"    margin-right: 50px;\n"
"    margin-bottom: 10px;\n"
"    selection-background-color: #0288d1;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #29b6f6;\n"
"    background-color: rgba(41, 182, 246, 0.1);\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 2px solid #0288d1;\n"
"}\n"
"\n"
"/* ===== CHECKBOX REMEMBER ME (CORRIG\303\211E) ===== */\n"
"#remembercheck {\n"
"    color: #bbdefb;\n"
"    font-size: 12px;\n"
"    spacing: 8px;\n"
"    margin-left: 50px;\n"
""
                        "    margin-top: 10px;\n"
"    margin-bottom: 5px;\n"
"    min-width: 280px;\n"
"}\n"
"\n"
"#remembercheck::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"    border-radius: 3px;\n"
"    border: 2px solid #64b5f6;\n"
"    background-color: rgba(30, 58, 95, 0.9);\n"
"}\n"
"\n"
"#remembercheck::indicator:checked {\n"
"    background-color: #0288d1;\n"
"    border-color: #4fc3f7;\n"
"    /* COCHE BLANCHE */\n"
"    image: url(data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPHBhdGggZD0iTTEwIDNMNC41IDguNUwyIDUiIHN0cm9rZT0id2hpdGUiIHN0cm9rZS13aWR0aD0iMiIgc3Ryb2tlLWxpbmVjYXA9InJvdW5kIiBzdHJva2UtbGluZWpvaW49InJvdW5kIi8+Cjwvc3ZnPgo=);\n"
"}\n"
"\n"
"#remembercheck::indicator:hover {\n"
"    border: 2px solid #4fc3f7;\n"
"}\n"
"\n"
"/* ===== BOUTON FORGOT PASSWORD ===== */\n"
"#btnForgotmdp {\n"
"    background-color: transparent;\n"
"    color: #29b6f6;\n"
"    border: none;\n"
"    font-size: 11px;\n"
""
                        "    text-decoration: none;\n"
"    padding: 0;\n"
"    margin-left: 50px;\n"
"    margin-top: 0;\n"
"    margin-bottom: 20px;\n"
"    text-align: left;\n"
"    min-width: 280px;\n"
"}\n"
"\n"
"#btnForgotmdp:hover {\n"
"    color: #4fc3f7;\n"
"    text-decoration: underline;\n"
"}\n"
"\n"
"/* ===== BOUTON SIGN IN (LARGEUR R\303\211DUITE) ===== */\n"
"#signinbtn {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0277bd,\n"
"        stop:0.5 #01579b,\n"
"        stop:1 #003f6b);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    min-height: 44px;\n"
"    max-height: 44px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 50px;\n"
"    margin-right: 50px;\n"
"    margin-bottom: 12px;\n"
"    letter-spacing: 0.5px;\n"
"    text-transform: uppercase;\n"
"}\n"
"\n"
"#signinbtn:hover {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"  "
                        "      stop:0 #0288d1,\n"
"        stop:0.5 #0277bd,\n"
"        stop:1 #01579b);\n"
"    border: 1px solid #4fc3f7;\n"
"}\n"
"\n"
"#signinbtn:pressed {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #01579b,\n"
"        stop:0.5 #013a63,\n"
"        stop:1 #002642);\n"
"    padding-top: 15px;\n"
"    padding-bottom: 13px;\n"
"}\n"
"\n"
"/* ===== BOUTON FACE ID (LARGEUR R\303\211DUITE) ===== */\n"
"#withfacebtn {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00897b,\n"
"        stop:0.5 #00695c,\n"
"        stop:1 #004d40);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"    max-height: 40px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 50px;\n"
"    margin-right: 50px;\n"
"    margin-bottom: 25px;\n"
"}\n"
"\n"
"#withfacebtn:hover {\n"
"    background-color: qlineargradient(x1:0,"
                        " y1:0, x2:0, y2:1,\n"
"        stop:0 #009688,\n"
"        stop:0.5 #00796b,\n"
"        stop:1 #005b4f);\n"
"    border: 1px solid #4db6ac;\n"
"}\n"
"\n"
"/* ===== CONTENEURS POUR ALIGNEMENT ===== */\n"
"/* Force l'alignement vertical */\n"
"QWidget {\n"
"    margin: 0;\n"
"    padding: 0;\n"
"}\n"
"\n"
"/* Espaceurs invisibles pour alignement */\n"
"QSpacerItem {\n"
"    min-height: 10px;\n"
"    max-height: 10px;\n"
"}\n"
"\n"
"/* ===== BARRES INUTILES (CACH\303\211ES) ===== */\n"
"QMenuBar, QStatusBar {\n"
"    background-color: transparent;\n"
"    color: transparent;\n"
"    border: none;\n"
"    height: 0;\n"
"    min-height: 0;\n"
"    max-height: 0;\n"
"}\n"
"\n"
"/* ===== \303\211TATS SP\303\211CIAUX ===== */\n"
"QLineEdit:invalid {\n"
"    border: 2px solid #ff5252;\n"
"    background-color: rgba(255, 82, 82, 0.1);\n"
"}\n"
"\n"
"QLineEdit:disabled,\n"
"QPushButton:disabled,\n"
"QCheckBox:disabled {\n"
"    opacity: 0.5;\n"
"}\n"
"\n"
"/* ===== TRANSITIONS ===== */\n"
"QLineEdit, QPushButton {\n"
" "
                        "   transition: border 0.2s ease, background-color 0.2s ease;\n"
"}\n"
"\n"
"/* ===== MESSAGES D'ERREUR ===== */\n"
"QLabel[objectName*=\"error\"] {\n"
"    color: #ff6b6b;\n"
"    font-size: 11px;\n"
"    font-style: italic;\n"
"    margin-left: 50px;\n"
"    margin-top: -8px;\n"
"    margin-bottom: 8px;\n"
"    min-width: 280px;\n"
"}"));
        centralwidget = new QWidget(SignIn);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1021, 741));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        pageSignIn = new QWidget();
        pageSignIn->setObjectName("pageSignIn");
        pageSignIn->setStyleSheet(QString::fromUtf8("/* ===== RESET ET STYLE GLOBAL ===== */\n"
"* {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QMainWindow {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #0a1929, \n"
"        stop:0.5 #0c2b46,\n"
"        stop:1 #0a2338);\n"
"}\n"
"\n"
"/* ===== CONTENEUR PRINCIPAL (StackedWidget) ===== */\n"
"QStackedWidget {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    padding: 0;\n"
"    margin: 0;\n"
"}\n"
"\n"
"/* Page de login (page_1) */\n"
"QWidget#page_1, QWidget[objectName=\"page_1\"], QWidget#centralwidget {\n"
"    background-color: rgba(16, 32, 48, 0.95);\n"
"    border-radius: 20px;\n"
"    border: 2px solid #1e3a5f;\n"
"    min-width: 380px;\n"
"    max-width: 380px;\n"
"    min-height: 520px;\n"
"    margin: auto;\n"
"    position: absolute;\n"
"    left: 50%;\n"
"    top: 50%;\n"
"    transform: translate(-50%, -50%);\n"
"}\n"
"\n"
"/* ===== LOGO - CENTRALIS\303\211 ===== */\n"
"QLabel#logo {\n"
"    margin-top: 10px"
                        ";\n"
"    margin-bottom: 20px;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"    qproperty-scaledContents: true;\n"
"    min-height: 80px;\n"
"    max-height: 80px;\n"
"}\n"
"\n"
"/* ===== TITRE ===== */\n"
"QLabel#title {\n"
"    color: #4fc3f7;\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', 'Arial Rounded MT Bold';\n"
"    text-align: center;\n"
"    margin-bottom: 30px;\n"
"    padding-bottom: 10px;\n"
"    border-bottom: 1px solid rgba(79, 195, 247, 0.3);\n"
"    text-shadow: 0 0 8px rgba(79, 195, 247, 0.5);\n"
"}\n"
"\n"
"/* ===== LABELS ===== */\n"
"QLabel[objectName=\"UserNameLabel\"], \n"
"QLabel[objectName*=\"password\"], \n"
"QLabel[objectName*=\"Password\"] {\n"
"    color: #90caf9;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    margin-left: 20px;\n"
"    margin-bottom: 5px;\n"
"    margin-top: 5px;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"\n"
"/* ===== CHAMPS DE SAISIE (LARGEUR R\303\211DUITE) ===== */\n"
""
                        "QLineEdit {\n"
"    background-color: rgba(30, 58, 95, 0.8);\n"
"    border: 2px solid #2d5278;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    font-size: 14px;\n"
"    color: #e3f2fd;\n"
"    font-family: 'Segoe UI', 'Arial';\n"
"    selection-background-color: #0288d1;\n"
"    selection-color: white;\n"
"    min-height: 42px;\n"
"    max-height: 42px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 20px;\n"
"    margin-right: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #29b6f6;\n"
"    background-color: rgba(41, 182, 246, 0.1);\n"
"    box-shadow: 0 0 10px rgba(41, 182, 246, 0.2);\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 2px solid #0288d1;\n"
"}\n"
"\n"
"/* ===== BOUTONS (LARGEUR R\303\211DUITE) ===== */\n"
"/* Bouton SIGN IN principal */\n"
"QPushButton#signinbtn {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0277bd,\n"
"        stop:0.5 #01579b,\n"
"        stop:1 #003f6b);\n"
"    color: white;\n"
""
                        "    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    margin-top: 20px;\n"
"    min-height: 46px;\n"
"    max-height: 46px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 20px;\n"
"    margin-right: 20px;\n"
"    letter-spacing: 1px;\n"
"    text-transform: uppercase;\n"
"}\n"
"\n"
"QPushButton#signinbtn:hover {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0288d1,\n"
"        stop:0.5 #0277bd,\n"
"        stop:1 #01579b);\n"
"    border: 1px solid #4fc3f7;\n"
"    box-shadow: 0 0 15px rgba(79, 195, 247, 0.3);\n"
"}\n"
"\n"
"QPushButton#signinbtn:pressed {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #01579b,\n"
"        stop:0.5 #013a63,\n"
"        stop:1 #002642);\n"
"}\n"
"\n"
"/* Bouton Face ID */\n"
"QPushButton#withfacebtn {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2"
                        ":1,\n"
"        stop:0 #00897b,\n"
"        stop:0.5 #00695c,\n"
"        stop:1 #004d40);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial;\n"
"    margin-top: 10px;\n"
"    min-height: 42px;\n"
"    max-height: 42px;\n"
"    min-width: 280px;\n"
"    max-width: 280px;\n"
"    margin-left: 20px;\n"
"    margin-right: 20px;\n"
"}\n"
"\n"
"QPushButton#withfacebtn:hover {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #009688,\n"
"        stop:0.5 #00796b,\n"
"        stop:1 #005b4f);\n"
"    border: 1px solid #4db6ac;\n"
"    box-shadow: 0 0 10px rgba(77, 182, 172, 0.2);\n"
"}\n"
"\n"
"QCheckBox#remembercheck {\n"
"    color: rgba(220, 232, 242, 0.80);\n"
"    font-size: 10.5pt;\n"
"    font-weight: 600;\n"
"    spacing: 10px;\n"
"}\n"
"\n"
"QCheckBox#remembercheck::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border-radi"
                        "us: 6px;\n"
"    border: 2px solid rgba(77, 159, 254, 0.70);\n"
"    background-color: rgba(0, 44, 114, 0.10);\n"
"}\n"
"\n"
"QCheckBox#remembercheck::indicator:checked {\n"
"    background-color: #4D9FFE;\n"
"    border: 2px solid #4D9FFE;\n"
"}\n"
"\n"
"/* ---------- Forgot link (PLUS DISCRET) ---------- */\n"
"QPushButton#btnForgetmdp {\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 4px 0px;\n"
"    color: rgba(220, 232, 242, 0.55);   /* gris clair, pas jaune */\n"
"    font-size: 10.5pt;\n"
"    font-weight: 600;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton#btnForgetmdp:hover {\n"
"    color: #FEBF00;                      /* jaune seulement au hover */\n"
"    text-decoration: underline;\n"
"}\n"
"\n"
"/* ===== ESPACEURS ET ALIGNEMENT ===== */\n"
"/* Pour forcer l'alignement vertical */\n"
"QWidget {\n"
"    margin: 0;\n"
"    padding: 0;\n"
"}\n"
"\n"
"/* Container pour centrer horizontalement */\n"
"QWidget > QLabel,\n"
"QWidget > QLineEdit,\n"
"QWidget > QPushButton,\n"
""
                        "QWidget > QCheckBox {\n"
"    margin-left: auto;\n"
"    margin-right: auto;\n"
"}\n"
"\n"
"/* ===== STYLE POUR \303\211L\303\211MENTS INVISIBLES ===== */\n"
"/* Cacher les \303\251l\303\251ments inutiles */\n"
"QMenuBar, QStatusBar {\n"
"    background-color: transparent;\n"
"    color: transparent;\n"
"    border: none;\n"
"    height: 0;\n"
"    min-height: 0;\n"
"    max-height: 0;\n"
"}\n"
"\n"
"/* ===== STYLES SP\303\211CIAUX POUR \303\211TATS ===== */\n"
"QLineEdit:invalid {\n"
"    border: 2px solid #ff5252;\n"
"    background-color: rgba(255, 82, 82, 0.1);\n"
"}\n"
"\n"
"QLineEdit:disabled,\n"
"QPushButton:disabled {\n"
"    background-color: rgba(66, 66, 66, 0.5);\n"
"    color: #757575;\n"
"    border-color: #424242;\n"
"    opacity: 0.6;\n"
"}\n"
"\n"
"/* ===== ANIMATIONS ET TRANSITIONS ===== */\n"
"QLineEdit, QPushButton, QCheckBox::indicator {\n"
"    transition: all 0.2s ease;\n"
"}\n"
"\n"
"/* ===== STYLE POUR LES MESSAGES ===== */\n"
"QLabel[objectName*=\"message\"], \n"
"QLabel[objectName*=\""
                        "status\"] {\n"
"    color: #81d4fa;\n"
"    font-size: 11px;\n"
"    font-style: italic;\n"
"    text-align: center;\n"
"    margin: 5px 20px;\n"
"    padding: 5px;\n"
"    border-radius: 4px;\n"
"    background-color: rgba(33, 150, 243, 0.1);\n"
"}"));
        UserNameEdit = new QLineEdit(pageSignIn);
        UserNameEdit->setObjectName("UserNameEdit");
        UserNameEdit->setGeometry(QRect(580, 190, 358, 46));
        PasswordEdit = new QLineEdit(pageSignIn);
        PasswordEdit->setObjectName("PasswordEdit");
        PasswordEdit->setGeometry(QRect(580, 290, 358, 46));
        UserNameLabel = new QLabel(pageSignIn);
        UserNameLabel->setObjectName("UserNameLabel");
        UserNameLabel->setGeometry(QRect(610, 130, 337, 61));
        UserNameLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        PasswordLabel = new QLabel(pageSignIn);
        PasswordLabel->setObjectName("PasswordLabel");
        PasswordLabel->setGeometry(QRect(610, 230, 261, 71));
        PasswordLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        signinbtn = new QPushButton(pageSignIn);
        signinbtn->setObjectName("signinbtn");
        signinbtn->setGeometry(QRect(600, 450, 348, 94));
        withfacebtn = new QPushButton(pageSignIn);
        withfacebtn->setObjectName("withfacebtn");
        withfacebtn->setGeometry(QRect(600, 560, 344, 76));
        btnForgetmdp = new QPushButton(pageSignIn);
        btnForgetmdp->setObjectName("btnForgetmdp");
        btnForgetmdp->setGeometry(QRect(630, 400, 301, 41));
        remembercheck = new QCheckBox(pageSignIn);
        remembercheck->setObjectName("remembercheck");
        remembercheck->setGeometry(QRect(650, 330, 411, 71));
        label_4 = new QLabel(pageSignIn);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 200, 471, 421));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/Images/logo.png")));
        stackedWidget->addWidget(pageSignIn);
        pageForgetpass = new QWidget();
        pageForgetpass->setObjectName("pageForgetpass");
        pageForgetpass->setStyleSheet(QString::fromUtf8("/* ===== FORGOT PAGE ===== */\n"
"QFrame#leftpanelForget {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 #0d2c4a,\n"
"        stop:0.5 #0a375b,\n"
"        stop:1 #073052);\n"
"    border-radius: 22px;\n"
"    border: 1px solid rgba(79,195,247,0.16);\n"
"}\n"
"\n"
"QFrame#rightpanelForget {\n"
"    background-color: rgba(255,255,255,0.06);\n"
"    border-radius: 22px;\n"
"    border: 1px solid rgba(255,255,255,0.14);\n"
"}\n"
"\n"
"/* Title of forgot page */\n"
"QLabel#ForgotTitle {\n"
"    color: #4fc3f7;\n"
"    font-size: 36px;\n"
"    font-weight: 900;\n"
"    qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"/* Instruction label */\n"
"QLabel#resetlabel {\n"
"    background: transparent;\n"
"    color: rgba(234,243,255,0.80);\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Input */\n"
"QLineEdit#resetlineEdit {\n"
"    min-height: 46px;\n"
"    min-width: 420px;\n"
"    max-width: 420px;\n"
"    background-color: rgba(25,45,65,0.65);\n"
"    borde"
                        "r: 1px solid rgba(255,255,255,0.16);\n"
"    border-radius: 14px;\n"
"    padding: 10px 14px;\n"
"    color: white;\n"
"}\n"
"QLineEdit#resetlineEdit:focus {\n"
"    border: 1px solid #4fc3f7;\n"
"}\n"
"\n"
"/* Buttons */\n"
"QPushButton#resetbtn {\n"
"    min-height: 54px;\n"
"    min-width: 420px;\n"
"    max-width: 420px;\n"
"    border-radius: 16px;\n"
"    background-color: #0A66FF;\n"
"    color: white;\n"
"    font-weight: 900;\n"
"    letter-spacing: 1px;\n"
"}\n"
"QPushButton#resetbtn:hover { background-color: rgba(10,102,255,0.86); }\n"
"\n"
"QPushButton#backsigninBTN {\n"
"    min-height: 52px;\n"
"    min-width: 420px;\n"
"    max-width: 420px;\n"
"    border-radius: 16px;\n"
"    background-color: rgba(255,255,255,0.08);\n"
"    color: rgba(234,243,255,0.85);\n"
"    border: 1px solid rgba(255,255,255,0.14);\n"
"    font-weight: 800;\n"
"}\n"
"QPushButton#backsigninBTN:hover {\n"
"    border: 1px solid rgba(79,195,247,0.35);\n"
"    color: #4fc3f7;\n"
"}\n"
""));
        ForgotTitle = new QLabel(pageForgetpass);
        ForgotTitle->setObjectName("ForgotTitle");
        ForgotTitle->setGeometry(QRect(290, 50, 451, 51));
        ForgotTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(pageForgetpass);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(80, 140, 891, 481));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftpanelForget = new QFrame(layoutWidget);
        leftpanelForget->setObjectName("leftpanelForget");
        leftpanelForget->setFrameShape(QFrame::Shape::StyledPanel);
        leftpanelForget->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(leftpanelForget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 331, 351));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Images/logo.png")));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        rightpannelforget = new QFrame(leftpanelForget);
        rightpannelforget->setObjectName("rightpannelforget");
        rightpannelforget->setGeometry(QRect(370, 0, 541, 479));
        rightpannelforget->setFrameShape(QFrame::Shape::StyledPanel);
        rightpannelforget->setFrameShadow(QFrame::Shadow::Raised);
        resetlabel = new QLabel(rightpannelforget);
        resetlabel->setObjectName("resetlabel");
        resetlabel->setGeometry(QRect(80, 80, 391, 20));
        resetlineEdit = new QLineEdit(rightpannelforget);
        resetlineEdit->setObjectName("resetlineEdit");
        resetlineEdit->setGeometry(QRect(60, 120, 450, 68));
        resetlineEdit->setMinimumSize(QSize(450, 68));
        resetlineEdit->setMaximumSize(QSize(450, 16777215));
        resetbtn = new QPushButton(rightpannelforget);
        resetbtn->setObjectName("resetbtn");
        resetbtn->setGeometry(QRect(60, 220, 420, 54));
        backsigninBTN = new QPushButton(rightpannelforget);
        backsigninBTN->setObjectName("backsigninBTN");
        backsigninBTN->setGeometry(QRect(60, 310, 422, 54));

        horizontalLayout->addWidget(leftpanelForget);

        stackedWidget->addWidget(pageForgetpass);
        pageStaffManagement = new QWidget();
        pageStaffManagement->setObjectName("pageStaffManagement");
        pageStaffManagement->setStyleSheet(QString::fromUtf8("/* =================================================\n"
"   PAGE STAFF MANAGEMENT - BACKGROUND\n"
"   ================================================= */\n"
"QWidget#pageStaffManagement {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #071a2c,\n"
"        stop:0.35 #082136,\n"
"        stop:0.7 #071c2d,\n"
"        stop:1 #040f1a);\n"
"    font-family: \"Segoe UI\";\n"
"    color: #EAF0FF;\n"
"}\n"
"\n"
"/* =================================================\n"
"   HEADER + SIDEBAR (SAME STYLE)\n"
"   ================================================= */\n"
"QFrame#header,\n"
"QFrame#sidebarMenu {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 rgba(12, 42, 75, 0.95),\n"
"        stop:0.55 rgba(8, 30, 55, 0.95),\n"
"        stop:1 rgba(6, 22, 40, 0.95));\n"
"    border: 1px solid rgba(255,255,255,0.12);\n"
"    border-radius: 16px;\n"
"}\n"
"\n"
"QFrame#header {\n"
"    padding: 10px 16px;\n"
"}\n"
"\n"
"QFrame#sidebarMenu {\n"
"    padding: 12px;\n"
""
                        "}\n"
"\n"
"/* =================================================\n"
"   HEADER CONTENT\n"
"   ================================================= */\n"
"QLabel#titreHeader {\n"
"    color: #EAF0FF;\n"
"    font-size: 15px;\n"
"    font-weight: 800;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"\n"
"QLabel#avatar {\n"
"    min-width: 42px;\n"
"    max-width: 42px;\n"
"    min-height: 42px;\n"
"    max-height: 42px;\n"
"    border-radius: 21px;\n"
"    border: 2px solid rgba(88,184,255,0.6);\n"
"    background-color: rgba(255,255,255,0.06);\n"
"}\n"
"\n"
"/* User profile button */\n"
"QCommandLinkButton#userprofiledetails {\n"
"    background-color: rgba(8, 18, 38, 0.55);\n"
"    border: 1px solid rgba(255,255,255,0.15);\n"
"    border-radius: 12px;\n"
"    padding: 8px 14px;\n"
"    color: #EAF0FF;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"QCommandLinkButton#userprofiledetails:hover {\n"
"    background-color: rgba(88,184,255,0.15);\n"
"    border: 1px solid rgba(88,184,255,0.45);\n"
"}\n"
"\n"
"QCommandLinkButton#userp"
                        "rofiledetails:pressed {\n"
"    background-color: rgba(88,184,255,0.25);\n"
"}\n"
"\n"
"/* =================================================\n"
"   SIDEBAR GROUP\n"
"   ================================================= */\n"
"QGroupBox#groupBox {\n"
"    border: none;\n"
"    margin-top: 6px;\n"
"}\n"
"\n"
"/* =================================================\n"
"   SIDEBAR BUTTONS (BASE)\n"
"   ================================================= */\n"
"QPushButton#clientsmanagementBTN,\n"
"QPushButton#equipmentmanagementBTN,\n"
"QPushButton#fishingzonemanagementBTN,\n"
"QPushButton#staffmanagementBTN,\n"
"QPushButton#stockmanagementBTN {\n"
"    background: transparent;\n"
"    border: none;\n"
"    color: rgba(234,240,255,0.80);\n"
"    padding: 12px 14px;\n"
"    border-radius: 12px;\n"
"    text-align: left;\n"
"    font-size: 13px;\n"
"    font-weight: 650;\n"
"}\n"
"\n"
"/* Hover effect */\n"
"QPushButton#clientsmanagementBTN:hover,\n"
"QPushButton#equipmentmanagementBTN:hover,\n"
"QPushButton#fishingzonem"
                        "anagementBTN:hover,\n"
"QPushButton#staffmanagementBTN:hover,\n"
"QPushButton#stockmanagementBTN:hover {\n"
"    background-color: rgba(88,184,255,0.14);\n"
"    border: 1px solid rgba(88,184,255,0.25);\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"/* Pressed */\n"
"QPushButton#clientsmanagementBTN:pressed,\n"
"QPushButton#equipmentmanagementBTN:pressed,\n"
"QPushButton#fishingzonemanagementBTN:pressed,\n"
"QPushButton#staffmanagementBTN:pressed,\n"
"QPushButton#stockmanagementBTN:pressed {\n"
"    background-color: rgba(88,184,255,0.25);\n"
"}\n"
"\n"
"/* =================================================\n"
"   ACTIVE / SELECTED BUTTON (Staff Management)\n"
"   ================================================= */\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: rgba(10, 102, 255, 0.28);\n"
"    border: 1px solid rgba(10, 102, 255, 0.55);\n"
"    color: #FFFFFF;\n"
"    padding-left: 18px;\n"
"}\n"
"QPushButton#staffmanagementBTN[active=\"true\"] {\n"
"    background-color: rgba(10, 102, 255, 0.35);\n"
" "
                        "   border-left: 4px solid #4FC3F7;\n"
"    color: white;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* =================================================\n"
"   LOG OUT BUTTON\n"
"   ================================================= */\n"
"QPushButton#logOutBTN {\n"
"    background: transparent;\n"
"    border: none;\n"
"    color: rgba(234,240,255,0.65);\n"
"    padding: 12px 14px;\n"
"    border-radius: 12px;\n"
"    text-align: left;\n"
"    font-weight: 650;\n"
"}\n"
"\n"
"QPushButton#logOutBTN:hover {\n"
"    background-color: rgba(255, 120, 120, 0.12);\n"
"    border: 1px solid rgba(255, 120, 120, 0.25);\n"
"    color: #FFC1C1;\n"
"}\n"
"\n"
"/* =================================================\n"
"   MAIN CONTENT AREA\n"
"   ================================================= */\n"
"QFrame#contenumain {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"/* =================================================\n"
"   MENUBAR + STATUSBAR\n"
"   ================================================= */\n"
"QMenuBar {"
                        "\n"
"    background-color: rgba(6, 22, 40, 0.95);\n"
"    color: rgba(234,240,255,0.85);\n"
"    border-bottom: 1px solid rgba(255,255,255,0.12);\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QStatusBar {\n"
"    background-color: rgba(6, 22, 40, 0.95);\n"
"    color: rgba(234,240,255,0.70);\n"
"    border-top: 1px solid rgba(255,255,255,0.12);\n"
"}\n"
"/* =======================\n"
"   FORM CARD (LEFT)\n"
"   objectName: formAddStaff\n"
"   ======================= */\n"
"QFrame#formAddStaff {\n"
"    background-color: rgba(255,255,255,0.06);\n"
"    border: 1px solid rgba(79,195,247,0.18);\n"
"    border-radius: 16px;\n"
"}\n"
"\n"
"/* Title label (labeladdstaff) */\n"
"QLabel#labeladdstaff {\n"
"    color: #E3F2FD;\n"
"    font-size: 18px;\n"
"    font-weight: 700;\n"
"    padding: 8px 0;\n"
"}\n"
"\n"
"/* All labels inside the form */\n"
"QFrame#formAddStaff QLabel {\n"
"    color: rgba(227,242,253,0.88);\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Inputs (LineEdits) */\n"
"QLineEdit {\n"
""
                        "    background-color: rgba(10, 35, 55, 0.65);\n"
"    color: #E3F2FD;\n"
"    border: 1px solid rgba(79,195,247,0.25);\n"
"    border-radius: 10px;\n"
"    padding: 8px 12px;\n"
"    min-height: 36px;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #4FC3F7;\n"
"    background-color: rgba(10, 35, 55, 0.85);\n"
"}\n"
"\n"
"/* ComboBoxes (role, cvstat) */\n"
"QComboBox {\n"
"    background-color: rgba(10, 35, 55, 0.65);\n"
"    color: #E3F2FD;\n"
"    border: 1px solid rgba(79,195,247,0.25);\n"
"    border-radius: 10px;\n"
"    padding: 7px 12px;\n"
"    min-height: 36px;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border: 1px solid rgba(79,195,247,0.45);\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 1px solid #4FC3F7;\n"
"    background-color: rgba(10, 35, 55, 0.85);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 36px;\n"
"    border: none;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    border-left: 6px solid transparent;\n"
""
                        "    border-right: 6px solid transparent;\n"
"    border-top: 8px solid rgba(227,242,253,0.8);\n"
"    margin-right: 10px;\n"
"}\n"
"\n"
"/* Upload CV Button (uploadcvbtn) */\n"
"QPushButton#uploadcvbtn {\n"
"    background-color: rgba(255,255,255,0.08);\n"
"    color: #E3F2FD;\n"
"    border: 1px dashed rgba(79,195,247,0.6);\n"
"    border-radius: 10px;\n"
"    padding: 8px 12px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Hover Upload */\n"
"QPushButton#uploadcvbtn:hover {\n"
"    background-color: rgba(79,195,247,0.2);\n"
"    border-color: #4FC3F7;\n"
"}\n"
"\n"
"/* Add Staff Button (addstaffbtn) */\n"
"QPushButton#addstaffbtn {\n"
"    background-color: #0288D1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    min-height: 40px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton#addstaffbtn:hover {\n"
"    background-color: #039BE5;\n"
"}\n"
"\n"
"QPushButton#addstaffbtn:pressed {\n"
"    background-color: #01579B;\n"
"}\n"
"/* ============================================="
                        "==== */\n"
"/* ============ STAFF LIST CONTAINER =============== */\n"
"/* ================================================= */\n"
"\n"
"#liststaffff {\n"
"    background-color: rgba(12, 32, 52, 0.95);\n"
"    border: 1px solid rgba(79, 195, 247, 0.25);\n"
"    border-radius: 18px;\n"
"    padding: 15px;\n"
"    margin-left: 10px;\n"
"}\n"
"\n"
"#liststaffff::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    top: 8px;\n"
"    padding: 0 8px;\n"
"    color: #4fc3f7;\n"
"    font-weight: 700;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* ================================================= */\n"
"/* ================= SEARCH BAR ==================== */\n"
"/* ================================================= */\n"
"\n"
"#staffsearchbarre {\n"
"    background-color: rgba(20, 45, 70, 0.9);\n"
"    border: 1px solid rgba(79, 195, 247, 0.4);\n"
"    border-radius: 14px;\n"
"    padding: 10px 15px;\n"
"    color: white;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"#staffsearchbarre:focus {\n"
"    border: 1p"
                        "x solid #4fc3f7;\n"
"    background-color: rgba(30, 75, 120, 0.9);\n"
"}\n"
"\n"
"/* ================================================= */\n"
"/* ================= SORT COMBO ==================== */\n"
"/* ================================================= */\n"
"\n"
"#sortstaff {\n"
"    background-color: rgba(20, 45, 70, 0.9);\n"
"    border: 1px solid rgba(79, 195, 247, 0.4);\n"
"    border-radius: 12px;\n"
"    padding: 6px 12px;\n"
"    color: #e3f2fd;\n"
"}\n"
"\n"
"#sortstaff:hover {\n"
"    background-color: rgba(79, 195, 247, 0.25);\n"
"}\n"
"\n"
"/* ================================================= */\n"
"/* ================== TABLE ======================== */\n"
"/* ================================================= */\n"
"\n"
"#tablestaff {\n"
"    background-color: rgba(10, 25, 40, 0.95);\n"
"    border: 1px solid rgba(79, 195, 247, 0.3);\n"
"    border-radius: 14px;\n"
"    gridline-color: rgba(79, 195, 247, 0.15);\n"
"    color: #e3f2fd;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"#tablestaff::item {\n"
""
                        "    padding: 8px;\n"
"}\n"
"\n"
"#tablestaff::item:selected {\n"
"    background-color: rgba(79, 195, 247, 0.35);\n"
"    color: white;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgba(15, 55, 90, 0.95);\n"
"    color: #4fc3f7;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Scrollbars table */\n"
"QTableWidget QScrollBar:vertical {\n"
"    background: transparent;\n"
"    width: 8px;\n"
"}\n"
"\n"
"QTableWidget QScrollBar::handle:vertical {\n"
"    background: #4fc3f7;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QTableWidget QScrollBar::add-line,\n"
"QTableWidget QScrollBar::sub-line {\n"
"    height: 0;\n"
"}\n"
"\n"
"/* ================================================= */\n"
"/* ================= BUTTONS ======================= */\n"
"/* ================================================= */\n"
"\n"
"\n"
"#cvanalysebtn,\n"
"#staticbtn,\n"
"#exportpdfstaffbtn {\n"
"    background-color: rgba(20, 60, 95, 0.9);\n"
"    border: 1px solid rgba(79, 195, 24"
                        "7, 0.4);\n"
"    border-radius: 12px;\n"
"    color: #e3f2fd;\n"
"    padding: 10px 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"\n"
"#cvanalysebtn:hover,\n"
"#staticbtn:hover,\n"
"#exportpdfstaffbtn:hover {\n"
"    background-color: rgba(79, 195, 247, 0.35);\n"
"    color: white;\n"
"}\n"
"\n"
"/* ===== DELETE BUTTON ===== */\n"
"#deletestaffbtn {\n"
"    background-color: rgba(183, 28, 28, 0.9);\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    padding: 10px 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"#deletestaffbtn:hover {\n"
"    background-color: #e53935;\n"
"    box-shadow: 0 0 15px rgba(244, 67, 54, 0.6);\n"
"}\n"
"/* ======================================= */\n"
"/* ========= MODIFY STAFF BUTTON ========= */\n"
"/* ======================================= */\n"
"\n"
"#modifystaffbtn {\n"
"    background-color: #f9a825;            /* Jaune principal */\n"
"    color: #1a1a1a;\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"    padding: 12px 20px;\n"
"    font-s"
                        "ize: 14px;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"/* Hover */\n"
"#modifystaffbtn:hover {\n"
"    background-color: #fbc02d;            /* Jaune plus clair */\n"
"    box-shadow: 0 0 15px rgba(251, 192, 45, 0.6);\n"
"}\n"
"\n"
"/* Click (pressed) */\n"
"#modifystaffbtn:pressed {\n"
"    background-color: #f57f17;            /* Jaune fonc\303\251 */\n"
"    box-shadow: inset 0 3px 6px rgba(0,0,0,0.35);\n"
"}\n"
""));
        layoutWidget1 = new QWidget(pageStaffManagement);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 0, 1491, 761));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        sidebarMenu = new QFrame(layoutWidget1);
        sidebarMenu->setObjectName("sidebarMenu");
        sidebarMenu->setMinimumSize(QSize(200, 0));
        sidebarMenu->setMaximumSize(QSize(200, 16777215));
        sidebarMenu->setFrameShape(QFrame::Shape::NoFrame);
        sidebarMenu->setFrameShadow(QFrame::Shadow::Raised);
        groupBox = new QGroupBox(sidebarMenu);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 100, 200, 581));
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setMaximumSize(QSize(200, 16777215));
        staffmanagementBTN = new QPushButton(groupBox);
        staffmanagementBTN->setObjectName("staffmanagementBTN");
        staffmanagementBTN->setGeometry(QRect(-10, 210, 181, 61));
        staffmanagementBTN->setProperty("active", QVariant(true));
        clientsmanagementBTN = new QPushButton(groupBox);
        clientsmanagementBTN->setObjectName("clientsmanagementBTN");
        clientsmanagementBTN->setGeometry(QRect(-10, 160, 191, 51));
        stockmanagementBTN = new QPushButton(groupBox);
        stockmanagementBTN->setObjectName("stockmanagementBTN");
        stockmanagementBTN->setGeometry(QRect(-10, 110, 171, 51));
        fishingzonemanagementBTN = new QPushButton(groupBox);
        fishingzonemanagementBTN->setObjectName("fishingzonemanagementBTN");
        fishingzonemanagementBTN->setGeometry(QRect(-10, 320, 221, 51));
        equipmentmanagementBTN = new QPushButton(groupBox);
        equipmentmanagementBTN->setObjectName("equipmentmanagementBTN");
        equipmentmanagementBTN->setGeometry(QRect(-10, 270, 201, 41));
        logoheader = new QLabel(sidebarMenu);
        logoheader->setObjectName("logoheader");
        logoheader->setGeometry(QRect(0, 10, 181, 151));
        logoheader->setPixmap(QPixmap(QString::fromUtf8(":/Images/logoHeader1.png")));
        logOutBTN = new QPushButton(sidebarMenu);
        logOutBTN->setObjectName("logOutBTN");
        logOutBTN->setGeometry(QRect(40, 650, 121, 61));

        horizontalLayout_2->addWidget(sidebarMenu);

        contenumain = new QFrame(layoutWidget1);
        contenumain->setObjectName("contenumain");
        contenumain->setFrameShape(QFrame::Shape::StyledPanel);
        contenumain->setFrameShadow(QFrame::Shadow::Raised);
        contenumain->setProperty("active", QVariant(true));
        verticalLayoutWidget = new QWidget(contenumain);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(-270, 0, 1431, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        header = new QFrame(verticalLayoutWidget);
        header->setObjectName("header");
        header->setFrameShape(QFrame::Shape::StyledPanel);
        header->setFrameShadow(QFrame::Shadow::Raised);
        titreHeader = new QLabel(header);
        titreHeader->setObjectName("titreHeader");
        titreHeader->setGeometry(QRect(220, 20, 461, 61));
        titreHeader->setAlignment(Qt::AlignmentFlag::AlignCenter);
        userprofiledetails = new QCommandLinkButton(header);
        userprofiledetails->setObjectName("userprofiledetails");
        userprofiledetails->setGeometry(QRect(830, 20, 211, 51));
        avatar = new QLabel(header);
        avatar->setObjectName("avatar");
        avatar->setGeometry(QRect(990, 20, 46, 46));
        avatar->setPixmap(QPixmap(QString::fromUtf8(":/Images/avatar.png")));

        verticalLayout_2->addWidget(header);

        layoutWidget2 = new QWidget(contenumain);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(-10, 100, 831, 621));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        liststaff = new QFrame(layoutWidget2);
        liststaff->setObjectName("liststaff");
        liststaff->setFrameShape(QFrame::Shape::StyledPanel);
        liststaff->setFrameShadow(QFrame::Shadow::Raised);
        liststaffff = new QGroupBox(liststaff);
        liststaffff->setObjectName("liststaffff");
        liststaffff->setGeometry(QRect(-10, 0, 821, 621));
        sortstaff = new QComboBox(liststaffff);
        sortstaff->addItem(QString());
        sortstaff->addItem(QString());
        sortstaff->addItem(QString());
        sortstaff->addItem(QString());
        sortstaff->setObjectName("sortstaff");
        sortstaff->setGeometry(QRect(210, 20, 151, 54));
        stafflistlabel = new QLabel(liststaffff);
        stafflistlabel->setObjectName("stafflistlabel");
        stafflistlabel->setGeometry(QRect(20, 20, 191, 51));
        stafflistlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tablestaff = new QTableWidget(liststaffff);
        if (tablestaff->columnCount() < 4)
            tablestaff->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablestaff->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablestaff->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablestaff->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablestaff->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tablestaff->rowCount() < 2)
            tablestaff->setRowCount(2);
        tablestaff->setObjectName("tablestaff");
        tablestaff->setGeometry(QRect(10, 90, 781, 261));
        tablestaff->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        tablestaff->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        tablestaff->setRowCount(2);
        tablestaff->setColumnCount(4);
        modifystaffbtn = new QPushButton(liststaffff);
        modifystaffbtn->setObjectName("modifystaffbtn");
        modifystaffbtn->setGeometry(QRect(150, 390, 161, 41));
        deletestaffbtn = new QPushButton(liststaffff);
        deletestaffbtn->setObjectName("deletestaffbtn");
        deletestaffbtn->setGeometry(QRect(390, 390, 171, 41));
        deletestaffbtn->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";"));
        cvanalysebtn = new QPushButton(liststaffff);
        cvanalysebtn->setObjectName("cvanalysebtn");
        cvanalysebtn->setGeometry(QRect(210, 450, 261, 41));
        staticbtn = new QPushButton(liststaffff);
        staticbtn->setObjectName("staticbtn");
        staticbtn->setGeometry(QRect(150, 520, 161, 41));
        exportpdfstaffbtn = new QPushButton(liststaffff);
        exportpdfstaffbtn->setObjectName("exportpdfstaffbtn");
        exportpdfstaffbtn->setGeometry(QRect(380, 520, 191, 41));
        lineEdit = new QLineEdit(liststaffff);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(390, 20, 371, 54));

        horizontalLayout_3->addWidget(liststaff);


        horizontalLayout_2->addWidget(contenumain);

        stackedWidget->addWidget(pageStaffManagement);
        SignIn->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignIn);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1017, 0));
        SignIn->setMenuBar(menubar);
        statusbar = new QStatusBar(SignIn);
        statusbar->setObjectName("statusbar");
        SignIn->setStatusBar(statusbar);

        retranslateUi(SignIn);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SignIn);
    } // setupUi

    void retranslateUi(QMainWindow *SignIn)
    {
        SignIn->setWindowTitle(QCoreApplication::translate("SignIn", "BORT-SignIn", nullptr));
        UserNameLabel->setText(QCoreApplication::translate("SignIn", "User Name", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("SignIn", "Password", nullptr));
        signinbtn->setText(QCoreApplication::translate("SignIn", "Sign In", nullptr));
        withfacebtn->setText(QCoreApplication::translate("SignIn", "Sign In With Face Id", nullptr));
        btnForgetmdp->setText(QCoreApplication::translate("SignIn", "Forget your Password?", nullptr));
        remembercheck->setText(QCoreApplication::translate("SignIn", "Remember me", nullptr));
        label_4->setText(QString());
        ForgotTitle->setText(QCoreApplication::translate("SignIn", "Forgot Your Password?", nullptr));
        label->setText(QString());
        resetlabel->setText(QCoreApplication::translate("SignIn", "Enter your email or username to reset your password", nullptr));
        resetbtn->setText(QCoreApplication::translate("SignIn", "Send Reset Link", nullptr));
        backsigninBTN->setText(QCoreApplication::translate("SignIn", "Back To Sign In", nullptr));
        groupBox->setTitle(QString());
        staffmanagementBTN->setText(QCoreApplication::translate("SignIn", "\360\237\220\237 Stock Management", nullptr));
        clientsmanagementBTN->setText(QCoreApplication::translate("SignIn", "\360\237\222\260Clients Management", nullptr));
        stockmanagementBTN->setText(QCoreApplication::translate("SignIn", "\360\237\221\251\360\237\217\273\342\200\215\360\237\222\274Staff Management", nullptr));
        fishingzonemanagementBTN->setText(QCoreApplication::translate("SignIn", "\360\237\227\272\357\270\217 Fishing Zone Management", nullptr));
        equipmentmanagementBTN->setText(QCoreApplication::translate("SignIn", "\342\232\223Equipment Management", nullptr));
        logoheader->setText(QString());
        logOutBTN->setText(QCoreApplication::translate("SignIn", "\342\217\273 Log Out", nullptr));
        titreHeader->setText(QCoreApplication::translate("SignIn", "BORT- Smart Fishing Port Application", nullptr));
        userprofiledetails->setText(QCoreApplication::translate("SignIn", "Despacito", nullptr));
        avatar->setText(QCoreApplication::translate("SignIn", "despa", nullptr));
        liststaffff->setTitle(QString());
        sortstaff->setItemText(0, QCoreApplication::translate("SignIn", "Sort with.....", nullptr));
        sortstaff->setItemText(1, QCoreApplication::translate("SignIn", "Fish species", nullptr));
        sortstaff->setItemText(2, QCoreApplication::translate("SignIn", "Quantity", nullptr));
        sortstaff->setItemText(3, QCoreApplication::translate("SignIn", "Zone", nullptr));

        stafflistlabel->setText(QCoreApplication::translate("SignIn", "Fish stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablestaff->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SignIn", "Fish species", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablestaff->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SignIn", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablestaff->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SignIn", "Phone Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablestaff->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SignIn", "Zone", nullptr));
        modifystaffbtn->setText(QCoreApplication::translate("SignIn", "3D Visualization", nullptr));
        deletestaffbtn->setText(QCoreApplication::translate("SignIn", "Add/Delete Species", nullptr));
        cvanalysebtn->setText(QCoreApplication::translate("SignIn", "Object recognition", nullptr));
        staticbtn->setText(QCoreApplication::translate("SignIn", "Go To Statistics", nullptr));
        exportpdfstaffbtn->setText(QCoreApplication::translate("SignIn", "Export To PDF", nullptr));
        lineEdit->setText(QCoreApplication::translate("SignIn", "Search....", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignIn: public Ui_SignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
