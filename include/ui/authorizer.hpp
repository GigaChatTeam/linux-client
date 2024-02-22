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

#include <QObject>

#include <optional>
#ifdef QT_DEBUG
	#include <QDebug>
	#include <iostream>
	#define DEBUG(str) qDebug() << str
#else
	#define DEBUG(str)
#endif

#include <QJsonDocument>
#include <QJsonObject>

#include <QByteArray>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QStringView>

#include "utils/nonewlineqlineedit.hpp"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSvgWidget>
#include <QWidget>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

#include <QKeyEvent>
#include <QResizeEvent>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include "stylesheets.hpp"
#include "utils/concepts_templates.hpp"
#include "utils/properties.hpp"
#include <functional>

class Authorizer : public QSvgWidget
{
	Q_OBJECT

private:
	struct InputField {
		QWidget *parent;

		void setupUI();
		void setupLayout();
		void setupConnections();
		void setStyles();
		explicit InputField(QWidget *newParent = nullptr);
		~InputField();

		void reposition(QRect parentGeometry);

		QWidget		   *widget;
		QGridLayout	   *layout;
		NoNewLineQLineEdit *username, *password;
		QSvgWidget	   *submitBG;
		QPushButton	   *submit;
		QLabel		   *topLabel, *showPwLabel;
		QCheckBox	   *showPw;

		QLabel *errorMsg = nullptr;
	};

	QNetworkAccessManager *mgr;

	QLabel *welcomeBack;

	InputField	*field;
	QHBoxLayout	*thisLayout;
	const QString	 BGImagePath   = ":/resources/AuthorizeBG.svg";
	static const int resizeFactorH = 3, resizeFactorV = 2;

protected:
	void resizeEvent(QResizeEvent *e) override;

public:
	explicit Authorizer(QWidget *parent = nullptr);
	static bool onlyWhitespaces(const QString &&str);

signals:
	void successfullyAuthorized();

public slots:
	void parseResponse(QNetworkReply *response);
	void failedAuth(QString context);
	void sendLoginRequest();
};