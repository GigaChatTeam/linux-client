#include "utils/message.hpp"

namespace GC
{

Message::Message(QString &_sender,
		 QString &_message,
		 bool	  showAuthor,
		 MsgAlign status,
		 QWidget *parent)
    : QFrame{parent}, alignment{status}, is_confirmed{false}
{
	layout	       = new QHBoxLayout(this);
	sender_message = std::make_unique<QVBoxLayout>();

	if (showAuthor) {
		sender = new QLabel(this);
		sender->setStyleSheet(StyleSheets::MessageSenderSS);
		if (_sender.at(0) == '\x1b') {
			_sender = "Could not resolve author";
			sender->setStyleSheet(StyleSheets::MessageErrorSS);
		}
		sender->setText(_sender);
		sender_message->addWidget(sender, 1);
	}

	message = new QLabel(this);
	message->setWordWrap(true);
	message->setStyleSheet(StyleSheets::MessageSS);
	if (_message.at(0) == '\x1b') {
		_message = "Error receiving a message";
		message->setStyleSheet(StyleSheets::MessageErrorSS);
	}
	message->setText(_message);
	message->setMinimumWidth(100);
	message->setMaximumWidth(500);

	sender_message->addWidget(message, 2);

	layout->addLayout(sender_message.get());
	Qt::Alignment alignment =
	    Qt::AlignVCenter |
	    (status == sent ? Qt::AlignRight : Qt::AlignLeft);
	layout->setAlignment(alignment);
	sender_message->setAlignment(alignment);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
}

void Message::makeUnsent() {}
void Message::makeSent() {}

} // namespace GC
