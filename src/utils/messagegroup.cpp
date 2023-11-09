#include "messagegroup.h"

GC::MessageGroup::MessageGroup(qint64 msgAuthor, MsgAlign status, QWidget *firstMessage)
    : QWidget{}, author{msgAuthor}
{
    layout = new QVBoxLayout(this);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    align_status = Qt::AlignVCenter | (status == sent ? Qt::AlignRight : Qt::AlignLeft);
    authorLabel = new QLabel(QString::number(author)); // TODO: search author's name
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

    layout->addWidget(message);
    message->layout()->setAlignment(align_status);
    message->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    return true;
}

bool GC::MessageGroup::addTextMessage(const QString &text, qint64 msgAuthor)
{
    if (msgAuthor != -1 && author != msgAuthor)
        return false;

    // TODO: implement
    // after I remove "author" or "sender" property from message class

    return true;
}
