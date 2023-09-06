#include "messanger.h"

void ScrollingWidget::setupUI()
{
    shownMessages = new QWidget();
    shownMessagesLayout = new QVBoxLayout(shownMessages);
    shownMessagesLayout->setAlignment(Qt::AlignTop);
#ifdef QT_DEBUG
    for(int i = 0; i < 20; ++i)
        shownMessagesLayout->addWidget(new QPushButton("lol"));
#endif
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
    connect(inputLine, SIGNAL(enterPressed()), this, SLOT(sendMessage()));
    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendMessage()));
}

ScrollingWidget::ScrollingWidget()
    : QWidget()
{
    serverConnection = new QWebSocket();
    setupUI();
    setupLayout();
    setupConnections();

    serverConnection->open(QUrl("wss://socketsbay.com/wss/v2/1/demo/GigaChat"));
}

QString ScrollingWidget::serializeMessage(const QString &messageText)
{

}

QJsonObject ScrollingWidget::deserializeMessage(const QString &messageText)
{
    QJsonObject ret;

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
    addMessage(message, "anon");
}

void ScrollingWidget::addMessage(const QString& text, const QString& sender)
{
    shownMessagesLayout->addWidget(new QLabel(sender +'\n' + text));
}

void ScrollingWidget::sendMessage()
{
    QString text = inputLine->text();
    inputLine->setText("");
    serverConnection->sendTextMessage(text);
    addMessage(text, tr("you"));
}

