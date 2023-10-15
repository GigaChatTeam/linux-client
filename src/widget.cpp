#include "widget.h"

//TODO: DEBUG & TEST
bool Widget::tokenIsPresent()
{
    /*      auth_data File structure:
    *   first string: tokes exists  ( 0 | 1 )
    *   if token exists == 1:
    *       second string: id           (  i64  )
    *       third string: user token    ( [chr] )
    *   else:
    *       second string does not matter
    *       and so does third
    */

    QFile auth_data("");
    if(!auth_data.exists())
    {
        DEBUG("AUTH DATA DOES NOT EXIST");
        auth_data.open(QFile::NewOnly | QFile::WriteOnly | QFile::Text);
        QTextStream out(&auth_data);
        out << "0" << Qt::endl;
        auth_data.close();
        auth_data.open(QFile::ReadOnly | QFile::Text);
        DEBUG("AUTH DATA STATUS: " << auth_data.isOpen());
    }

    if(!auth_data.isOpen())
    {
        DEBUG("AUTH DATA COULD NOT BE OPENED");
        return false;
    }

    QTextStream in(&auth_data);
    QString has_data, id, token;
    in >> has_data;

    if(has_data != "1")
        return false;

    in.skipWhiteSpace();
    id = in.readLine();
    token = in.readLine();

    if (id.isNull() || token.isNull())
        return false;

    USER_PROPERTIES.userID = id.toLongLong();
    USER_PROPERTIES.accessToken = token.toUtf8().data();
    return true;


/*
    std::fstream auth_data(":/id_and_token", std::ios::in);
    if (!auth_data.is_open())
    {
        DEBUG("AUTH DATA COULD NOT BE OPEN");
        auth_data.open(":/auth_data/id_token", std::ios::out);
        auth_data << "0" << std::endl;
        auth_data.close();
        auth_data.open(":/auth_data/id_token", std::ios::in);
        DEBUG("AUTH DATA STATUS: " << auth_data.is_open());
    }
    std::string has_data = "", id, token;
    //auth_data >> has_data should have side-effects
    //if it is evaluated to false, the has_data check should not be performed
    //therefore the following code should be valid
    if (!(auth_data >> has_data) || has_data != "1")
        return false;
    if (!std::getline(auth_data, id) || !std::getline(auth_data, token))
        return false;
    USER_PROPERTIES.userID = std::stoll(id);
    USER_PROPERTIES.accessToken = token.data();
    return true;
*/
}
void Widget::setupConnections()
{
    connect(helloScreen, &Authorizer::successfullyAuthorized,
            this, &Widget::onAuthentication,
            Qt::DirectConnection);
}
//TODO: IMPLEMENT
void Widget::constructUI()
{
    eventsAndUI = new QWidget();
    eventsAndUILayout = new QHBoxLayout(eventsAndUI);
    UI = new UserInterface();
    recentEvents = new QListWidget();
    eventsAndUILayout->addWidget(recentEvents, 1);
    eventsAndUILayout->addWidget(UI, 9);

    serverConnection_p = qobject_cast<ScrollingWidget*>(std::get<2>(UI->tabs[0]))->serverConnection;
        //must be initialized after UserInterface

    setupConnections();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    if (!tokenIsPresent())
        helloScreen = new Authorizer(this);
    else constructUI();

}

Widget::~Widget()
{}

void Widget::onAuthentication()
{
    delete helloScreen;
    constructUI();

#ifdef QT_DEBUG //to verify server token rejection
    USER_PROPERTIES.accessToken = "ИDИ_НАХУЙ_ПИДОРАС_DEEZ_NUTZ_SUCK_ON_DEEZ_BALLS";
#endif
    qobject_cast<ScrollingWidget*>(std::get<2>(UI->tabs[0]))->serverConnection->open(QUrl(SERVERS.cdnServer
        + QString("/id=%0&token=%1").arg(QString::number(USER_PROPERTIES.userID), USER_PROPERTIES.accessToken)));
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

