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

#include "utils/message.hpp"

namespace GC
{

Message::Message(QString &_sender,
		 QString &_message,
		 bool	  showAuthor,
		 MsgAlign status,
		 QWidget *parent)
    : QFrame{parent}, alignment{status}, is_confirmed{false}
{
	layout	       = new QHBoxLayout(this);
	sender_message = std::make_unique<QVBoxLayout>();

	if (showAuthor) {
		sender = new QLabel(this);
		sender->setStyleSheet(StyleSheets::MessageSenderSS);
		if (_sender.at(0) == '\x1b') {
			_sender = "Could not resolve author";
			sender->setStyleSheet(StyleSheets::MessageErrorSS);
		}
		sender->setText(_sender);
		sender_message->addWidget(sender, 1);
	}

	message = new QLabel(this);
	message->setWordWrap(true);
	message->setStyleSheet(StyleSheets::MessageSS);
	if (_message.at(0) == '\x1b') {
		_message = "Error receiving a message";
		message->setStyleSheet(StyleSheets::MessageErrorSS);
	}
	message->setText(_message);
	message->setMinimumWidth(100);
	message->setMaximumWidth(500);

	sender_message->addWidget(message, 2);

	layout->addLayout(sender_message.get());
	Qt::Alignment alignment =
	    Qt::AlignVCenter |
	    (status == sent ? Qt::AlignRight : Qt::AlignLeft);
	layout->setAlignment(alignment);
	sender_message->setAlignment(alignment);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
}

void Message::makeUnsent() {}
void Message::makeSent() {}

} // namespace GC
