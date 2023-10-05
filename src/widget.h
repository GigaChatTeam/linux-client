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

#include <QString>
#include <QWebSocket>

class Widget : public QWidget
{
    Q_OBJECT

private:
    Authorizer* helloScreen;
    UserInterface* UI;

    QListWidget* recentEvents;
    QList<RecentEvent*> eventsList;

    QWidget* eventsAndUI;
    QHBoxLayout* eventsAndUILayout;

    bool tokenIsPresent();

    void setupUI();
    void setupConnections();
    void constructUI();
public:

    QWebSocket* serverConnection_p;

    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onAuthentication();
    void addRecentEvents(QList<RecentEvent*> REList);

};
#endif // WIDGET_H
