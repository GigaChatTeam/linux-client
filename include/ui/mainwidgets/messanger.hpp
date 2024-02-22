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

#include "utils/properties.hpp"
#include <QObject>

#include "utils/concepts_templates.hpp"
#include "utils/message.hpp"
#include "utils/messagegroup.hpp"
#include "utils/misc_functions.hpp"
#include "utils/nonewlineqlineedit.hpp"
#include <QAbstractScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QUrl>
#include <QWebSocket>

#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

#include <QtCompilerDetection>

#include <optional>
#include <utility>

// TODO: REMOVE LATER
#ifdef QT_DEBUG
	#include <iostream>
	#define DEBUG(str) qDebug() << str
#else
	#define DEBUG(str)
#endif

struct package {
	QString	   command_type;
	QByteArray control_hash;
	QString	   message_data;
};

class ScrollingWidget : public QWidget
{
	/* IMPORTANT NOTE
	 * How are messages going to be displayed, stored, sorted and written to
	 * drive?
	 *
	 * -> messages are going to be stored in SQLite database (probably)
	 * -> on startup: load 1 message from each chat (maybe)
	 * -> upon entering chat: load N messages (default 128) from database
	 * -> store pointers to Message objects (widgets) in one hash map,
	 * common for every chat
	 * -> for each chat, construct a widget and a layout, use QStackedLayout
	 * or come up with a system for this yourself
	 * -> when tabbing in/out of chat, just switch chat widget
	 * -> when Websocket receives a message and the author is you, it must
	 * loop up the message pointer in hash map, set and indicator for
	 * delivered/error (like an icon of sorts)
	 * -> sending a message immediately writes it to database, so as
	 * receiving does
	 * -> control hash is NOT stored for received messages, so they
	 */

	Q_OBJECT

	QScrollArea	   *shownMessagesScroller;
	NoNewLineQLineEdit *inputLine;
	QPushButton	   *sendButton;

	QWidget	    *shownMessages;
	QVBoxLayout *shownMessagesLayout;

public:
	QWebSocket *serverConnection;
	QHash<QString, GC::Message *>
	    messagesDB; // TODO: store pointers to messages through control hash
	GC::MessageGroup *lastAddedGroup;

	void setupUI();
	void setupLayout();
	void setupConnections();
	explicit ScrollingWidget(QWidget *parent);
	~ScrollingWidget();

public slots:
	void addMessage(QString &text, qint64 _sender, GC::MsgAlign align);
	void errorOccured();

	void receiveTextMessage(QString message);
	void sendTextMessage();

public:
	static QString serializeMessage(const QString &messageText);
	static std::optional<QJsonObject>
	deserializeMessage(const QString &messageText);

	static void packageToString(const package &p, QString &s);
	static void stringToPackage(const QString	   &s,
				    std::optional<package> &p);
};
