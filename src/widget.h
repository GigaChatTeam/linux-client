#ifndef WIDGET_H
#define WIDGET_H

#include <fstream>

#include "authorizer.h"
#include "userinterface.h"
#include "utils/recentevent.h"
#include "utils/properties.h"
#include "utils/misc_functions.h"

#include <QObject>

#include <QListWidget>
#include <QWidget>

#include <QStackedLayout>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QBoxLayout>

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QWebSocket>
// #include <QNetworkAccessManager>
// #include <QNetworkRequest>
// #include <QNetworkReply>

class Widget : public QWidget
{
    Q_OBJECT

private:
    Authorizer* helloScreen = nullptr;
    UserInterface* UI = nullptr;

    QListWidget* recentEvents;
    QList<RecentEvent*> eventsList;

    QWidget* eventsAndUI;
    QHBoxLayout* eventsAndUILayout = nullptr;

    QBoxLayout* please_resize_authorizer = nullptr;

    bool tokenIsPresent();

    void setupUI();
    void setupConnections();
    void constructUI();

    void newAuthorizer();

    void openWebsocket();

public:

    QWebSocket* serverConnection_p;
    QNetworkAccessManager* RTCDPreauth;

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void onAuthentication();
    void addRecentEvents(QList<RecentEvent*> REList);
    void requireReauth();
    void onTokenGet(QNetworkReply* re);

};
#endif // WIDGET_H
