#ifndef WIDGET_H
#define WIDGET_H

#include <fstream>

#include "authorizer.h"
#include "userinterface.h"
#include "utils/misc_functions.h"
#include "utils/properties.h"
#include "utils/recentevent.h"

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
