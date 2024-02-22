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

#include "utils/messagegroup.hpp"

GC::MessageGroup::MessageGroup(QWidget *parent,
			       qint64	msgAuthor,
			       MsgAlign status,
			       QWidget *firstMessage)
    : QWidget{parent}, author{msgAuthor}
{
	layout = new QVBoxLayout(this);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
	align_status = Qt::AlignVCenter |
		       (status == sent ? Qt::AlignRight : Qt::AlignLeft);
	authorLabel = new QLabel(QString::number(author),
				 this); // TODO: search author's name
	authorLabel->setStyleSheet(StyleSheets::MessageSenderSS);
	layout->addWidget(authorLabel);
	layout->setAlignment(align_status);
	if (firstMessage != nullptr) { addMessage(firstMessage); }
}

bool GC::MessageGroup::addMessage(QWidget *message, qint64 msgAuthor)
{
	if (msgAuthor != -1 && author != msgAuthor) return false;

	message->setParent(this); // transfer ownership
	layout->addWidget(message);
	message->layout()->setAlignment(align_status);
	message->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	return true;
}

bool GC::MessageGroup::addTextMessage([[maybe_unused]] const QString &text,
				      qint64			      msgAuthor)
{
	if (msgAuthor != -1 && author != msgAuthor) return false;

	// TODO: implement
	// after I remove "author" or "sender" property from message class

	return true;
}
