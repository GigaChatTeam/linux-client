#include "widget.h"

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

    QFile auth_data(SHARE_DIRECTORY "/token");
    if(!auth_data.exists())
    {
        auth_data.open(QFile::NewOnly | QFile::WriteOnly | QFile::Text);
        QTextStream out(&auth_data);
        out << "0" << Qt::endl;
        auth_data.close();
    }

    auth_data.open(QFile::ReadOnly | QFile::Text);

    if(!auth_data.isOpen())
        return false;

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

    bool ID_valid;
    USER_PROPERTIES.userID = id.toLongLong(&ID_valid);
    USER_PROPERTIES.accessToken = token.toUtf8().data();
    return ID_valid;
}
void Widget::setupConnections()
{
    if (helloScreen != nullptr)
    {
        connect(helloScreen, &Authorizer::successfullyAuthorized,
                this, &Widget::onAuthentication,
                Qt::AutoConnection);
    }
}

void Widget::constructUI()
{
    eventsAndUILayout = new QHBoxLayout(this);
    UI = new UserInterface();
    recentEvents = new QListWidget(this);
    eventsAndUILayout->addWidget(recentEvents, 1);
    eventsAndUILayout->addWidget(UI, 9);
    RTCDPreauth = new QNetworkAccessManager(this);

    serverConnection_p = qobject_cast<ScrollingWidget*>(std::get<2>(UI->tabs[0]))->serverConnection;
    openWebsocket();
}

void Widget::newAuthorizer()
{
    helloScreen = new Authorizer();
    setupConnections();
    please_resize_authorizer = new QBoxLayout(QBoxLayout::TopToBottom, this);
    please_resize_authorizer->setContentsMargins(0, 0, 0, 0);
    please_resize_authorizer->addWidget(helloScreen);
}

// TODO: RENAME FUNCTIONS
// THIS FUNCTION ONLY STARTS REQUEST
void Widget::openWebsocket()
{
    // TODO: get 'secret', 'client' and 'key' from CC
    /// user.1.5d31654918b943891e05387d0e22b3b3ad7fe05a2e0d8bbd87131b49ca72bb6af44df17b._p1CdoStvml60QWnCHFy1OsQkl9_sySm8H9qo49eSEH2Bnzv
    /// in this string:
    /// 1: client
    /// 5d31654918b943891e05387d0e22b3b3ad7fe05a2e0d8bbd87131b49ca72bb6af44df17b: secret
    /// _p1CdoStvml60QWnCHFy1OsQkl9_sySm8H9qo49eSEH2Bnzv: key
    QString secret = "",
            client = "",
            key = "";

    QNetworkRequest re = QNetworkRequest(SERVERS.tokengenServer);
    QByteArray postData = QString(R"({"secret":"%1","key":"%3"p,"client":"%2"})").arg(secret, client, key).toUtf8();
    connect(RTCDPreauth, SIGNAL(finished(QNetworkReply*)), this, SLOT(onTokenGet(QNetworkReply*)));
    RTCDPreauth->post(re, postData);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    if (!tokenIsPresent())  newAuthorizer();
    else                    constructUI();

}

Widget::~Widget()
{}

void Widget::keyPressEvent(QKeyEvent *e)
{
#ifdef QT_DEBUG
    if (e->key() == Qt::Key_K && e->modifiers() == Qt::ControlModifier)
    {   // switch between authorization screens
        if (please_resize_authorizer) {
            onAuthentication();
        } else if (eventsAndUILayout) {
            requireReauth();
        } else {
            std::terminate();
        }
        e->accept();
        return;
    }
#endif

    QWidget::keyPressEvent(e);
}
void Widget::onAuthentication()
{
    delete please_resize_authorizer;
    please_resize_authorizer = nullptr;
    helloScreen->deleteLater();

    constructUI();
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
void Widget::requireReauth()
{
    deleteLayoutWidgets(eventsAndUILayout);
    delete eventsAndUILayout;
    eventsAndUILayout = nullptr;
    newAuthorizer();
}
void Widget::onTokenGet(QNetworkReply *re)
{
    QJsonObject jsonData = QJsonDocument::fromJson(re->readAll()).object();
    
    auto a1 = getJsonSafe<QString>("a1", jsonData);
    auto a2 = getJsonSafe<QString>("a2", jsonData);
    auto a3 = getJsonSafe<QString>("a3", jsonData);

    if (!a1 || !a2 || !a3) {
        qInfo() << "\e[91m" << "ERROR IN FUNCTION" << __PRETTY_FUNCTION__
                << ": BAD JSON\e[0m";
        return; // TODO: HANDLE
    }
    QUrl url =
        SERVERS.cdnServer +
        QString("/?id=%0&token=%1").arg(
            QString::number(USER_PROPERTIES.userID),
            USER_PROPERTIES.accessToken
        );
    serverConnection_p->open(url);
}

