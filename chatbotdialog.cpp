#include "chatbotdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
ChatBotDialog::ChatBotDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("ChatBot — Port Assistant (Offline)");
    resize(500, 580);
    setStyleSheet(
        "QDialog          { background-color: #071a2c; }"
        "QTextEdit         { background: #061426; border: 1px solid #1a3a5c;"
        "                    border-radius: 8px; color: #d0e8ff;"
        "                    font-size: 13px; padding: 8px; }"
        "QLineEdit         { background: #081c34; border: 1px solid #1e4976;"
        "                    border-radius: 8px; padding: 7px 12px;"
        "                    font-size: 13px; color: #d0e8ff; min-height: 36px; }"
        "QLineEdit:focus   { border-color: #29b6f6; }"
        "QPushButton       { background: #1565c0; color: white;"
        "                    border: 1px solid #1e88e5; border-radius: 8px;"
        "                    padding: 8px 20px; font-weight: bold; }"
        "QPushButton:hover { background: #1976d2; }"
        );

    // ── Widgets ───────────────────────────────────────────────────────────────
    chatHistory = new QTextEdit(this);
    chatHistory->setReadOnly(true);

    userInput = new QLineEdit(this);
    userInput->setPlaceholderText("Type your message and press Enter…");

    sendButton = new QPushButton("Send", this);

    // ── Layouts ───────────────────────────────────────────────────────────────
    QHBoxLayout *inputRow = new QHBoxLayout;
    inputRow->addWidget(userInput, 1);
    inputRow->addWidget(sendButton);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(12, 12, 12, 12);
    main->setSpacing(8);
    main->addWidget(chatHistory, 1);
    main->addLayout(inputRow);

    // ── Signals / Slots ───────────────────────────────────────────────────────
    connect(sendButton, &QPushButton::clicked,      this, &ChatBotDialog::onSendClicked);
    connect(userInput,  &QLineEdit::returnPressed,  this, &ChatBotDialog::onSendClicked);

    // ── Rule engine ───────────────────────────────────────────────────────────
    buildRules();

    // ── Welcome message ───────────────────────────────────────────────────────
    appendBot("Hello! I am your offline port assistant. "
              "Ask me about equipment, vessels, maintenance, weather, or staff.");
}

ChatBotDialog::~ChatBotDialog() {}

// ─────────────────────────────────────────────────────────────────────────────
//  Build keyword → reply map
//  Keys are lowercase; matching is done with contains() so partial words work.
// ─────────────────────────────────────────────────────────────────────────────
void ChatBotDialog::buildRules()
{
    // Greetings
    rules["hello"]    = "Hello! How can I assist you with port operations today?";
    rules["hi"]       = "Hi there! Ready to help with your port management needs.";
    rules["bonjour"]  = "Bonjour ! Comment puis-je vous aider avec la gestion du port ?";
    rules["salut"]    = "Salut ! Posez-moi vos questions sur le port.";
    rules["hey"]      = "Hey! What can I do for you?";

    // Equipment
    rules["equipment"]   = "Equipment states are: Good, Maintenance, or Broken. "
                         "Use the Equipment module to add, edit, or remove items.";
    rules["crane"]       = "Cranes are heavy lifting equipment. Ensure regular maintenance "
                     "checks every 30 days to keep state 'Good'.";
    rules["hydraulic"]   = "Hydraulic systems require fluid level checks weekly. "
                         "Report leaks immediately.";
    rules["vehicle"]     = "Port vehicles must be inspected before each shift. "
                       "Log mileage in the equipment log.";
    rules["maintenance"] = "Maintenance schedule: cranes every 30 days, "
                           "hydraulics every 7 days, vehicles daily. "
                           "Use the Prediction module for AI-assisted scheduling.";
    rules["broken"]      = "A 'Broken' equipment status requires immediate action. "
                      "Take the unit offline and notify the maintenance team.";

    // Vessels
    rules["vessel"]   = "Vessel management lets you track capacity, load, and docking status. "
                      "Use the Dashboard to add or remove vessels.";
    rules["ship"]     = "Ship data includes name, capacity, and current load. "
                    "Visit the Vessels Dashboard for live counts.";
    rules["boat"]     = "All boats must be registered with their capacity before docking.";
    rules["dock"]     = "Docking assignments are managed in the Vessels Dashboard. "
                    "Ensure capacity is not exceeded.";
    rules["capacity"] = "Vessel capacity is tracked in tons. "
                        "Alerts trigger when load exceeds 90% of capacity.";

    // Fishing / Operations
    rules["fish"]   = "Fish stock levels are updated in the Stock module. "
                    "Contact the zone supervisor for fishing zone assignments.";
    rules["zone"]   = "Fishing zones are assigned by the port authority. "
                    "Check the Zones module for current availability.";
    rules["stock"]  = "Stock management tracks fish inventory by species and weight. "
                     "Use the Stock module to update quantities.";
    rules["load"]   = "Load tracking ensures vessels don't exceed safe capacity. "
                    "The Dashboard displays real-time load per vessel.";

    // Staff / Clients
    rules["staff"]   = "Staff records are managed in the Personnel module. "
                     "Each crew member must have a valid certification on file.";
    rules["crew"]    = "Crew assignments are linked to vessel records. "
                    "Minimum crew per vessel is set by maritime regulations.";
    rules["client"]  = "Client accounts track orders, contracts, and delivery schedules. "
                      "See the Clients module for details.";
    rules["contact"] = "To contact support, reach the port supervisor at the control room.";

    // Weather / Prediction
    rules["weather"]    = "Weather prediction is available in the Prediction module. "
                       "It uses AI to forecast conditions affecting port operations.";
    rules["prediction"] = "The Prediction module uses the Claude AI API to analyse equipment "
                          "trends and forecast maintenance needs or weather impact.";
    rules["forecast"]   = "Open the Prediction module and enter current conditions "
                        "to receive an AI-generated operational forecast.";

    // System / App
    rules["help"]   = "I can answer questions about: equipment, vessels, maintenance, "
                    "weather, staff, clients, fishing zones, and stock. Just ask!";
    rules["logout"] = "To logout, close the main window or use the File menu.";
    rules["bort"]   = "BORT is your Smart Fishing Port Management System. "
                    "It covers equipment, vessels, staff, clients, stock, and fishing zones.";
    rules["database"] = "The system connects to an Oracle XE database via ODBC. "
                        "Ensure the Oracle service is running before launching.";

    // Farewells
    rules["bye"]       = "Goodbye! Have a safe shift.";
    rules["goodbye"]   = "Goodbye! Stay safe at sea.";
    rules["merci"]     = "De rien ! N'hésitez pas si vous avez d'autres questions.";
    rules["thank"]     = "You're welcome! Anything else I can help with?";
}

// ─────────────────────────────────────────────────────────────────────────────
//  Match user input to a rule; return default if nothing matches
// ─────────────────────────────────────────────────────────────────────────────
QString ChatBotDialog::getBotReply(const QString &msg) const
{
    QString lower = msg.toLower().trimmed();

    // Iterate rules in insertion order — first match wins
    for (auto it = rules.constBegin(); it != rules.constEnd(); ++it) {
        if (lower.contains(it.key())) {
            return it.value();
        }
    }

    return "I didn't understand that. Try asking about equipment, vessels, "
           "maintenance, weather, staff, or type \"help\" for a topic list.";
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slot: user pressed Send or Enter
// ─────────────────────────────────────────────────────────────────────────────
void ChatBotDialog::onSendClicked()
{
    QString msg = userInput->text().trimmed();
    if (msg.isEmpty()) return;

    appendUser(msg);
    userInput->clear();

    QString reply = getBotReply(msg);
    appendBot(reply);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Append helpers — keep HTML formatting centralised here
// ─────────────────────────────────────────────────────────────────────────────
void ChatBotDialog::appendUser(const QString &text)
{
    chatHistory->append(
        "<p><span style='color:#90caf9; font-weight:bold;'>You:</span> "
        + text.toHtmlEscaped() + "</p>"
        );
}

void ChatBotDialog::appendBot(const QString &text)
{
    chatHistory->append(
        "<p><span style='color:#4fc3f7; font-weight:bold;'>Assistant:</span> "
        + text.toHtmlEscaped() + "</p>"
        );
}
