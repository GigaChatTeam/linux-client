#include "messanger.h"

void ScrollingWidget::setupUI()
{
    shownMessages = new QWidget();
    shownMessagesLayout = new QVBoxLayout(shownMessages);
    shownMessagesLayout->setAlignment(Qt::AlignTop);
/*#ifdef QT_DEBUG
    for(int i = 0; i < 20; ++i)
        shownMessagesLayout->addWidget(new QPushButton("lol"));
#endif*/
    messageHolder = new QScrollArea();
    messageHolder->setWidget(shownMessages);
    messageHolder->setWidgetResizable(true);
    messageHolder->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    messageHolder->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    inputLine = new NoNewLineQLineEdit(tr("Message"));
    sendButton= new QPushButton(tr("send"));
}
void ScrollingWidget::setupLayout()
{
    auto topLayout = new QVBoxLayout(this);
    auto subLayout = new QHBoxLayout();

    subLayout->addWidget(inputLine, 9);
    subLayout->addWidget(sendButton, 1);
    topLayout->addWidget(messageHolder, 9);
    topLayout->addLayout(subLayout, 1);
}
void ScrollingWidget::setupConnections()
{
    connect(serverConnection, SIGNAL(textMessageReceived(QString)), this, SLOT(receiveMessage(QString)));
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

}

QJsonObject ScrollingWidget::deserializeMessage(const QString &messageText)
{
    QJsonObject ret;
    ret["text"] = messageText;
    return ret;
}

void ScrollingWidget::errorOccured()
{
    DEBUG("ERROR OCCURED");

}

void ScrollingWidget::receiveMessage(QString message)
{
    DEBUG(message);
    QJsonObject msgContents = deserializeMessage(message);
    addMessage(msgContents["text"].toString(), "anon", GC::received);
}

void ScrollingWidget::addMessage(const QString& text, const QString& sender, GC::MsgAlign align)
{
    GC::Message* temp = new GC::Message(sender, text, align);
    shownMessagesLayout->addWidget(temp);
    QScrollBar* position = messageHolder->verticalScrollBar();
    position->setSliderPosition(position->maximum());
    DEBUG(temp);
}

void ScrollingWidget::sendTextMessage()
{
    QString text = inputLine->text();
    inputLine->setText("");

    QJsonObject properties;
    properties["type"] = "MESSAGE-POST";
    properties["channel"] = -1;
    properties["user"] = -2;
    properties["text"] = text;

    QJsonDocument serializer(properties);

    serverConnection->sendTextMessage(serializer.toJson(QJsonDocument::Compact));
    addMessage(text, tr("you"), GC::sent);
}

