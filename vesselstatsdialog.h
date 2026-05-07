#ifndef VESSELSTATSDIALOG_H
#define VESSELSTATSDIALOG_H

/*
 * VesselStatsDialog — Interactive Vessel Fleet Manager
 * ─────────────────────────────────────────────────────────────────────────────
 * Displays and manages a list of vessels with live-updating statistics
 * AND a bar chart that visualises each vessel's load vs capacity.
 *
 * Chart additions are marked with  ← CHART  for easy identification.
 */

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVector>
#include <QString>

// ← CHART: Qt Charts headers
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

// ── Plain-old-data vessel record ──────────────────────────────────────────────
struct VesselData {
    QString name;       // vessel name
    int     capacity;   // max load in tons
    int     load;       // current load in tons
};

class VesselStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VesselStatsDialog(QWidget *parent = nullptr);
    ~VesselStatsDialog() override;

private slots:
    void onAddVessel();
    void onRemoveVessel();
    void onCapacityChanged(int row, int value);
    void onLoadChanged(int row, int value);

private:
    // ── Summary display ───────────────────────────────────────────────────────
    QLabel *lblVesselCount;
    QLabel *lblTotalCapacity;
    QLabel *lblTotalLoad;
    QLabel *lblAvgLoad;

    // ── Table and action buttons ──────────────────────────────────────────────
    QTableWidget *table;
    QPushButton  *addButton;
    QPushButton  *removeButton;

    // ── Data store ────────────────────────────────────────────────────────────
    QVector<VesselData> vessels;
    int vesselCounter = 0;   // used to auto-name new vessels

    // ← CHART: Chart widget members ───────────────────────────────────────────
    QChartView  *chartView;   // the visible widget placed in the layout
    QChart      *chart;       // the chart object (owned by chartView)
    QPieSeries  *pieSeries;   // one slice per vessel showing its load

    // ── Helpers ───────────────────────────────────────────────────────────────
    void refreshTable();
    void refreshSummary();
    void refreshChart();          // ← CHART: rebuilds chart from vessels vector
    void addTableRow(int row);
    QString loadStatus(int load, int capacity) const;
};

#endif // VESSELSTATSDIALOG_H
