#include "vesselstatsdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QSpinBox>
#include <QInputDialog>
#include <QLineEdit>

// ─────────────────────────────────────────────────────────────────────────────
//  Column indices (keeps magic numbers out of the logic)
// ─────────────────────────────────────────────────────────────────────────────
enum Col {
    ColName     = 0,
    ColCapacity = 1,
    ColLoad     = 2,
    ColStatus   = 3,
    ColCount    = 4
};

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor — build entire UI
// ─────────────────────────────────────────────────────────────────────────────
VesselStatsDialog::VesselStatsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Vessels Dashboard");
    setMinimumSize(820, 720);   // slightly taller to accommodate the chart
    setStyleSheet(
        "QDialog          { background: #071a2c; color: #d0e8ff; }"
        "QGroupBox        { border: 1px solid #1a3a5c; border-radius: 8px;"
        "                   margin-top: 10px; font-weight: bold; color: #4fc3f7; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; top: 3px; }"
        "QLabel           { color: #90caf9; }"
        "QTableWidget     { background: #061426; border: 1px solid #1a3a5c;"
        "                   border-radius: 8px; color: #d0e8ff; gridline-color: #0d2a4a; }"
        "QTableWidget::item         { padding: 4px 8px; }"
        "QTableWidget::item:selected { background: #1565c0; }"
        "QHeaderView::section       { background: #0a2040; color: #4fc3f7;"
        "                             border: none; border-bottom: 1px solid #1a3a5c;"
        "                             padding: 6px; font-weight: bold; }"
        "QSpinBox          { background: #081c34; border: 1px solid #1e4976;"
        "                    border-radius: 5px; padding: 3px 6px; color: #d0e8ff; }"
        "QSpinBox:focus    { border-color: #29b6f6; }"
        "QPushButton       { background: #1565c0; color: white;"
        "                    border: 1px solid #1e88e5; border-radius: 8px;"
        "                    padding: 8px 20px; font-weight: bold; }"
        "QPushButton:hover { background: #1976d2; }"
        "QPushButton#removeBtn { background: #b71c1c; border-color: #e53935; }"
        "QPushButton#removeBtn:hover { background: #c62828; }"
        );

    // ── Summary cards ─────────────────────────────────────────────────────────
    auto makeCard = [](const QString &title) -> QLabel* {
        QLabel *lbl = new QLabel("—");
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet(
            "QLabel { background: #0a2040; border: 1px solid #1a3a5c;"
            "         border-radius: 8px; padding: 10px 18px;"
            "         color: #4fc3f7; font-size: 16px; font-weight: bold; "
            "         min-width: 120px; }"
            );
        lbl->setToolTip(title);
        return lbl;
    };

    lblVesselCount   = makeCard("Total Vessels");
    lblTotalCapacity = makeCard("Total Capacity (tons)");
    lblTotalLoad     = makeCard("Total Load (tons)");
    lblAvgLoad       = makeCard("Average Load %");

    QGroupBox  *summaryGroup  = new QGroupBox("Fleet Summary", this);
    QHBoxLayout *summaryLayout = new QHBoxLayout(summaryGroup);
    summaryLayout->setContentsMargins(12, 18, 12, 12);
    summaryLayout->setSpacing(12);

    auto addCard = [&](QLabel *lbl, const QString &caption) {
        QVBoxLayout *col = new QVBoxLayout;
        QLabel *cap = new QLabel(caption);
        cap->setAlignment(Qt::AlignCenter);
        cap->setStyleSheet("color:#607d8b; font-size:11px;");
        col->addWidget(lbl);
        col->addWidget(cap);
        summaryLayout->addLayout(col);
    };

    addCard(lblVesselCount,   "Vessels");
    addCard(lblTotalCapacity, "Total Capacity (t)");
    addCard(lblTotalLoad,     "Total Load (t)");
    addCard(lblAvgLoad,       "Avg Load %");

    // ── Vessel table ──────────────────────────────────────────────────────────
    table = new QTableWidget(0, ColCount, this);
    table->setHorizontalHeaderLabels({"Vessel Name", "Capacity (t)", "Load (t)", "Status"});
    table->horizontalHeader()->setSectionResizeMode(ColName, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(ColCapacity, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(ColLoad,     QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(ColStatus,   QHeaderView::ResizeToContents);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(table->styleSheet() +
                         "QTableWidget { alternate-background-color: #081c34; }");

    // ── Buttons ───────────────────────────────────────────────────────────────
    addButton    = new QPushButton("➕  Add Vessel",    this);
    removeButton = new QPushButton("➖  Remove Vessel", this);
    removeButton->setObjectName("removeBtn");

    QHBoxLayout *btnRow = new QHBoxLayout;
    btnRow->addStretch();
    btnRow->addWidget(addButton);
    btnRow->addWidget(removeButton);

    // ← CHART: Build the pie chart ────────────────────────────────────────────
    //
    //  QPieSeries — one slice per vessel representing its current load.
    //  refreshChart() rebuilds the slices every time anything changes.

    chart = new QChart();
    chart->setTitle("Load Distribution by Vessel");
    chart->setTitleBrush(QBrush(QColor("#4fc3f7")));
    chart->setBackgroundBrush(QBrush(QColor("#0a2040")));
    chart->setBackgroundRoundness(10);
    chart->legend()->setLabelColor(QColor("#90caf9"));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    pieSeries = new QPieSeries();
    pieSeries->setHoleSize(0.35);   // donut style — easier to read labels
    chart->addSeries(pieSeries);

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(220);
    chartView->setStyleSheet("border: 1px solid #1a3a5c; border-radius: 8px;");
    // ← CHART end ─────────────────────────────────────────────────────────────

    // ── Main layout ───────────────────────────────────────────────────────────
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(16, 16, 16, 16);
    main->setSpacing(12);
    main->addWidget(summaryGroup);
    main->addWidget(table, 1);
    main->addWidget(chartView);     // ← CHART: chart sits below the table
    main->addLayout(btnRow);

    // ── Signals ───────────────────────────────────────────────────────────────
    connect(addButton,    &QPushButton::clicked, this, &VesselStatsDialog::onAddVessel);
    connect(removeButton, &QPushButton::clicked, this, &VesselStatsDialog::onRemoveVessel);

    // ── Seed with 3 demo vessels ──────────────────────────────────────────────
    vessels = {
        {"Al-Bahar I",   500, 320},
        {"Al-Bahar II",  750, 600},
        {"Horizon Star", 300, 50 }
    };
    vesselCounter = static_cast<int>(vessels.size());

    refreshTable();
    refreshSummary();
    // ← CHART: initial chart draw after data is ready
    refreshChart();
}

VesselStatsDialog::~VesselStatsDialog() {}

// ─────────────────────────────────────────────────────────────────────────────
//  Return a status badge string based on load percentage
// ─────────────────────────────────────────────────────────────────────────────
QString VesselStatsDialog::loadStatus(int load, int capacity) const
{
    if (capacity <= 0) return "—";
    double pct = (static_cast<double>(load) / capacity) * 100.0;
    if (pct >= 90.0) return "🔴 Critical";
    if (pct >= 70.0) return "🟡 Warning";
    return "🟢 OK";
}

// ─────────────────────────────────────────────────────────────────────────────
//  Rebuild the entire table from the vessels vector
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::refreshTable()
{
    // Block signals while rebuilding to avoid spurious slot calls
    table->blockSignals(true);
    table->setRowCount(0);

    for (int i = 0; i < vessels.size(); ++i) {
        table->insertRow(i);
        addTableRow(i);
    }

    table->blockSignals(false);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Populate one row (called during refreshTable)
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::addTableRow(int row)
{
    const VesselData &v = vessels[row];

    // Name (non-editable label cell)
    QTableWidgetItem *nameItem = new QTableWidgetItem(v.name);
    nameItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    table->setItem(row, ColName, nameItem);

    // Capacity spinbox
    QSpinBox *capSpin = new QSpinBox;
    capSpin->setRange(0, 99999);
    capSpin->setSuffix(" t");
    capSpin->setValue(v.capacity);
    capSpin->setStyleSheet("QSpinBox { border: none; background: transparent; color: #d0e8ff; }");
    table->setCellWidget(row, ColCapacity, capSpin);

    // Load spinbox
    QSpinBox *loadSpin = new QSpinBox;
    loadSpin->setRange(0, v.capacity);
    loadSpin->setSuffix(" t");
    loadSpin->setValue(v.load);
    loadSpin->setStyleSheet("QSpinBox { border: none; background: transparent; color: #d0e8ff; }");
    table->setCellWidget(row, ColLoad, loadSpin);

    // Status label
    QTableWidgetItem *statusItem = new QTableWidgetItem(loadStatus(v.load, v.capacity));
    statusItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, ColStatus, statusItem);

    // Connect spinbox signals — capture row index by value
    connect(capSpin, &QSpinBox::valueChanged, this, [this, row](int val) {
        onCapacityChanged(row, val);
    });
    connect(loadSpin, &QSpinBox::valueChanged, this, [this, row](int val) {
        onLoadChanged(row, val);
    });
}

// ─────────────────────────────────────────────────────────────────────────────
//  Update summary cards from aggregated vessel data
//  Also triggers a chart refresh so everything stays in sync.
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::refreshSummary()
{
    int totalCap  = 0;
    int totalLoad = 0;

    for (const VesselData &v : vessels) {
        totalCap  += v.capacity;
        totalLoad += v.load;
    }

    double avg = (totalCap > 0)
                     ? (static_cast<double>(totalLoad) / totalCap) * 100.0
                     : 0.0;

    lblVesselCount->setText(QString::number(vessels.size()));
    lblTotalCapacity->setText(QString("%1 t").arg(totalCap));
    lblTotalLoad->setText(QString("%1 t").arg(totalLoad));
    lblAvgLoad->setText(QString("%1 %").arg(avg, 0, 'f', 1));

    // Colour-code average load label
    QString colour = (avg >= 90.0) ? "#ef5350"
                     : (avg >= 70.0) ? "#ffa726"
                                     : "#66bb6a";
    lblAvgLoad->setStyleSheet(
        QString("QLabel { background: #0a2040; border: 1px solid #1a3a5c;"
                "         border-radius: 8px; padding: 10px 18px;"
                "         color: %1; font-size: 16px; font-weight: bold;"
                "         min-width: 120px; }").arg(colour));

    // ← CHART: keep the chart in sync with every summary refresh
    refreshChart();
}

// ─────────────────────────────────────────────────────────────────────────────
//  ← CHART: refreshChart() — rebuild pie chart from the vessels vector
//
//  Each slice represents one vessel's current load (in tons).
//  A vessel with load = 0 gets a tiny ghost slice so it stays visible
//  in the legend.
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::refreshChart()
{
    // ── 1. Clear all existing slices ──────────────────────────────────────────
    pieSeries->clear();

    // ── 2. Colour palette — cycles if there are more than 6 vessels ───────────
    static const QColor palette[] = {
        QColor("#0288d1"), QColor("#0097a7"), QColor("#00838f"),
        QColor("#1565c0"), QColor("#283593"), QColor("#4527a0")
    };
    constexpr int paletteSize = static_cast<int>(sizeof(palette) / sizeof(palette[0]));

    // ── 3. Add one slice per vessel ───────────────────────────────────────────
    for (int i = 0; i < vessels.size(); ++i) {
        const VesselData &v = vessels[i];

        // Use actual load; fall back to a tiny value so the slice is visible
        double value = (v.load > 0) ? static_cast<double>(v.load) : 0.01;

        // Label shows vessel name + load in tons
        QString label = QString("%1 (%2 t)").arg(v.name).arg(v.load);

        QPieSlice *slice = pieSeries->append(label, value);

        // Apply colour from palette
        QColor colour = palette[i % paletteSize];
        slice->setColor(colour);
        slice->setBorderColor(colour.lighter(130));
        slice->setBorderWidth(1);
        slice->setLabelColor(QColor("#d0e8ff"));

        // Highlight the most-loaded vessel by exploding its slice
        double pct = (v.capacity > 0)
                         ? (static_cast<double>(v.load) / v.capacity) * 100.0
                         : 0.0;
        if (pct >= 90.0) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.08);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: Add a new vessel
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::onAddVessel()
{
    bool ok = false;
    QString name = QInputDialog::getText(
        this,
        "Add Vessel",
        "Vessel name:",
        QLineEdit::Normal,
        QString("Vessel %1").arg(++vesselCounter),
        &ok
        );

    if (!ok || name.trimmed().isEmpty()) {
        --vesselCounter;    // roll back counter if cancelled
        return;
    }

    VesselData v;
    v.name     = name.trimmed();
    v.capacity = 500;   // sensible default
    v.load     = 0;
    vessels.append(v);

    int row = vessels.size() - 1;
    table->insertRow(row);
    addTableRow(row);
    refreshSummary();   // ← triggers refreshChart() automatically

    table->scrollToBottom();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: Remove the selected vessel
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::onRemoveVessel()
{
    if (vessels.isEmpty()) return;

    int row = table->currentRow();
    if (row < 0) row = vessels.size() - 1;   // if nothing selected, remove last

    vessels.removeAt(row);
    table->removeRow(row);
    refreshSummary();   // ← triggers refreshChart() automatically
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: Capacity spinbox changed for row
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::onCapacityChanged(int row, int value)
{
    if (row < 0 || row >= vessels.size()) return;

    vessels[row].capacity = value;

    // Keep load spinbox max in sync
    QSpinBox *loadSpin = qobject_cast<QSpinBox*>(table->cellWidget(row, ColLoad));
    if (loadSpin) loadSpin->setMaximum(value);

    // Refresh status cell
    int load = vessels[row].load;
    if (QTableWidgetItem *item = table->item(row, ColStatus))
        item->setText(loadStatus(load, value));

    refreshSummary();   // ← triggers refreshChart() automatically
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: Load spinbox changed for row
// ─────────────────────────────────────────────────────────────────────────────
void VesselStatsDialog::onLoadChanged(int row, int value)
{
    if (row < 0 || row >= vessels.size()) return;

    vessels[row].load = value;

    // Refresh status cell
    int cap = vessels[row].capacity;
    if (QTableWidgetItem *item = table->item(row, ColStatus))
        item->setText(loadStatus(value, cap));

    refreshSummary();   // ← triggers refreshChart() automatically
}
