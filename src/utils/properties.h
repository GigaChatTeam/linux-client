#pragma once

#include <vector>

#include <QString>
#include <QByteArray>
#include <QUrl>

typedef struct {
    QByteArray accessToken;
    int64_t userID;
    std::vector<int64_t> activeChannels,
                         passiveChannels;
} USER_PROPERTIES_T;

typedef struct {
    QString loginServer,
            cdnServer;
} SERVERS_T;

extern USER_PROPERTIES_T USER_PROPERTIES;
extern SERVERS_T SERVERS;

