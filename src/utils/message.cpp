#include "message.h"

namespace GC {

Message::Message(const QString &_sender,
                 const QString &_message,
                 MsgAlign status,
                 QWidget *parent)
    : QWidget(parent), alignment{status}
{
    layout = new QHBoxLayout(this);
    layout->setAlignment(alignment == sent ? Qt::AlignLeft : Qt::AlignRight);
    sender = new QLabel(_sender);
    message = new QLabel(_message);
    message->setWordWrap(false);
    sender_message = new QVBoxLayout();
    sender_message->addWidget(sender, 1);
    sender_message->addWidget(message, 2);
    if (alignment == sent)
    {
        layout->addSpacing(1);
        layout->addLayout(sender_message, 4);
    }
    else
    {
        layout->addLayout(sender_message, 4);
        layout->addSpacing(1);
    }

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    setStyleSheet("border: 2px red;");
}

} // namespace GC
