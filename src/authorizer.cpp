#include "authorizer.h"

void Authorizer::InputField::setupUI()
{
	widget	 = new QWidget(parent);
	layout	 = new QGridLayout(widget);
	username = new NoNewLineQLineEdit(tr("Username goes here,"), parent);
	password =
	    new NoNewLineQLineEdit(tr("Password - here..."), true, parent);
	submitBG    = new QSvgWidget(":/resources/LoginBN.svg", parent);
	submit	    = new QPushButton(tr("Log in"), submitBG);
	topLabel    = new QLabel(tr("Login"), parent);
	showPw	    = new QCheckBox(parent);
	showPwLabel = new QLabel(tr("show password"), parent);

	QHBoxLayout *submitLayout = new QHBoxLayout(submitBG);
	submitLayout->setContentsMargins(0, 0, 0, 0);
	submitLayout->addWidget(submit);
	submit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void Authorizer::InputField::setupLayout()
{
	layout->addWidget(topLabel, 0, 0, 2, 4);
	layout->addWidget(username, 2, 0, 2, 4);
	layout->addWidget(password, 4, 0, 2, 4);
	layout->addWidget(showPw, 6, 1, 1, 1);
	layout->addWidget(showPwLabel, 6, 2, 1, 2);
	layout->addWidget(submitBG, 7, 0, 2, 4);
	topLabel->setAlignment(Qt::AlignCenter);

	for (int i = 0; i < layout->columnCount(); ++i)
		for (int j = 0; j < layout->rowCount(); ++j) {
			layout->setColumnStretch(i, 1);
			layout->setRowStretch(j, 1);
		}

	for (int i = 0; i < layout->count(); ++i)
		layout->itemAt(i)->widget()->setSizePolicy(
		    QSizePolicy::MinimumExpanding,
		    QSizePolicy::MinimumExpanding);
}
void Authorizer::InputField::setupConnections()
{
	connect(submit,
		SIGNAL(clicked()),
		parent,
		SLOT(sendLoginRequest()),
		Qt::DirectConnection);
	connect(password,
		SIGNAL(enterPressed()),
		parent,
		SLOT(sendLoginRequest()),
		Qt::DirectConnection);
	connect(username,
		SIGNAL(enterPressed()),
		password,
		SLOT(setFocus()),
		Qt::DirectConnection);
	connect(showPw,
		SIGNAL(stateChanged(int)),
		password,
		SLOT(setPasswordHide(int)),
		Qt::DirectConnection);
}
void Authorizer::InputField::setStyles()
{
	using namespace StyleSheets;
	submitBG->setStyleSheet(SVGBGSS);
	topLabel->setStyleSheet(LabelSS);
	showPwLabel->setStyleSheet(CheckboxSS);
}
Authorizer::InputField::InputField(QWidget *newParent) : parent{newParent}
{
	setupUI();
	setupLayout();
	setupConnections();
	setStyles();
	reposition(newParent->geometry());
}
void Authorizer::InputField::reposition(QRect parentGeometry)
{
	int x1 = parentGeometry.height(), y1 = parentGeometry.width();
	int x2 = x1 / resizeFactorV, y2 = y1 / resizeFactorH;

	widget->setGeometry((y1 - y2) / 2, (x1 - x2) / 2, y2, x2);
}
Authorizer::InputField::~InputField() { delete widget; }

Authorizer::Authorizer(QWidget *parent) : QSvgWidget{parent}
{
	mgr = new QNetworkAccessManager(this);
#ifdef QT_DEBUG
	mgr->setTransferTimeout(1000);
#endif

	setMinimumSize(666, 420);
	load(BGImagePath);

	field	    = new InputField(this);
	welcomeBack = new QLabel(tr("Welcome back!"), this);
	welcomeBack->setStyleSheet(StyleSheets::LabelSS);
	welcomeBack->setMargin(30);

	connect(mgr,
		&QNetworkAccessManager::finished,
		this,
		&Authorizer::parseResponse,
		Qt::DirectConnection);
}

bool Authorizer::onlyWhitespaces(const QString &&str)
{
	QString temp = str;
	temp.removeIf([](auto x) { return QChar(x).isSpace(); });
	return temp.isEmpty();
}

void Authorizer::sendLoginRequest()
{
	if (field->password->isDefault || field->username->isDefault) {
		failedAuth(tr("Error: username and password can't be empty"));
		return;
	}

	if (onlyWhitespaces(field->password->text()) ||
	    onlyWhitespaces(field->username->text())) {
		failedAuth(
		    tr("Error: username and password can't consist only of "
		       "whitespaces"));
		return;
	}

	QString requestData =
	    QString("username=%1&password=%2")
		.arg(field->username->text(), field->password->text());

	QNetworkRequest authRequest =
	    QNetworkRequest(QUrl(SERVERS.loginServer + "/auth"));
	mgr->post(authRequest, requestData.toUtf8());
}
void Authorizer::parseResponse(QNetworkReply *response)
{
	QByteArray jsonEscapeString = response->readAll();
	DEBUG("DATA RECIEVED:\n\x1b[1;33;40m" << jsonEscapeString << "\x1b[0m");

	if (response->error() != QNetworkReply::NoError) {
		qInfo() << "\x1b[1;33;40mNETWORK ERROR RECIEVED:"
			<< response->error() << "\x1b[0m";
		QString error =
		    tr("Login request failed:\n"
		       "Error code: %1\n%2");
		failedAuth(error.arg(QString::number(response->error()),
				     response->errorString()));

#ifdef QT_DEBUG
		USER_PROPERTIES.token  = "test_token";
		USER_PROPERTIES.userID = 'TEST';
		if (field->username->text() == "test") {
			delete field;
			emit successfullyAuthorized();
		}
		return;
#endif
	}

	jsonEscapeString.replace(
	    "\\", 1, "", 0); // I cant't fucking believe that this line of code
			     // cost me 7 fukcing hours
	QJsonObject respJson =
	    QJsonDocument::fromJson(jsonEscapeString).object();

	getJsonSafe<QJsonObject>("data", respJson)
	    .or_else([&respJson, this]
		     -> std::optional<QJsonObject> { // shut up qtcreator, this
						     // is valid syntax in C++23
		    failedAuth(QString("Error: ") +
			       getJsonSafe<QString>("description", respJson)
				   .value_or("Unresolved JSON error"));
		    return std::nullopt;
	    })
	    .and_then([&response,
		       this](QJsonObject data) -> std::optional<QJsonObject> {
		    USER_PROPERTIES.token =
			getJsonSafe<QString>("token", data)
			    .transform([](QString maybe_value) {
				    return maybe_value.toUtf8();
			    })
			    .value_or(QByteArray());
		    USER_PROPERTIES.userID =
			getJsonSafe<qint64>("id", data).value_or(-1);
		    USER_PROPERTIES.username =
			getJsonSafe<QString>("username", data).value_or("");
		    QList<QByteArray> tmp = USER_PROPERTIES.token.split('.');
		    TOKEN_PARTS.UID	  = tmp.at(1);
		    TOKEN_PARTS.secret	  = tmp.at(2);
		    TOKEN_PARTS.key	  = tmp.at(3);
		    delete field;
		    emit successfullyAuthorized();
		    return std::nullopt;
	    });
}
void Authorizer::failedAuth(QString context)
{
	if (field->errorMsg != nullptr) goto textset;
	{
		setStyleSheet(StyleSheets::FailedAuthSS);
		QLabel *temp = new QLabel();
		temp->setWordWrap(true);
		temp->setSizePolicy(QSizePolicy::MinimumExpanding,
				    QSizePolicy::MinimumExpanding);
		temp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		temp->setStyleSheet("color: red; font: bold 12pt");
		field->layout->addWidget(temp, 9, 0, 1, 4);
		field->errorMsg = temp;
	}
textset:
	field->errorMsg->setText(context);
	field->username->setFocus();
}
void Authorizer::resizeEvent(QResizeEvent *e)
{
	QSvgWidget::resizeEvent(e);
	field->reposition(geometry());
}
