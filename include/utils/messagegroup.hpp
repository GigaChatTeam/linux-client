/* ----------------------------------------------------------------------------
   gigachat-linux-client - A linux client for gigachat digital ecosystem
   Copyright (C) 2024 Sotov Konstantin A

   This file is part of linux client for gigachat.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------------
*/

#ifndef MESSAGEGROUP_H
#define MESSAGEGROUP_H

#include <QLabel>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include "ui/stylesheets.hpp"
#include "utils/message.hpp"

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
