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

#include "utils/nonewlineqlineedit.h"
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

#include "stylesheets.h"
#include "utils/concepts_templates.h"
#include "utils/properties.h"
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
