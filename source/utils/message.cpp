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
    sender = QLabel(_sender);
    message = QLabel(_message);
    message.setWordWrap(false);
    sender_message = QVBoxLayout();
    sender_message.addWidget(&sender, 1);
    sender_message.addWidget(&message, 2);
    layout.addSpacing(1);
    layout.addLayout(&sender_message, 4)

}

} // namespace GC
