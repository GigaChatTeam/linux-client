#pragma once

#include <vector>

#include <QString>
#include <QByteArray>
#include <QUrl>

struct {
    QByteArray accessToken;
    int64_t userID;
    std::vector<int64_t> activeChannels,
                         passiveChannels;
} USER_PROPERTIES;

struct {
    QString loginServer,
            cdnServer;
} SERVERS {"https://ru.gigacht.com", "wss://ru.gigacht.com"};

