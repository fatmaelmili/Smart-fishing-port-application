#include "predictiondialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QUrl>

// ─────────────────────────────────────────────────────────────────────────────
//  ⚠  Replace with your actual Anthropic API key before running.
// ─────────────────────────────────────────────────────────────────────────────
static const QString CLAUDE_API_KEY = "YOUR_ANTHROPIC_API_KEY_HERE";
static const QString CLAUDE_API_URL = "https://api.anthropic.com/v1/messages";
static const QString CLAUDE_MODEL   = "claude-sonnet-4-20250514";

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor — build UI
// ─────────────────────────────────────────────────────────────────────────────
PredictionDialog::PredictionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("AI Prediction — Port Operations");
    setMinimumWidth(540);
    setStyleSheet(
        "QDialog          { background: #071a2c; color: #d0e8ff; }"
        "QGroupBox        { border: 1px solid #1a3a5c; border-radius: 8px;"
        "                   margin-top: 10px; font-weight: bold; color: #4fc3f7; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; top: 3px; }"
        "QLabel           { color: #90caf9; }"
        "QComboBox, QSpinBox, QLineEdit {"
        "                   background: #081c34; border: 1px solid #1e4976;"
        "                   border-radius: 6px; padding: 5px 8px;"
        "                   color: #d0e8ff; min-height: 28px; }"
        "QComboBox:focus, QSpinBox:focus, QLineEdit:focus { border-color: #29b6f6; }"
        "QComboBox QAbstractItemView { background: #0a2040; color: #d0e8ff;"
        "                              selection-background-color: #1565c0; }"
        "QTextEdit         { background: #061426; border: 1px solid #1a3a5c;"
        "                    border-radius: 8px; color: #d0e8ff; font-size: 13px;"
        "                    padding: 8px; }"
        "QPushButton       { background: #1565c0; color: white;"
        "                    border: 1px solid #1e88e5; border-radius: 8px;"
        "                    padding: 9px 24px; font-weight: bold; font-size: 13px; }"
        "QPushButton:hover    { background: #1976d2; }"
        "QPushButton:disabled { background: #0d2a4a; color: #555; border-color: #333; }"
        );

    // ── Input group ───────────────────────────────────────────────────────────
    QGroupBox   *inputGroup  = new QGroupBox("Equipment / Operation Details", this);
    QFormLayout *formLayout  = new QFormLayout(inputGroup);
    formLayout->setSpacing(10);
    formLayout->setContentsMargins(12, 18, 12, 12);

    equipmentTypeBox = new QComboBox(this);
    equipmentTypeBox->addItems({"Crane", "Hydraulic System", "Vehicle",
                                "Vessel / Ship", "Generator", "Conveyor Belt",
                                "Forklift", "Other"});

    equipmentStateBox = new QComboBox(this);
    equipmentStateBox->addItems({"Good", "Maintenance", "Broken"});

    daysSinceService = new QSpinBox(this);
    daysSinceService->setRange(0, 730);
    daysSinceService->setSuffix(" days");
    daysSinceService->setValue(15);

    additionalNotes = new QLineEdit(this);
    additionalNotes->setPlaceholderText(
        "e.g. 'Unusual vibration noted', 'oil level low'…");

    formLayout->addRow("Equipment Type:",          equipmentTypeBox);
    formLayout->addRow("Current State:",           equipmentStateBox);
    formLayout->addRow("Days Since Last Service:", daysSinceService);
    formLayout->addRow("Additional Notes:",        additionalNotes);

    // ── Predict button ────────────────────────────────────────────────────────
    predictButton = new QPushButton("🔍  Run AI Prediction", this);

    // ── Status label ──────────────────────────────────────────────────────────
    statusLabel = new QLabel("Ready — fill in the details and press Run.", this);
    statusLabel->setStyleSheet("color: #607d8b; font-style: italic; font-size: 12px;");

    // ── Result group ──────────────────────────────────────────────────────────
    QGroupBox *resultGroup = new QGroupBox("AI Prediction Result", this);
    QVBoxLayout *resultBox = new QVBoxLayout(resultGroup);
    resultBox->setContentsMargins(10, 18, 10, 10);

    resultArea = new QTextEdit(this);
    resultArea->setReadOnly(true);
    resultArea->setMinimumHeight(200);
    resultArea->setPlaceholderText("The AI prediction will appear here…");
    resultBox->addWidget(resultArea);

    // ── Main layout ───────────────────────────────────────────────────────────
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(predictButton, 0, Qt::AlignRight);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(resultGroup, 1);

    // ── Network manager ───────────────────────────────────────────────────────
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &PredictionDialog::onReplyFinished);

    // ── Predict button signal ─────────────────────────────────────────────────
    connect(predictButton, &QPushButton::clicked,
            this, &PredictionDialog::onPredictClicked);
}

PredictionDialog::~PredictionDialog() {}

// ─────────────────────────────────────────────────────────────────────────────
//  Build a structured prompt from the form values
// ─────────────────────────────────────────────────────────────────────────────
QString PredictionDialog::buildPrompt() const
{
    return QString(
               "You are an expert maintenance advisor for a smart fishing port management system.\n\n"
               "Analyse the following equipment data and provide:\n"
               "1. A risk assessment (Low / Medium / High)\n"
               "2. Predicted time until next required maintenance\n"
               "3. Specific recommended actions (bullet points)\n"
               "4. Any safety warnings if applicable\n\n"
               "Equipment Data:\n"
               "- Type:                 %1\n"
               "- Current State:        %2\n"
               "- Days Since Service:   %3\n"
               "- Operator Notes:       %4\n\n"
               "Be concise, practical, and professional. "
               "Use plain text formatting (no markdown)."
               )
        .arg(equipmentTypeBox->currentText())
        .arg(equipmentStateBox->currentText())
        .arg(daysSinceService->value())
        .arg(additionalNotes->text().trimmed().isEmpty()
                 ? "None provided"
                 : additionalNotes->text().trimmed());
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: Predict button clicked
// ─────────────────────────────────────────────────────────────────────────────
void PredictionDialog::onPredictClicked()
{
    // ── Check for placeholder API key ─────────────────────────────────────────
    if (CLAUDE_API_KEY == "YOUR_ANTHROPIC_API_KEY_HERE") {
        statusLabel->setText("ℹ️ Demo Mode: Placeholder API key detected.");
        statusLabel->setStyleSheet("color: #ffa726; font-style: italic;");

        resultArea->setPlainText(
            "AI PREDICTION (DEMO MODE)\n"
            "────────────────────────────────────────────────\n"
            "Risk Assessment: Medium\n\n"
            "Predicted Maintenance: 15-20 days\n\n"
            "Recommended Actions:\n"
            "• Schedule a routine inspection of " + equipmentTypeBox->currentText() + " units.\n"
                                                "• Verify lubricant levels and pressure seals.\n"
                                                "• Compare current vibration levels with baseline data.\n"
                                                "\nNote: To receive real AI predictions, please set a valid \n"
                                                "Anthropic API key in predictiondialog.cpp."
            );
        return;
    }

    setControlsEnabled(false);
    statusLabel->setText("⏳ Connecting to Claude AI (Anthropic API)…");
    statusLabel->setStyleSheet("color: #4fc3f7; font-style: italic;");
    resultArea->clear();

    sendPredictionRequest(buildPrompt());
}

// ─────────────────────────────────────────────────────────────────────────────
//  Build and fire the HTTP POST to the Claude API
// ─────────────────────────────────────────────────────────────────────────────
void PredictionDialog::sendPredictionRequest(const QString &prompt)
{
    // Build messages array (single-turn — no history needed for predictions)
    QJsonObject userMessage;
    userMessage["role"]    = "user";
    userMessage["content"] = prompt;

    QJsonArray messages;
    messages.append(userMessage);

    // Build request body
    QJsonObject body;
    body["model"]      = CLAUDE_MODEL;
    body["max_tokens"] = 1024;
    body["system"]     = "You are an expert maintenance and operations advisor for "
                     "a smart fishing port management system called BORT. "
                     "Provide structured, actionable predictions and recommendations.";
    body["messages"]   = messages;

    QByteArray payload = QJsonDocument(body).toJson();

    // Build and configure the network request
    QUrl url(CLAUDE_API_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("x-api-key",         CLAUDE_API_KEY.toUtf8());
    request.setRawHeader("anthropic-version", "2023-06-01");

    networkManager->post(request, payload);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: API response received
// ─────────────────────────────────────────────────────────────────────────────
void PredictionDialog::onReplyFinished(QNetworkReply *reply)
{
    QString resultText;

    if (reply->error() != QNetworkReply::NoError) {
        resultText    = "⚠️ Network error: " + reply->errorString();
        statusLabel->setText("❌ Request failed.");
        statusLabel->setStyleSheet("color: #ef9a9a; font-style: italic;");
    } else {
        QByteArray    raw     = reply->readAll();
        QJsonDocument doc     = QJsonDocument::fromJson(raw);
        QJsonObject   obj     = doc.object();

        if (obj.contains("content")) {
            QJsonArray arr = obj["content"].toArray();
            if (!arr.isEmpty()) {
                resultText = arr[0].toObject()["text"].toString();
            }
        } else if (obj.contains("error")) {
            resultText = "⚠️ API error: " +
                         obj["error"].toObject()["message"].toString();
        } else {
            resultText = "⚠️ Unexpected response from server.";
        }

        if (!resultText.startsWith("⚠️")) {
            statusLabel->setText("✅ Prediction received successfully.");
            statusLabel->setStyleSheet("color: #a5d6a7; font-style: italic;");
        } else {
            statusLabel->setText("❌ API returned an error.");
            statusLabel->setStyleSheet("color: #ef9a9a; font-style: italic;");
        }
    }

    resultArea->setPlainText(resultText);
    setControlsEnabled(true);
    reply->deleteLater();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Enable / disable controls while the request is in flight
// ─────────────────────────────────────────────────────────────────────────────
void PredictionDialog::setControlsEnabled(bool enabled)
{
    predictButton->setEnabled(enabled);
    equipmentTypeBox->setEnabled(enabled);
    equipmentStateBox->setEnabled(enabled);
    daysSinceService->setEnabled(enabled);
    additionalNotes->setEnabled(enabled);
}
