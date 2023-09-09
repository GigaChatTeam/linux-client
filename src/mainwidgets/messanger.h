#pragma once

#include <QObject>
#include "utils/properties.h"

#include "utils/nonewlineqlineedit.h"
#include "utils/message.h"
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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// TODO: REMOVE LATER
#ifdef QT_DEBUG
    #include <iostream>
    #define DEBUG(str) qDebug() << str
#else
    #define DEBUG(str)
#endif

class ScrollingWidget : public QWidget
{
    Q_OBJECT

    QWebSocket* serverConnection;

    QScrollArea* shownMessagesScroller;
    NoNewLineQLineEdit* inputLine;
    QPushButton* sendButton;

    QWidget* shownMessages;
    QVBoxLayout* shownMessagesLayout;

public:
    void setupUI();
    void setupLayout();
    void setupConnections();
    ScrollingWidget();
    static QString serializeMessage(const QString& messageText);
    static QJsonObject deserializeMessage(const QString& messageText);

public slots:
    void addMessage(const QString& text, const QString& sender, GC::MsgAlign align);
    void errorOccured();
    void receiveTextMessage(QString message);
    void sendTextMessage();
};

