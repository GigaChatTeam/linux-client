#include "messagegroup.h"

GC::MessageGroup::MessageGroup(QWidget* parent, qint64 msgAuthor, MsgAlign status, QWidget *firstMessage)
    : QWidget{parent}, author{msgAuthor}
{
    layout = new QVBoxLayout(this);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    align_status = Qt::AlignVCenter | (status == sent ? Qt::AlignRight : Qt::AlignLeft);
    authorLabel = new QLabel(QString::number(author), this); // TODO: search author's name
    authorLabel->setStyleSheet(StyleSheets::MessageSenderSS);
    layout->addWidget(authorLabel);
    layout->setAlignment(align_status);
    if (firstMessage != nullptr) {
        addMessage(firstMessage);
    }

}

bool GC::MessageGroup::addMessage(QWidget *message, qint64 msgAuthor)
{
    if (msgAuthor != -1 && author != msgAuthor)
        return false;

    message->setParent(this); // transfer ownership
    layout->addWidget(message);
    message->layout()->setAlignment(align_status);
    message->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    return true;
}

bool GC::MessageGroup::addTextMessage([[maybe_unused]] const QString &text, qint64 msgAuthor)
{
    if (msgAuthor != -1 && author != msgAuthor)
        return false;

    // TODO: implement
    // after I remove "author" or "sender" property from message class

    return true;
}
