#pragma once

#include <QObject>
#include "utils/properties.h"

#include "utils/nonewlineqlineedit.h"
#include "utils/message.h"
#include "utils/concepts_templates.h"
#include "utils/misc_functions.h"
#include "utils/messagegroup.h"
#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QPushButton>
#include <QScrollBar>
#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QWebSocket>
#include <QUrl>

#include <QList>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QtCompilerDetection>

#include <optional>
#include <utility>

// TODO: REMOVE LATER
#ifdef QT_DEBUG
    #include <iostream>
    #define DEBUG(str) qDebug() << str
#else
    #define DEBUG(str)
#endif

struct package {
    QString command_type;
    QByteArray control_hash;
    QString message_data;
};

class ScrollingWidget : public QWidget
{

    /* IMPORTANT NOTE
     * How are messages going to be displayed, stored, sorted and written to drive?
     *
     * -> messages are going to be stored in SQLite database (probably)
     * -> on startup: load 1 message from each chat (maybe)
     * -> upon entering chat: load N messages (default 128) from database
     * -> store pointers to Message objects (widgets) in one hash map, common for every chat
     * -> for each chat, construct a widget and a layout, use QStackedLayout or come up
     *      with a system for this yourself
     * -> when tabbing in/out of chat, just switch chat widget
     * -> when Websocket receives a message and the author is you, it must loop up the
     *      message pointer in hash map, set and indicator for delivered/error (like an icon of sorts)
     * -> sending a message immediately writes it to database, so as receiving does
     * -> control hash is NOT stored for received messages, so they
     */

    Q_OBJECT

    QScrollArea* shownMessagesScroller;
    NoNewLineQLineEdit* inputLine;
    QPushButton* sendButton;

    QWidget* shownMessages;
    QVBoxLayout* shownMessagesLayout;

public:
    QWebSocket* serverConnection;
    QHash<QString, GC::Message*> messagesDB; // TODO: store pointers to messages through control hash
    GC::MessageGroup* lastAddedGroup;

    void setupUI();
    void setupLayout();
    void setupConnections();
    explicit ScrollingWidget(QWidget* parent);
    ~ScrollingWidget();

public slots:
    void addMessage(QString &text, qint64 _sender, GC::MsgAlign align);
    void errorOccured();

    void receiveTextMessage(QString message);
    void sendTextMessage();

public:
    static QString serializeMessage(const QString& messageText);
    static std::optional<QJsonObject> deserializeMessage(const QString& messageText);

    static void packageToString(const package &p, QString &s);
    static void stringToPackage(const QString &s, std::optional<package> &p);

};

