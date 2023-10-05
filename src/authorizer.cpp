#include "authorizer.h"

void Authorizer::InputField::setupUI()
{
    widget = new QWidget(parent);
    layout   = new QGridLayout(widget);
    username = new NoNewLineQLineEdit(tr("Username goes here,"));
    password = new NoNewLineQLineEdit(tr("Password - here..."), true);
    submitBG = new QSvgWidget(":/resources/LoginBN.svg");
    submit = new QPushButton(tr("Log in"), submitBG);
    topLabel = new QLabel(tr("Login"));
    showPw = new QCheckBox();
    showPwLabel = new QLabel(tr("show password"));

    QHBoxLayout* submitLayout = new QHBoxLayout(submitBG);
    submitLayout->setContentsMargins(0, 0, 0, 0);
    submitLayout->addWidget(submit);
    submit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void Authorizer::InputField::setupLayout()
{
    layout->addWidget(topLabel,    0, 0, 2, 4);
    layout->addWidget(username,    2, 0, 2, 4);
    layout->addWidget(password,    4, 0, 2, 4);
    layout->addWidget(showPw,      6, 1, 1, 1);
    layout->addWidget(showPwLabel, 6, 2, 1, 2);
    layout->addWidget(submitBG,    7, 0, 2, 4);
    topLabel->setAlignment(Qt::AlignCenter);

    for(int i = 0; i < layout->columnCount(); ++i)
    for(int j = 0; j < layout->rowCount(); ++j)
    {
        layout->setColumnStretch(i, 1);
        layout->setRowStretch(j, 1);
    }

    for(int i = 0; i < layout->count(); ++i)
        layout->itemAt(i)->widget()->setSizePolicy(
                    QSizePolicy::Expanding,
                    QSizePolicy::Expanding);
}
void Authorizer::InputField::setupConnections()
{
    connect(submit   , SIGNAL(clicked())         , parent    , SLOT(sendLoginRequest())     , Qt::DirectConnection);
    connect(password , SIGNAL(enterPressed())    , parent    , SLOT(sendLoginRequest())     , Qt::DirectConnection);
    connect(username , SIGNAL(enterPressed())    , password  , SLOT(setFocus())             , Qt::DirectConnection);
    connect(showPw   , SIGNAL(stateChanged(int)) , password  , SLOT(setPasswordHide(int))   , Qt::DirectConnection);
}
void Authorizer::InputField::setStyles()
{
    using namespace StyleSheets;
    submitBG->setStyleSheet(SVGBGSS);
    topLabel->setStyleSheet(LabelSS);
    showPwLabel->setStyleSheet(CheckboxSS);
}
Authorizer::InputField::InputField(QWidget* newParent)
    : parent{newParent}
{
    setupUI();
    setupLayout();
    setupConnections();
    setStyles();
    reposition(newParent->geometry());
}
void Authorizer::InputField::reposition(QRect parentGeometry)
{
    int x1 = parentGeometry.height(),
        y1 = parentGeometry.width();
    int x2 = x1/resizeFactorV,
        y2 = y1/resizeFactorH;

    widget->setGeometry( (y1-y2)/2, (x1-x2)/2, y2, x2 );
}
Authorizer::InputField::~InputField()
{
    delete widget;
}


Authorizer::Authorizer(QWidget *parent)
    : QSvgWidget{parent}
{
    mgr.setTransferTimeout(5000); //5 seconds. may be changed later.

    setMinimumSize(666, 420);
    load(BGImagePath);


    field = new InputField(this);
    welcomeBack = new QLabel(tr("Welcome back!"), this);
    welcomeBack->setStyleSheet(StyleSheets::LabelSS);
    welcomeBack->setMargin(30);

    connect(&mgr, &QNetworkAccessManager::finished,
            this, &Authorizer::parseResponse,
            Qt::DirectConnection);
}

void Authorizer::sendLoginRequest()
{

    if (field->password->isDefault() || field->username->isDefault())
    {
        failedAuth(tr("Error: username and password can't be empty"));
        return;
    }

    QString requestUrl = QString("/"
#ifndef GIGAQT_AUTH_PARSE_TEST
                                 "auth"
#else
                                 "debug"
#endif
                                 "?username=%1&password=%2")
                            .arg(field->username->text(), field->password->text());

    QNetworkRequest authRequest = QNetworkRequest(QUrl(SERVERS.loginServer + requestUrl));
    mgr.get(authRequest);
}
void Authorizer::parseResponse(QNetworkReply* response)
{
    QByteArray jsonEscapeString = response->readAll();
    DEBUG( "DATA RECIEVED:\n\e[1;33;40m" << jsonEscapeString << "\e[0m" );

    if(response->error() != QNetworkReply::NoError)
    {
        DEBUG( "\e[1;33;40mNETWORK ERROR RECIEVED:"
                 << response->error()
                 << "\e[0m" );
        QString error = tr("Login request failed:\n"
                           "Error code: %1\n%2");
        failedAuth(error.arg(QString::number(response->error()), response->errorString()));

#ifdef QT_DEBUG
        USER_PROPERTIES.accessToken = "test_token";
        USER_PROPERTIES.userID = 'TEST';
        if(field->username->text() == "test")
            emit successfullyAuthorized();
#endif
#ifndef GIGAQT_AUTH_PARSE_TEST
        return;
#endif
    }

    jsonEscapeString.replace("\\", 1, "", 0); // I cant't fucking believe that this line of code costed me 7 fukcing horts
    QJsonObject respJson = QJsonDocument::fromJson(jsonEscapeString).object();


    //not cutting out of the source just to remember all the suffering
#ifdef GIGAQT_AUTH_PARSE_TEST
    // TODO: fix response parsing when receiving from server
    // it works with these tests, but not with actual server
    QByteArray __success_ex__ = "{\"auth-data\":{\"AAAA\": true}}",
               __fail_ex__ = "{\"status\": \"Refused\", \"reason\": \"BadRequest\", \"description\": \"UserNotFound\"}";
    respJson = QJsonDocument::fromJson(
                   __success_ex__
                   //__fail_ex__
                   ).object();
#endif


    DEBUG("\e[1;93m" << jsonEscapeString << "\e[0m");
    DEBUG(getJsonSafe<QJsonObject>("auth-data", respJson).has_value() << respJson["auth-data"].toObject());

    // Unreadable functional code, hell yeah
    getJsonSafe<QJsonObject>("auth-data", respJson)
    .or_else([&respJson, this] -> std::optional<QJsonObject> { // shut up qtcreator, this is valid syntax in C++23
        DEBUG("OR_ELSE TRIGGERED: " << __PRETTY_FUNCTION__);
        failedAuth(QString("Error: ") + getJsonSafe<QString>("description", respJson)
           .value_or("Unresolved JSON error"));
        return std::nullopt;
    })
    .and_then([&response, this](QJsonObject data) -> std::optional<QJsonObject>{
        DEBUG("AND_THEN TRIGGERED: " << __PRETTY_FUNCTION__);
        USER_PROPERTIES.accessToken = getJsonSafe<QString>("token", data)
            .transform([](QString maybe_value){
                return maybe_value.toUtf8();
            }).value_or(QByteArray());
        USER_PROPERTIES.userID = getJsonSafe<qint64>("id", data).value_or(-1);
        DEBUG("token: " << USER_PROPERTIES.accessToken << Qt::endl << "ID: " << USER_PROPERTIES.userID);
        emit successfullyAuthorized();
        return std::nullopt;
    });
}
void Authorizer::failedAuth(QString context)
{
    if (field->errorMsg != nullptr) goto textset;
    {
        setStyleSheet(StyleSheets::FailedAuthSS);
        QLabel* temp = new QLabel();
        temp->setWordWrap(true);
        temp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        temp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        temp->setStyleSheet("color: red; font: bold 12pt");
        field->layout->addWidget(temp, 9, 0, 1, 4);
        field->errorMsg = temp; //i'm lazy
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
