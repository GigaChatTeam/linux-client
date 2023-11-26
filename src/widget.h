#ifndef WIDGET_H
#define WIDGET_H

#include <fstream>

#include "authorizer.h"
#include "userinterface.h"
#include "utils/recentevent.h"
#include "utils/properties.h"

#include <QObject>

#include <QListWidget>
#include <QWidget>

#include <QStackedLayout>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QBoxLayout>

#include <QFile>
#include <QString>
#include <QWebSocket>

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

    inline void openWebsocket() {
        DEBUG(__PRETTY_FUNCTION__);
        QUrl url =
            SERVERS.cdnServer +
            QString("/?id=%0&token=%1").arg(
                QString::number(USER_PROPERTIES.userID),
                USER_PROPERTIES.accessToken
            );
        serverConnection_p->open(url);
        DEBUG(__PRETTY_FUNCTION__ << serverConnection_p->resourceName());
    }

public:

    QWebSocket* serverConnection_p;

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void onAuthentication();
    void addRecentEvents(QList<RecentEvent*> REList);
    void requireReauth();

};
#endif // WIDGET_H
