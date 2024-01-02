#ifndef MESSAGEGROUP_H
#define MESSAGEGROUP_H

#include <QLabel>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include "stylesheets.h"
#include "utils/message.h"

namespace GC
{

// TODO: add reply logic (through some polymorphic method I suppose)
// TODO: add proper todo

class MessageGroup : public QWidget
{
	Q_OBJECT

private:
	QVBoxLayout *layout;

public:
	qint64	      author;
	QLabel	     *authorLabel;
	Qt::Alignment align_status;

	explicit MessageGroup(QWidget *parent,
			      qint64   msgAuthor,
			      MsgAlign status,
			      QWidget *firstMessage = nullptr);

	bool addMessage(QWidget *message,
			qint64 msgAuthor = -1); // if author is present, return
						// the success of operation
	bool addTextMessage(const QString &text,
			    qint64	   msgAuthor = -1); // same here

signals:
};

} // namespace GC

#endif // MESSAGEGROUP_H
