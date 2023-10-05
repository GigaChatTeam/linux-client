#include "widget.h"

void Widget::setupConnections()
{
    connect(helloScreen, &Authorizer::successfullyAuthorized,
            this, &Widget::onAuthentication,
            Qt::DirectConnection);
}
//TODO: IMPLEMENT
void Widget::constructEvents()
{}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    authorizeControl = new QStackedLayout(this);
    helloScreen = new Authorizer(this);

    eventsAndUI = new QWidget();
    eventsAndUILayout = new QHBoxLayout(eventsAndUI);
    UI = new UserInterface();
    recentEvents = new QListWidget();
    eventsAndUILayout->addWidget(recentEvents, 1);
    eventsAndUILayout->addWidget(UI, 9);

    //can not put this before UI is initialized
    serverConnection_p = qobject_cast<ScrollingWidget*>(std::get<2>(UI->tabs[0]))->serverConnection;

    authorizeControl->addWidget(helloScreen);
    authorizeControl->addWidget(eventsAndUI);

    setupConnections();
}

Widget::~Widget()
{}

void Widget::onAuthentication()
{
    authorizeControl->setCurrentIndex(1);
#ifdef QT_DEBUG //to verify server token rejection
    USER_PROPERTIES.accessToken = "ИDИ_НАХУЙ_ПИДОРАС_DEEZ_NUTZ_SUCK_ON_DEEZ_BALLS";
#endif
    serverConnection_p->open(QUrl(
        SERVERS.cdnServer + QString("/id=%0&token=%1").arg(QString::number(USER_PROPERTIES.userID), USER_PROPERTIES.accessToken)
        ));
}

void Widget::addRecentEvents(QList<RecentEvent *> REList)
{
    foreach(RecentEvent* re, REList)
    {
        QListWidgetItem* item = new QListWidgetItem();
        recentEvents->addItem(item);
        recentEvents->setItemWidget(item, re);
    }
}

