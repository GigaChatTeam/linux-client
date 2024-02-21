#include "ui/mainwidgets/messanger.hpp"

void ScrollingWidget::setupUI()
{
	shownMessages	    = new QWidget();
	shownMessagesLayout = new QVBoxLayout(shownMessages);
	shownMessagesLayout->setAlignment(Qt::AlignTop);

	shownMessagesScroller = new QScrollArea(this);

	shownMessagesScroller->setWidgetResizable(true);
	shownMessagesScroller->setWidget(shownMessages);
	shownMessagesScroller->setVerticalScrollBarPolicy(
	    Qt::ScrollBarAlwaysOn);
	shownMessagesScroller->setHorizontalScrollBarPolicy(
	    Qt::ScrollBarAlwaysOff);

	inputLine  = new NoNewLineQLineEdit(tr("Message"), this);
	sendButton = new QPushButton(tr("send"), this);
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
	connect(serverConnection,
		SIGNAL(textMessageReceived(QString)),
		this,
		SLOT(receiveTextMessage(QString)));
	connect(serverConnection,
		SIGNAL(aboutToClose()),
		this,
		SLOT(errorOccured())); // TODO: DELETE
	connect(serverConnection, &QWebSocket::connected, this, [&]() {
		qDebug() << "\x1b[1;91mQWEBSOCKER CONNECTED\x1b[0m";
		DEBUG(__PRETTY_FUNCTION__ << serverConnection->resourceName());
	});
	connect(
	    inputLine, SIGNAL(enterPressed()), this, SLOT(sendTextMessage()));
	connect(sendButton, SIGNAL(pressed()), this, SLOT(sendTextMessage()));
}

ScrollingWidget::ScrollingWidget(QWidget *parent) : QWidget{parent}
{
	serverConnection = new QWebSocket();
	serverConnection->setParent(this);
	setupUI();
	setupLayout();
	setupConnections();

	lastAddedGroup = new GC::MessageGroup(this, 0, GC::sent, nullptr);

	DEBUG("\x1b[31m" << SERVERS.cdnServer << "\x1b[0m");
}

ScrollingWidget::~ScrollingWidget()
{
	DEBUG(__PRETTY_FUNCTION__ << "\x1b[1;91mDESTRUCTOR CALLED\x1b[0m");
	delete serverConnection;
}

void ScrollingWidget::addMessage(QString     &text,
				 qint64	      _sender,
				 GC::MsgAlign align)
{
	QString sender = _sender >= 0 ? QString::number(_sender) : "\x1b";
	// TODO: IMPLEMENT SENDER NAME LOOKUP (HLB)

	GC::Message *currentMessage = new GC::Message(
	    sender,
	    text,
	    _sender != lastAddedGroup->author || _sender < 0,
	    align,
	    lastAddedGroup // the ownership is transferred anyways so i think i
			   // should pass a nullptr instead...
	);

	if (_sender == lastAddedGroup->author) {
		lastAddedGroup->addMessage(currentMessage);
		DEBUG("addding message to prev group");
		return;
	}

	GC::MessageGroup *currentGroup =
	    new GC::MessageGroup(this, _sender, align, currentMessage);

	shownMessagesLayout->addWidget(currentGroup);
	lastAddedGroup	     = currentGroup;
	QScrollBar *position = shownMessagesScroller->verticalScrollBar();

	DEBUG(position->maximum() << position->value());
	position->setSliderPosition(position->maximum());
	DEBUG(position->maximum() << position->value());
}
void ScrollingWidget::errorOccured()
{
	DEBUG(__PRETTY_FUNCTION__);
	qInfo() << "\x1b[36;41m THE SOCKET IS ABOUT TO CLOSE \x1b[0m";
}

void ScrollingWidget::receiveTextMessage(QString message)
{
	std::optional<QJsonObject> msgContents = deserializeMessage(message);

	// more monadic operations, let's go
	QString contents =
	    msgContents
		.and_then(
		    [](const QJsonObject &contained) -> std::optional<QString> {
			    return getJsonSafe<QString>("text", contained);
		    })
		.value_or("\x1b");
	qint64 author =
	    msgContents
		.and_then(
		    [](const QJsonObject &contained) -> std::optional<qint64> {
			    return getJsonSafe<qint64>("author", contained);
		    })
		.value_or(-1);

	addMessage(contents, author, GC::received);
}
void ScrollingWidget::sendTextMessage()
{
	QString text = inputLine->text();
	inputLine->setText("");
	if (text.isEmpty() || inputLine->isDefault) text = " ";
	serverConnection->sendTextMessage(serializeMessage(text));
	addMessage(text, USER_PROPERTIES.userID, GC::sent);
}

QString ScrollingWidget::serializeMessage(
    const QString &messageText /*MessageType::MessageType type*/)
{
	QJsonObject json;
	QString	    control_hash, message_type;

	json["type"]	= "TEXT";
	json["text"]	= messageText;
	json["channel"] = 5; // TODO!!!
	// json["author"] = USER_PROPERTIES.userID;

	control_hash = getDateF();
	message_type = MessageType::toString(
	    MessageType::USER_CHANNELS_MESSAGES_POST_NEW); // TODO: IMPLEMENT

	package ret{.command_type = message_type,
		    .control_hash = control_hash.toUtf8(),
		    .message_data =
			QJsonDocument(json).toJson(QJsonDocument::Compact)};
	QString serialized;

	packageToString(ret, serialized);
	DEBUG(serialized);
	return serialized;
}
std::optional<QJsonObject>
ScrollingWidget::deserializeMessage(const QString &messageText)
{
	std::optional<package> received = std::nullopt;
	stringToPackage(messageText, received);

	if (!received.has_value()) return std::nullopt;

	QJsonObject ret =
	    QJsonDocument::fromJson(received->message_data.toUtf8()).object();
	return std::make_optional(ret);
}

void ScrollingWidget::stringToPackage(const QString	     &s,
				      std::optional<package> &p)
{
	DEBUG(__PRETTY_FUNCTION__);
	qint64 percent_1, percent_2;
	quint8 count = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] != '%') continue;

		count++;
		switch (count) {
		case 1:
			percent_1 = i;
			break;
		case 2:
			percent_2 = i;
			Q_FALLTHROUGH();
		default:
			goto for_break; // falling through to this
		}
	}
for_break:

	if (count != 2 || percent_2 < percent_1 || percent_2 >= s.size() ||
	    percent_1 < 0) {
		p = std::nullopt;
		return;
	}
	p = std::make_optional(package{
	    .command_type = s.sliced(0, percent_1),
	    .control_hash =
		s.sliced(percent_1 + 1, percent_2 - percent_1 - 1).toUtf8(),
	    .message_data = s.sliced(percent_2 + 1)});
}
void ScrollingWidget::packageToString(const package &p, QString &s)
{
	s = QString("%1%%2%%3")
		.arg(p.command_type, p.control_hash, p.message_data);
}
