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
                Qt::DirectConnection);
    }
}

void Widget::constructUI()
{
    // Authorizer presense check must done beforehand
    if (this->layout() != nullptr) std::terminate();

    eventsAndUILayout = new QHBoxLayout(this);
    UI = new UserInterface();
    recentEvents = new QListWidget();
    eventsAndUILayout->addWidget(recentEvents, 1);
    eventsAndUILayout->addWidget(UI, 9);

    serverConnection_p = qobject_cast<ScrollingWidget*>(std::get<2>(UI->tabs[0]))->serverConnection;
        // must be initialized after UserInterface
        // obviously
        // didn't spend 5 hours trying to figure out this segfault

    setupConnections();

    openWebsocket();
}

void Widget::newAuthorizer()
{
    // UI presense check must done beforehand
    if (this->layout() != nullptr) std::terminate();

    helloScreen = new Authorizer(/*this*/);
    please_resize_authorizer = new QBoxLayout(QBoxLayout::TopToBottom, this);
    please_resize_authorizer->setContentsMargins(0, 0, 0, 0);
    please_resize_authorizer->addWidget(helloScreen);

    setLayout(please_resize_authorizer);
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
#ifdef QT_DEBUG // obviously, for debugging purposes
    if (e->key() == Qt::Key_K && e->modifiers() == Qt::ControlModifier)
    {   // switch between authorization screens
        if (please_resize_authorizer) {
            onAuthentication();
            qDebug() << "killing authorizer\n";
        } else if (eventsAndUILayout) {
            requireReauth();
            qDebug() << "killing killing UI\n";
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
    delete please_resize_authorizer; please_resize_authorizer = nullptr;
    delete helloScreen; helloScreen = nullptr;

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
    if (eventsAndUILayout) delete eventsAndUILayout;
    eventsAndUILayout = nullptr; //outside of "if" because this does not matter

    newAuthorizer();

}

