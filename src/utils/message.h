#pragma once

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "stylesheets.h"

namespace GC {

enum MsgAlign
{
    sent, received
};

class Message : public QFrame
{
    Q_OBJECT

    QLabel *sender, *message;
    QHBoxLayout *layout;
    QVBoxLayout *sender_message;
    QIcon *senderPFP;

    MsgAlign alignment;

public:
    explicit Message(const QString& _sender,
                     const QString& _message,
                     MsgAlign status,
                     QWidget *parent = nullptr);

signals:

};

} // namespace GC

