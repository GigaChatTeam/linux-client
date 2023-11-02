#include "message.h"

namespace GC {

Message::Message(QString _sender,
                 QString _message,
                 MsgAlign status,
                 QWidget *parent)
    : QFrame(parent), alignment{status}, confirmed{false}
{
    layout = new QHBoxLayout(this);
    sender = new QLabel();
    message = new QLabel();
    message->setWordWrap(false);

    if (_sender.at(0) == '\e'){
        _sender = "Could not resolve author";
        sender->setStyleSheet(StyleSheets::MessageErrorSS);
    }
    if (_message.at(0) == '\e'){
        _message = "Error receiving a message";
        message->setStyleSheet(StyleSheets::MessageErrorSS);
    }

    sender->setText(_sender);
    message->setText(_message);
    message->setFixedWidth(300);

    sender_message = new QVBoxLayout();
    sender_message->addWidget(sender, 1);
    sender_message->addWidget(message, 2);

    layout->addLayout(sender_message);

    Qt::Alignment alignment = Qt::AlignVCenter | (status == sent ? Qt::AlignRight : Qt::AlignLeft);
    layout->setAlignment(alignment);
    sender_message->setAlignment(alignment);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    setStyleSheet(StyleSheets::MessageSS);

}

void Message::makeUnsent()
{

}
void Message::makeSent()
{

}

} // namespace GC
