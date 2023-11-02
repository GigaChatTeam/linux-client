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
    connect(serverConnection, SIGNAL(aboutToClose()), this, SLOT(errorOccured())); // TODO: DELETE
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
}

void ScrollingWidget::addMessage(const QString& text, qint64 _sender, GC::MsgAlign align)
{
    QString sender = _sender >= 0 ? QString::number(_sender): "\e";
    // TODO: IMPLEMENT SENDER NAME LOOKUP (HLB)

    GC::Message* temp = new GC::Message(sender, text, align);
    shownMessagesLayout->addWidget(temp);
    QScrollBar* position = shownMessagesScroller->verticalScrollBar();

    DEBUG(position->maximum() << position->value());
    position->setSliderPosition(position->maximum());
    DEBUG(position->maximum() << position->value());
}
void ScrollingWidget::errorOccured()
{
    DEBUG("ERROR OCCURED");
    qInfo() << "\e[36;41m ERRORS YOU MOTHERFUCKER\e[0m";
}

void ScrollingWidget::receiveTextMessage(QString message)
{
    std::optional<QJsonObject> msgContents = deserializeMessage(message);

    // more monadic operations, let's go
    QString contents = msgContents.and_then(
        [](const QJsonObject& contained) -> std::optional<QString> {
            return getJsonSafe<QString>("text", contained);
        }).value_or("\e");
    qint64 author = msgContents.and_then(
        [](const QJsonObject& contained) -> std::optional<qint64> {
            return getJsonSafe<qint64>("author", contained);
        }).value_or(-1);

    addMessage(contents, author, GC::received);
}
void ScrollingWidget::sendTextMessage()
{
    QString text = inputLine->text();
    inputLine->setText("");
    serverConnection->sendTextMessage(serializeMessage(text));
    addMessage(text, USER_PROPERTIES.userID, GC::sent);
}

QString ScrollingWidget::serializeMessage(const QString &messageText)
{
    QJsonObject json;
    QString control_hash, message_type;

    json["text"] = messageText;
    json["channel"] = -1;
    json["author"] = USER_PROPERTIES.userID;

    control_hash = "000000000000"; // TODO!!!
    message_type = "MESSAGE-POST"; // TODO!!!

    package ret {
        .command_type = message_type,
        .control_hash = control_hash.toUtf8(),
        .message_data = QJsonDocument(json).toJson(QJsonDocument::Compact)
    };
    QString serialized;

    packageToString(ret, serialized);
    DEBUG(serialized);
    return serialized;
}
std::optional<QJsonObject> ScrollingWidget::deserializeMessage(const QString &messageText)
{

    std::optional<package> received = std::nullopt;
    stringToPackage(messageText, received);

    if (!received.has_value())
        return std::nullopt;

    QJsonObject ret = QJsonDocument::fromJson(received->message_data.toUtf8()).object();
    return std::make_optional(ret);
}

void ScrollingWidget::stringToPackage(const QString &s, std::optional<package> &p)
{
    DEBUG(__PRETTY_FUNCTION__);
    qint64 percent_1, percent_2;
    quint8 count = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != '%') continue;

        count++;
        switch (count)
        {
        case 1: percent_1 = i; break;
        case 2: percent_2 = i; [[fallthrough]];
        default: goto for_break; // falling through to this
        }
    }
for_break:

    if (count != 2 || percent_2 < percent_1 || percent_2 >= s.size() || percent_1 < 0)
    {
        p = std::nullopt;
        return;
    }
    p = std::make_optional(package {
        .command_type = s.sliced(0, percent_1),
        .control_hash = s.sliced(percent_1 + 1, percent_2 - percent_1 - 1).toUtf8(),
        .message_data = s.sliced(percent_2 + 1)
    });
}
void ScrollingWidget::packageToString(const package &p, QString &s)
{
    s = QString("%1%%2%%3").arg(p.command_type, p.control_hash, p.message_data);
}


