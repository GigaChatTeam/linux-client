#include "messanger.h"

void ScrollingWidget::setupUI()
{
    shownMessages = new QWidget();
    shownMessagesLayout = new QVBoxLayout(shownMessages);
    shownMessagesLayout->setAlignment(Qt::AlignTop);

    shownMessagesScroller = new QScrollArea();

    shownMessagesScroller->setWidgetResizable(true);
    shownMessagesScroller->setWidget(shownMessages);
    shownMessagesScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    shownMessagesScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    inputLine = new NoNewLineQLineEdit(tr("Message"));
    sendButton= new QPushButton(tr("send"));
}
void ScrollingWidget::setupLayout()
{
    auto topLayout = new QVBoxLayout(this);
    auto subLayout = new QHBoxLayout();

    subLayout->addWidget(inputLine, 9);
    subLayout->addWidget(sendButton, 1);
    topLayout->addWidget(shownMessagesScroller, 9);
    topLayout->addLayout(subLayout, 1);
}
void ScrollingWidget::setupConnections()
{
    connect(serverConnection, SIGNAL(textMessageReceived(QString)), this, SLOT(receiveTextMessage(QString)));
    connect(serverConnection, SIGNAL(disconnected()), this, SLOT(errorOccured()));
    connect(inputLine, SIGNAL(enterPressed()), this, SLOT(sendTextMessage()));
    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendTextMessage()));
}

ScrollingWidget::ScrollingWidget()
    : QWidget()
{
    serverConnection = new QWebSocket();
    setupUI();
    setupLayout();
    setupConnections();

    DEBUG("\e[31m" << SERVERS.cdnServer << "\e[0m");

    serverConnection->open(QUrl(SERVERS.cdnServer + "/?"));
}

QString ScrollingWidget::serializeMessage(const QString &messageText)
{
    QJsonObject ret;
    ret["text"] = messageText;
    ret["type"] = "MESSAGE-POST";
    ret["channel"] = -1;
    ret["user"] = -2;

    return QJsonDocument(ret).toJson(QJsonDocument::Compact);
}
QJsonObject ScrollingWidget::deserializeMessage(const QString &messageText)
{
    QJsonObject ret= QJsonDocument::fromJson(messageText.toUtf8()).object();
    return ret;
}

void ScrollingWidget::addMessage(const QString& text, const QString& sender, GC::MsgAlign align)
{
    GC::Message* temp = new GC::Message(sender, text, align);
    shownMessagesLayout->addWidget(temp);
    QScrollBar* position = shownMessagesScroller->verticalScrollBar();
    position->setSliderPosition(position->maximum());
    DEBUG(temp);
}

void ScrollingWidget::errorOccured()
{
    DEBUG("ERROR OCCURED");

}
void ScrollingWidget::receiveTextMessage(QString message)
{
    DEBUG(message);
    QJsonObject msgContents = deserializeMessage(message);
    addMessage(msgContents["text"].toString(), "anon", GC::received);
}
void ScrollingWidget::sendTextMessage()
{
    QString text = inputLine->text();
    inputLine->setText("");
    serverConnection->sendTextMessage(serializeMessage(text));
    addMessage(text, tr("you"), GC::sent);
}

