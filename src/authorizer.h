#pragma once

#include <QObject>

//stdc++
#include <optional>
#ifdef QT_DEBUG
    #include <iostream>
    #include <QDebug>
    #define DEBUG(str) qDebug() << str
#else
    #define DEBUG(str)
#endif

#include <QJsonDocument>
#include <QJsonObject>

#include <QStringView>
#include <QByteArray>
#include <QString>
#include <QPixmap>
#include <QDebug>

#include <QPushButton>
#include <QCheckBox>
#include <QSvgWidget>
#include <QLineEdit>
#include "utils/nonewlineqlineedit.h"
#include <QWidget>
#include <QLabel>

#include <QHBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>

#include <QResizeEvent>
#include <QKeyEvent>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include "stylesheets.h"
#include "utils/properties.h"
#include "utils/concepts_templates.h"
#include <functional>

class Authorizer : public QSvgWidget
{
    Q_OBJECT

private:

    struct InputField
    {
        QWidget* parent;

        void setupUI();
        void setupLayout();
        void setupConnections();
        void setStyles();
        explicit InputField(QWidget* newParent = nullptr);
        ~InputField();

        void reposition(QRect parentGeometry);

        QWidget *widget;
        QGridLayout* layout;
        NoNewLineQLineEdit *username,
                           *password;
        QSvgWidget  *submitBG;
        QPushButton *submit;
        QLabel *topLabel,
               *showPwLabel;
        QCheckBox* showPw;

        QLabel* errorMsg = nullptr;
    };

    QNetworkAccessManager mgr;

    QLabel* welcomeBack;

    InputField* field;
    QHBoxLayout* thisLayout;
    const QString BGImagePath = ":/resources/AuthorizeBG.svg";
    static const int resizeFactorH = 3,
                     resizeFactorV = 2;

protected:
    void resizeEvent(QResizeEvent* e) override;

public:
    explicit Authorizer(QWidget* parent = nullptr);

signals:
    void successfullyAuthorized(QByteArray response);

public slots:
    void parseResponse(QNetworkReply* response);
    void failedAuth(QString context);
    void sendLoginRequest();
};
