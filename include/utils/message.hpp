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

#pragma once

#include <memory>

#include <QFrame>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "ui/stylesheets.hpp"

namespace GC
{

enum MsgAlign { sent, received };

class Message : public QFrame
{
	Q_OBJECT

	static inline const QIcon unconfirmed =
				      QIcon(":/icons_builtin/unread_mark.png"),
				  confirmed =
				      QIcon("/icons_builtin/read_mark.png");

	QLabel			    *sender, *message;
	QHBoxLayout		    *layout;
	std::unique_ptr<QVBoxLayout> sender_message;
	QIcon			    *senderPFP, *readStatus;

	MsgAlign alignment;

public:
	explicit Message(QString &_sender,
			 QString &_message,
			 bool	  showAuthor,
			 MsgAlign status,
			 QWidget *parent);

	void makeUnsent();
	void makeSent();

	bool is_confirmed;
};

} // namespace GC
