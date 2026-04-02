#include "signin.h"
#include "ui_signin.h"
#include "equipment.h"

#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QPageLayout>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QScrollBar>
#include <algorithm>

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

// Bold, uppercase, clearly readable field labels
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
//  CONSTRUCTOR
// ═══════════════════════════════════════════════════════════════════

SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);

    setupFormWidgets();
    setupTableStyle();
    setupSearchBar();
    setupSortCombo();
    setupButtonStyles();
    setupNavHighlight();

    ui->stackedWidget->setCurrentWidget(ui->pageEquipmentForm);

    // Navigation
    auto goForm = [this]() { ui->stackedWidget->setCurrentWidget(ui->pageEquipmentForm); };
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

    connect(ui->backWbtnE_F, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    auto goLogout = [this]() { ui->stackedWidget->setCurrentIndex(0); };
    connect(ui->logOutBTN_W,  &QPushButton::clicked, this, goLogout);
    connect(ui->logOutBTN_D,  &QPushButton::clicked, this, goLogout);
    connect(ui->logOutBTNe_F, &QPushButton::clicked, this, goLogout);

    connect(ui->addEqbtn_F,      &QPushButton::clicked, this, &SignIn::on_addEqbtn_F_clicked);
    connect(ui->exportpdfbtnE_L, &QPushButton::clicked, this, &SignIn::on_exportpdfbtnE_L_clicked);
    connect(ui->chatbotbtn_L,    &QPushButton::clicked, this, &SignIn::on_chatbotbtn_L_clicked);
    connect(ui->chatbotbtn_2_L,  &QPushButton::clicked, this, &SignIn::on_chatbotbtn_L_clicked);

    connect(ui->modifybtn_L, &QPushButton::clicked, this, [this]() {
        int r = ui->tableeq_L->currentRow();
        if (r >= 0) editRowInline(r);
        else QMessageBox::information(this, "Info", "Click ✏ on a row to edit it.");
    });

    connect(ui->deletebtnE_L, &QPushButton::clicked, this, [this]() {
        int r = ui->tableeq_L->currentRow();
        if (r >= 0) deleteRowInline(r);
        else QMessageBox::information(this, "Info", "Click 🗑 on a row to delete it.");
    });

    connect(ui->searchbar_L, &QLineEdit::textChanged, this, &SignIn::filterAndSortTable);

    connect(ui->sortEq_L, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SignIn::filterAndSortTable);

    loadEquipmentList();
}
// ═══════════════════════════════════════════════════════════════════
//  FORM WIDGET INJECTION
//  The form card (formEq / formcontEq_F) is 731px wide.
//  We center everything: labels left-aligned at x=150, fields at x=310.
//  SpinBoxes replace the hidden quantityedit_F and capacity_F.
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupFormWidgets()
{
    // ── Text fields ──
    for (auto *le : { ui->Eqnameedit_F, ui->Eqaddressedit_F, ui->stateedit_F }) {
        if (!le) continue;
        le->setStyleSheet(kField);
        le->setMinimumHeight(44);
    }
    if (ui->Eqnameedit_F)    ui->Eqnameedit_F->setPlaceholderText("e.g.  Caterpillar D9");
    if (ui->Eqaddressedit_F) ui->Eqaddressedit_F->setPlaceholderText("e.g.  Hydraulic / Crane");
    if (ui->stateedit_F)     ui->stateedit_F->setPlaceholderText("Good  /  Maintenance  /  Broken");

    // ── Labels: bold, visible, left-aligned ──
    for (auto *lb : { ui->Eqnamelabel_F, ui->Eqaddresslabel_F,
                     ui->statelabel_F,  ui->quantitylabel_F, ui->capacitylab_F }) {
        if (!lb) continue;
        lb->setStyleSheet(kLabel);
        lb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }

    // ── Form title: centered ──
    if (ui->labeladdeq_F) {
        ui->labeladdeq_F->setText("⚓  Register New Equipment");
        ui->labeladdeq_F->setAlignment(Qt::AlignCenter);
        ui->labeladdeq_F->setStyleSheet(
            "QLabel{"
            "  color:#4fc3f7;"
            "  font-size:20px;"
            "  font-weight:900;"
            "  letter-spacing:1px;"
            "  background:transparent;"
            "  border-bottom:2px solid rgba(79,195,247,0.28);"
            "  padding-bottom:6px;"
            "}");
    }

    // ── QUANTITY: replace quantityedit_F with a QSpinBox (NUMBER column = int) ──
    if (ui->quantityedit_F) {
        QRect    geo = ui->quantityedit_F->geometry();
        QWidget *par = ui->quantityedit_F->parentWidget();
        ui->quantityedit_F->hide();

        m_qtySpinBox = new QSpinBox(par);
        m_qtySpinBox->setGeometry(geo);           // same position & size as original field
        m_qtySpinBox->setRange(0, 999999);
        m_qtySpinBox->setValue(0);
        m_qtySpinBox->setAlignment(Qt::AlignCenter);
        m_qtySpinBox->setToolTip("Enter quantity (whole number)");
        m_qtySpinBox->setStyleSheet(
            kField + "QSpinBox{color:#4fc3f7;font-size:16px;font-weight:800;}");
        m_qtySpinBox->show();
    }

    // ── CAPACITY: replace capacity_F with a QSpinBox (NUMBER column = int) ──
    if (ui->capacity_F) {
        QRect    geo = ui->capacity_F->geometry();
        QWidget *par = ui->capacity_F->parentWidget();
        ui->capacity_F->hide();

        m_capSpinBox = new QSpinBox(par);
        m_capSpinBox->setGeometry(geo);           // same position & size as original field
        m_capSpinBox->setRange(0, 9999999);
        m_capSpinBox->setValue(0);
        m_capSpinBox->setAlignment(Qt::AlignCenter);
        m_capSpinBox->setToolTip("Enter capacity (whole number)");
        m_capSpinBox->setStyleSheet(
            kField + "QSpinBox{color:#4fc3f7;font-size:16px;font-weight:800;}");
        m_capSpinBox->show();
    }
}

// ═══════════════════════════════════════════════════════════════════
//  TABLE STYLE
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupTableStyle()
{
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
        QScrollBar:vertical {
            background: transparent; width: 6px; border-radius: 3px;
        }
        QScrollBar::handle:vertical {
            background: rgba(79,195,247,0.45); border-radius: 3px; min-height: 28px;
        }
        QScrollBar::handle:vertical:hover { background: #4fc3f7; }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; border: none; }
    )");

    auto *sh = new QGraphicsDropShadowEffect(t);
    sh->setBlurRadius(22); sh->setColor(QColor(41,182,246,45)); sh->setOffset(0,4);
    t->setGraphicsEffect(sh);
}

// ═══════════════════════════════════════════════════════════════════
//  SEARCH BAR
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupSearchBar()
{
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

void SignIn::setupSortCombo()
{
    auto *cb = ui->sortEq_L;
    cb->clear();
    cb->addItems({"⇅  Sort by…","▲  Name A→Z","▼  Name Z→A",
                  "▲  Type A→Z","▼  Type Z→A",
                  "▲  Qty ↑",   "▼  Qty ↓","●  State"});
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

QPushButton* SignIn::makeIconBtn(const QString &label, const QString &color,
                                 const QString &border, QWidget *parent)
{
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

void SignIn::setupButtonStyles()
{
    struct B { QPushButton *btn; QString c1, c2, bd; };
    QList<B> lb = {
                   {ui->modifybtn_L,    "#7a5800","#e6a817","#f0c040"},
                   {ui->deletebtnE_L,   "#8b0000","#c62828","#ef5350"},
                   {ui->chatbotbtn_L,   "#0d3a8a","#1565c0","#42a5f5"},
                   {ui->goToFormBtnE,   "#1b5e20","#2e7d32","#66bb6a"},
                   {ui->staticbtnE_L,   "#004d40","#00695c","#26a69a"},
                   {ui->exportpdfbtnE_L,"#263238","#37474f","#78909c"},
                   {ui->chatbotbtn_2_L, "#38006b","#6a1b9a","#ce93d8"},
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
        fx->setBlurRadius(10); fx->setColor(QColor(b.bd)); fx->setOffset(0,3);
        b.btn->setGraphicsEffect(fx);
    }

    // Primary CTA — Add Equipment
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
        fx->setBlurRadius(22); fx->setColor(QColor("#1e88e5")); fx->setOffset(0,5);
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
    if (ui->backWbtnE_F) {
        ui->backWbtnE_F->setStyleSheet(R"(
            QPushButton {
                background:rgba(20,38,58,0.55); color:rgba(234,240,255,0.80);
                border:1px solid rgba(120,160,200,0.22); border-radius:12px;
                padding:10px 18px; font-size:13px; font-weight:700;
            }
            QPushButton:hover { background:rgba(37,99,235,0.18); border:1px solid rgba(88,184,255,0.55); color:#fff; }
        )");
    }
}

// ═══════════════════════════════════════════════════════════════════
//  SIDEBAR HIGHLIGHT
// ═══════════════════════════════════════════════════════════════════

void SignIn::setupNavHighlight()
{
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
    for (auto *b : {ui->staffmanagementBTNe_F,     ui->clientsmanagementBTNe_F,
                    ui->stockmanagementBTNe_F,      ui->fishingzonemanagementBTNe_F,
                    ui->staffmanagementBTNe_L,      ui->clientsmanagementBTNe_L,
                    ui->stockmanagementBTNe_L,      ui->fishingzonemanagementBTNe_L})
        if (b) b->setStyleSheet(normal);
}

// ═══════════════════════════════════════════════════════════════════
//  LOAD DATA  —  QTE & CAPACITE are ints
// ═══════════════════════════════════════════════════════════════════

void SignIn::loadEquipmentList()
{
    m_allEq.clear();

    auto rows = equipment::getAll();

    for (auto &r : rows) {
        EqRow row;
        row.name  = r[0];
        row.type  = r[1];
        row.state = r[2];
        row.qty   = r[3].toInt();
        row.cap   = r[4].toInt();
        m_allEq.append(row);
    }

    filterAndSortTable();
}

// ═══════════════════════════════════════════════════════════════════
//  FILTER + SORT  →  TABLE
// ═══════════════════════════════════════════════════════════════════

void SignIn::filterAndSortTable()
{
    QString f = ui->searchbar_L->text().trimmed().toLower();
    int si    = ui->sortEq_L->currentIndex();

    QList<EqRow> rows;
    for (const auto &r : m_allEq) {
        if (f.isEmpty()
            || r.name.toLower().contains(f)
            || r.type.toLower().contains(f)
            || r.state.toLower().contains(f)
            || QString::number(r.qty).contains(f)
            || QString::number(r.cap).contains(f))
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

void SignIn::addRowButtons(int row)
{
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
//  ADD EQUIPMENT  — ✅ binds plain int to NUMBER columns
// ═══════════════════════════════════════════════════════════════════

void SignIn::on_addEqbtn_F_clicked()
{
    QString name  = ui->Eqnameedit_F    ? ui->Eqnameedit_F->text().trimmed()    : "";
    QString type  = ui->Eqaddressedit_F ? ui->Eqaddressedit_F->text().trimmed() : "";
    QString state = ui->stateedit_F     ? ui->stateedit_F->text().trimmed()     : "Good";
    int     qty   = m_qtySpinBox        ? m_qtySpinBox->value()                 : 0;
    int     cap   = m_capSpinBox        ? m_capSpinBox->value()                 : 0;

    // Validation (UNCHANGED)
    auto flash = [](QLineEdit *le, bool err) {
        if (!le) return;
        le->setStyleSheet(err
                              ? "QLineEdit{border:1.5px solid #ef5350;border-radius:10px;"
                                "background:rgba(239,83,80,0.09);padding:7px 14px;color:#EAF0FF;font-size:13px;min-height:38px;}"
                              : "QLineEdit{border:1.5px solid #29b6f6;border-radius:10px;"
                                "background:rgba(41,182,246,0.07);padding:7px 14px;color:#EAF0FF;font-size:13px;min-height:38px;}");
    };

    bool err = false;
    if (name.isEmpty()) { flash(ui->Eqnameedit_F, true); err = true; }
    else                flash(ui->Eqnameedit_F, false);

    if (type.isEmpty()) { flash(ui->Eqaddressedit_F, true); err = true; }
    else                flash(ui->Eqaddressedit_F, false);

    if (err) {
        QMessageBox::warning(this, "⚠  Missing Fields",
                             "Please fill in:\n\n  • Equipment Name\n  • Equipment Type");
        return;
    }

    // ✅ REPLACED SQL WITH DATA CLASS
    equipment e(name, type, state.isEmpty() ? "Good" : state, qty, cap);

    if (e.ajouter()) {

        // Success flash (UNCHANGED)
        if (ui->addEqbtn_F) {
            ui->addEqbtn_F->setStyleSheet(
                "QPushButton{background:#2e7d32;color:white;border:1.5px solid #66bb6a;"
                "border-radius:13px;padding:13px 22px;font-size:15px;font-weight:800;}");
            QTimer::singleShot(900, this, [this]() { setupButtonStyles(); });
        }

        QMessageBox::information(this, "✅  Added",
                                 "\"" + name + "\" registered successfully!");

        // Clear form (UNCHANGED)
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
//  EDIT ROW INLINE  — ✅ QSpinBox for qty & cap (NUMBER columns)
// ═══════════════════════════════════════════════════════════════════

void SignIn::editRowInline(int row)
{
    QTableWidget *t = ui->tableeq_L;
    if (row < 0 || row >= t->rowCount() || t->columnSpan(row,0) > 1) return;

    auto txt = [&](int col) -> QString {
        auto *it = t->item(row, col); return it ? it->text() : "";
    };
    QString oldName  = txt(COL_NAME);
    QString oldType  = txt(COL_TYPE);
    QString oldState = txt(COL_STATE);
    int     oldQty   = txt(COL_QTY).toInt();
    int     oldCap   = txt(COL_CAP).toInt();

    QDialog dlg(this);
    dlg.setWindowTitle("✏  Edit Equipment");
    dlg.setFixedSize(460, 430);
    dlg.setStyleSheet("QDialog{background:#071a2c;}");

    auto *vl = new QVBoxLayout(&dlg);
    vl->setContentsMargins(28,22,28,22);
    vl->setSpacing(6);

    auto *hdr = new QLabel("✏  " + oldName);
    hdr->setStyleSheet("color:#4fc3f7;font-size:16px;font-weight:900;background:transparent;"
                       "border-bottom:2px solid rgba(79,195,247,0.25);padding-bottom:6px;margin-bottom:4px;");
    vl->addWidget(hdr);

    auto *grid = new QWidget;
    auto *gl   = new QGridLayout(grid);
    gl->setColumnStretch(0,0); gl->setColumnStretch(1,1);
    gl->setHorizontalSpacing(14); gl->setVerticalSpacing(10);

    auto addRow = [&](int r, const QString &lbl, QWidget *w) {
        auto *lb = new QLabel(lbl); lb->setStyleSheet(kLabel);
        lb->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        gl->addWidget(lb, r, 0);
        gl->addWidget(w,  r, 1);
    };

    auto *leName  = new QLineEdit(oldName);  leName->setStyleSheet(kField);  leName->setMinimumHeight(40);
    auto *leType  = new QLineEdit(oldType);  leType->setStyleSheet(kField);  leType->setMinimumHeight(40);
    auto *leState = new QLineEdit(oldState); leState->setStyleSheet(kField); leState->setMinimumHeight(40);
    auto *spQ     = new QSpinBox; spQ->setRange(0,999999); spQ->setValue(oldQty);
    spQ->setStyleSheet(kField+"QSpinBox{color:#4fc3f7;font-weight:800;}"); spQ->setMinimumHeight(40);
    auto *spC     = new QSpinBox; spC->setRange(0,9999999); spC->setValue(oldCap);
    spC->setStyleSheet(kField+"QSpinBox{color:#4fc3f7;font-weight:800;}"); spC->setMinimumHeight(40);

    addRow(0, "NAME  *",     leName);
    addRow(1, "TYPE  *",     leType);
    addRow(2, "STATE",       leState);
    addRow(3, "QUANTITY",    spQ);
    addRow(4, "CAPACITY",    spC);
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

    connect(save, &QPushButton::clicked, &dlg, [&]() {
        if (leName->text().trimmed().isEmpty() || leType->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dlg, "Error", "Name and Type are required.");
            return;
        }

        // ✅ REPLACED SQL WITH DATA CLASS
        equipment e(
            leName->text().trimmed(),
            leType->text().trimmed(),
            leState->text().trimmed(),
            spQ->value(),
            spC->value()
            );

        if (e.modifier(oldName)) {
            dlg.accept();
        } else {
            QMessageBox::critical(&dlg, "❌ Error", "Update failed.");
        }
    });

    if (dlg.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "✅  Updated", "Equipment updated successfully.");
        loadEquipmentList();
    }
}

// ═══════════════════════════════════════════════════════════════════
//  DELETE ROW INLINE
// ═══════════════════════════════════════════════════════════════════

void SignIn::deleteRowInline(int row)
{
    QTableWidget *t = ui->tableeq_L;
    if (row < 0 || row >= t->rowCount() || t->columnSpan(row,0) > 1) return;

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

    // ✅ REPLACED SQL WITH DATA CLASS
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

void SignIn::on_exportpdfbtnE_L_clicked()
{
    QString path = QFileDialog::getSaveFileName(
        this, "Export Equipment List", "equipment_list.pdf", "PDF (*.pdf)");
    if (path.isEmpty()) return;

    QPdfWriter w(path);
    w.setPageSize(QPageSize(QPageSize::A4));
    w.setPageOrientation(QPageLayout::Landscape);
    w.setResolution(96);
    QPainter p(&w);

    int rows = ui->tableeq_L->rowCount();
    const int DCOLS = 5;
    const int colW = 200, rowH = 55, sx = 80, sy = 180;

    p.setPen(QColor("#1565c0"));
    p.setFont(QFont("Segoe UI", 18, QFont::Bold));
    p.drawText(sx, 110, "BORT — Equipment List");
    p.setFont(QFont("Segoe UI", 9));
    p.setPen(QColor("#666"));
    p.drawText(sx, 150, "Exported: " + QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm"));

    p.fillRect(sx, sy, colW * DCOLS, rowH, QColor("#1565c0"));
    p.setPen(Qt::white);
    p.setFont(QFont("Segoe UI", 9, QFont::Bold));
    QStringList hdr = {"NAME","TYPE","STATE","QUANTITY","CAPACITY"};
    for (int c = 0; c < DCOLS; ++c) p.drawText(sx + c*colW + 10, sy + 35, hdr[c]);

    p.setFont(QFont("Segoe UI", 9));
    for (int r = 0; r < rows; ++r) {
        p.fillRect(sx, sy+(r+1)*rowH, colW*DCOLS, rowH,
                   (r%2==0) ? QColor("#edf2f7") : QColor("#fff"));
        p.setPen(QColor("#1a202c"));
        for (int c = 0; c < DCOLS; ++c) {
            auto *it = ui->tableeq_L->item(r, c);
            if (it) p.drawText(sx + c*colW + 10, sy+(r+1)*rowH + 35, it->text());
        }
    }
    p.end();
    QMessageBox::information(this, "✅  PDF Exported", "Saved to:\n" + path);
}

// ═══════════════════════════════════════════════════════════════════
//  CHATBOT
// ═══════════════════════════════════════════════════════════════════

void SignIn::on_chatbotbtn_L_clicked()
{
    QDialog dlg(this);
    dlg.setWindowTitle("🤖  BORT AI Assistant");
    dlg.setFixedSize(500, 580);
    dlg.setStyleSheet("QDialog{background:#071a2c;}");

    auto *vl = new QVBoxLayout(&dlg);
    vl->setContentsMargins(20,20,20,20); vl->setSpacing(10);

    auto *hdr = new QLabel("🤖  BORT AI Assistant");
    hdr->setStyleSheet("color:#4fc3f7;font-size:17px;font-weight:800;background:transparent;");
    vl->addWidget(hdr);

    auto *chat = new QTextEdit;
    chat->setReadOnly(true);
    chat->setStyleSheet("QTextEdit{background:rgba(6,20,38,0.95);border:1.5px solid "
                        "rgba(79,195,247,0.22);border-radius:10px;color:#EAF0FF;font-size:13px;padding:10px;}");

    chat->append("<span style='color:#4fc3f7;font-weight:700;'>🤖 BORT:</span>"
                 " Hello! Try: <i>how many, list broken, show all, help</i>");
    vl->addWidget(chat, 1);

    auto *row = new QWidget;
    auto *hl = new QHBoxLayout(row);
    hl->setContentsMargins(0,0,0,0);
    hl->setSpacing(8);

    auto *inp  = new QLineEdit;
    inp->setPlaceholderText("Ask something…");
    inp->setStyleSheet(kField);
    inp->setMinimumHeight(40);

    auto *send = new QPushButton("Send  ▶");
    send->setStyleSheet("QPushButton{background:#1565c0;color:white;border:1.5px solid #42a5f5;"
                        "border-radius:9px;padding:9px 18px;font-weight:700;}"
                        "QPushButton:hover{background:#1e88e5;}");

    hl->addWidget(inp, 1);
    hl->addWidget(send);
    vl->addWidget(row);

    auto respond = [&](const QString &msg) {
        QString q = msg.toLower().trimmed();
        QString reply;

        auto rows = equipment::getAll();

        if (q.contains("how many") || q.contains("count")) {
            reply = "There are <b>" + QString::number(rows.size()) + "</b> equipment items.";
        }
        else if (q.contains("broken") || q.contains("repair") || q.contains("hors")) {
            QStringList ns;
            for (auto &r : rows) {
                QString state = r[2].toLower();
                if (state.contains("broken") || state.contains("repair") || state.contains("hors"))
                    ns << r[0];
            }
            reply = ns.isEmpty()
                        ? "✅ No equipment needs attention."
                        : "⚠ Needs attention:<br>• " + ns.join("<br>• ");
        }
        else if (q.contains("list") || q.contains("show")) {
            QStringList pts;
            for (auto &r : rows) {
                pts << r[0] + " — " + r[2];
            }
            reply = pts.isEmpty() ? "No equipment." : pts.join("<br>");
        }
        else if (q.contains("help")) {
            reply = "Commands:<br>• <i>how many equipment</i><br>• <i>list broken</i><br>• <i>show all</i>";
        }
        else {
            reply = "Type <i>help</i> for available commands.";
        }

        chat->append("<br><span style='color:#90caf9;font-weight:700;'>👤 You:</span> " + msg);
        chat->append("<span style='color:#4fc3f7;font-weight:700;'>🤖 BORT:</span> " + reply);
    };

    connect(send, &QPushButton::clicked, [&]() {
        QString t = inp->text().trimmed();
        if (!t.isEmpty()) {
            respond(t);
            inp->clear();
        }
    });

    connect(inp, &QLineEdit::returnPressed, send, &QPushButton::click);

    dlg.exec();
}
// ═══════════════════════════════════════════════════════════════════
//  DESTRUCTOR
// ═══════════════════════════════════════════════════════════════════

SignIn::~SignIn() { delete ui; }
