#ifndef CHATBOTDIALOG_H
#define CHATBOTDIALOG_H

/*
 * ChatBotDialog — Offline Rule-Based Chatbot
 * ─────────────────────────────────────────────────────────────────────────────
 * No network calls. Responds instantly using keyword-based rules.
 * Fully self-contained; no QNetworkAccessManager needed.
 */

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>

class ChatBotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatBotDialog(QWidget *parent = nullptr);
    ~ChatBotDialog() override;

private slots:
    void onSendClicked();

private:
    // ── UI widgets ────────────────────────────────────────────────────────────
    QTextEdit   *chatHistory;
    QLineEdit   *userInput;
    QPushButton *sendButton;

    // ── Rule engine ──────────────────────────────────────────────────────────
    QMap<QString, QString> rules;   // keyword → reply
    void   buildRules();
    QString getBotReply(const QString &msg) const;

    // ── Helpers ───────────────────────────────────────────────────────────────
    void appendBot (const QString &text);
    void appendUser(const QString &text);
};

#endif // CHATBOTDIALOG_H
