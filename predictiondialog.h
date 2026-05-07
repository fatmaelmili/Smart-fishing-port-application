#ifndef PREDICTIONDIALOG_H
#define PREDICTIONDIALOG_H

/*
 * PredictionDialog — AI-Powered Prediction via Claude API
 * ─────────────────────────────────────────────────────────────────────────────
 * Sends an equipment / operational context to the Claude API and displays
 * the AI-generated prediction in a read-only text area.
 *
 * HOW TO USE:
 *   PredictionDialog *dlg = new PredictionDialog(this);
 *   dlg->exec();
 *
 * Set your API key in predictiondialog.cpp (CLAUDE_API_KEY constant).
 */

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class PredictionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PredictionDialog(QWidget *parent = nullptr);
    ~PredictionDialog() override;

private slots:
    void onPredictClicked();
    void onReplyFinished(QNetworkReply *reply);

private:
    // ── Input widgets ─────────────────────────────────────────────────────────
    QComboBox   *equipmentTypeBox;   // crane / hydraulic / vehicle / vessel
    QComboBox   *equipmentStateBox;  // Good / Maintenance / Broken
    QSpinBox    *daysSinceService;   // 0–365 days
    QLineEdit   *additionalNotes;    // free text
    QPushButton *predictButton;

    // ── Output widgets ────────────────────────────────────────────────────────
    QTextEdit   *resultArea;
    QLabel      *statusLabel;

    // ── Network ───────────────────────────────────────────────────────────────
    QNetworkAccessManager *networkManager;

    // ── Helpers ───────────────────────────────────────────────────────────────
    void sendPredictionRequest(const QString &prompt);
    void setControlsEnabled(bool enabled);
    QString buildPrompt() const;
};

#endif // PREDICTIONDIALOG_H
