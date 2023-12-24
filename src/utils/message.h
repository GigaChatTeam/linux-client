#pragma once

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "stylesheets.h"

namespace GC {

enum MsgAlign {sent, received};

class Message : public QFrame
{
    Q_OBJECT

    static inline const QIcon
        unconfirmed = QIcon(":/icons_builtin/unread_mark.png"),
        confirmed = QIcon("/icons_builtin/read_mark.png");

    QLabel *sender, *message;
    QHBoxLayout *layout;
    std::unique_ptr<QVBoxLayout> sender_message;
    QIcon *senderPFP,
          *readStatus;

    MsgAlign alignment;

public:
    explicit Message(QString &_sender,
                     QString &_message,
                     bool showAuthor,
                     MsgAlign status,
                     QWidget *parent);

    void makeUnsent();
    void makeSent();

    bool is_confirmed;

};

} // namespace GC

