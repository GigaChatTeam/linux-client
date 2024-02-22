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

#ifndef WIDGET_H
#define WIDGET_H

#include <fstream>

#include "ui/authorizer.hpp"
#include "ui/userinterface.hpp"
#include "utils/misc_functions.hpp"
#include "utils/properties.hpp"
#include "utils/recentevent.hpp"

#include <QObject>

#include <QListWidget>
#include <QWidget>

#include <QBoxLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QStackedLayout>

#include <QByteArray>
#include <QFile>
#include <QList>
#include <QString>
#include <QWebSocket>

class Widget : public QWidget
{
	Q_OBJECT

private:
	Authorizer    *helloScreen = nullptr;
	UserInterface *UI	   = nullptr;

	QListWidget	    *recentEvents;
	QList<RecentEvent *> eventsList;

	QWidget	    *eventsAndUI;
	QHBoxLayout *eventsAndUILayout = nullptr;

	QBoxLayout *please_resize_authorizer = nullptr;

	bool tokenIsPresent();

	void setupUI();
	void setupConnections();
	void constructUI();

	void newAuthorizer();

	void initializeWSTokenRequest();

public:
	QWebSocket	      *serverConnection_p;
	QNetworkAccessManager *RTCDPreauth;

	Widget(QWidget *parent = nullptr);
	~Widget();

protected:
	void keyPressEvent(QKeyEvent *e) override;

public slots:
	void onAuthentication();
	void addRecentEvents(QList<RecentEvent *> REList);
	void requireReauth();
	void onTokenGet(QNetworkReply *re);
};
#endif // WIDGET_H
