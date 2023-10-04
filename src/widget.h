#ifndef WIDGET_H
#define WIDGET_H

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

class Widget : public QWidget
{
    Q_OBJECT

private:
    QStackedLayout* authorizeControl;
    Authorizer* helloScreen;
    UserInterface* UI;

    QListWidget* recentEvents;
    QList<RecentEvent*> eventsList;

    QWidget* eventsAndUI;
    QHBoxLayout* eventsAndUILayout;

    void setupUI();
    void setupConnections();
    void constructEvents();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onAuthentication();
    void addRecentEvents(QList<RecentEvent*> REList);

};
#endif // WIDGET_H
