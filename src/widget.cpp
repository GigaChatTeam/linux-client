#include "widget.h"

bool Widget::tokenIsPresent()
{
	/*
	 *       auth_data File structure:
	 *   first string: tokes exists  ( 0 | 1 )
	 *   if token exists == 1:
	 *       second string: id           (  i64  )
	 *       third string: user token    ( [chr] )
	 *   else:
	 *       second string does not matter
	 *       and so does third
	 */

	QFile auth_data(SHARE_DIRECTORY "/token");
	if (!auth_data.exists()) {
		auth_data.open(QFile::NewOnly | QFile::WriteOnly | QFile::Text);
		QTextStream out(&auth_data);
		out << "0" << Qt::endl;
		auth_data.close();
	}

	auth_data.open(QFile::ReadOnly | QFile::Text);

	if (!auth_data.isOpen()) return false;

	QTextStream in(&auth_data);
	QString	    has_data, id, token;
	in >> has_data;

	if (has_data != "1") return false;

	in.skipWhiteSpace();
	id    = in.readLine();
	token = in.readLine();

	if (id.isNull() || token.isNull()) return false;

	bool ID_valid;
	USER_PROPERTIES.userID = id.toLongLong(&ID_valid);
	USER_PROPERTIES.token  = token.toUtf8().data();
	return ID_valid;
}
void Widget::setupConnections()
{
	if (helloScreen != nullptr) {
		connect(helloScreen,
			&Authorizer::successfullyAuthorized,
			this,
			&Widget::onAuthentication,
			Qt::AutoConnection);
	}
}

void Widget::constructUI()
{
	eventsAndUILayout = new QHBoxLayout(this);
	UI		  = new UserInterface();
	recentEvents	  = new QListWidget(this);
	eventsAndUILayout->addWidget(recentEvents, 1);
	eventsAndUILayout->addWidget(UI, 9);
	RTCDPreauth = new QNetworkAccessManager(this);

	serverConnection_p =
	    qobject_cast<ScrollingWidget *>(std::get<2>(UI->tabs[0]))
		->serverConnection;
	initializeWSTokenRequest();
}

void Widget::newAuthorizer()
{
	helloScreen = new Authorizer();
	setupConnections();
	please_resize_authorizer =
	    new QBoxLayout(QBoxLayout::TopToBottom, this);
	please_resize_authorizer->setContentsMargins(0, 0, 0, 0);
	please_resize_authorizer->addWidget(helloScreen);
}

void Widget::initializeWSTokenRequest()
{
	auto	   re = QNetworkRequest(SERVERS.tokengenServer);
	QByteArray postData =
	    QString(R"({"secret":"%1","key":"%2","client":%3})")
		.arg(TOKEN_PARTS.secret, TOKEN_PARTS.key, TOKEN_PARTS.UID)
		.toUtf8();
	connect(RTCDPreauth,
		SIGNAL(finished(QNetworkReply *)),
		this,
		SLOT(onTokenGet(QNetworkReply *)));
	RTCDPreauth->post(re, postData);
	qInfo().noquote() << postData;
}

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	if (!tokenIsPresent()) newAuthorizer();
	else
		constructUI();
}

Widget::~Widget() {}

void Widget::keyPressEvent(QKeyEvent *e)
{
#ifdef QT_DEBUG
	if (e->key() == Qt::Key_K &&
	    e->modifiers() ==
		Qt::ControlModifier) { // switch between authorization screens
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
	foreach (RecentEvent *re, REList) {
		QListWidgetItem *item = new QListWidgetItem();
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
	disconnect(RTCDPreauth);

	QJsonObject jsonData = QJsonDocument::fromJson(re->readAll()).object();

	DEBUG(jsonData);

	auto status	= getJsonSafe<QString>("status", jsonData);
	auto temp_token = getJsonSafe<QString>("token", jsonData);

	if (!status || !temp_token) {
		qInfo().nospace() << "\x1b[91mERROR IN FUNCTION "
				  << __PRETTY_FUNCTION__ << ": BAD JSON\x1b[0m";
		return;
	}
	QUrl url = SERVERS.cdnServer +
		   QString("/%0/%1").arg(TOKEN_PARTS.UID, temp_token.value());
	serverConnection_p->open(url);
}
