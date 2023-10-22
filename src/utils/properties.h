#pragma once

#include <vector>

#include <QString>
#include <QByteArray>
#include <QUrl>

typedef struct {
    QByteArray accessToken;
    qint64 userID;
    std::vector<qint64> activeChannels,
                               passiveChannels;
} USER_PROPERTIES_T;

typedef struct {
    QString loginServer,
            cdnServer;
} SERVERS_T;

typedef struct {
    QString home, // will need if someone tries to build this for linux
            var,
            db;
} FILEPATHS_T;

extern USER_PROPERTIES_T USER_PROPERTIES;
extern SERVERS_T SERVERS;
extern FILEPATHS_T FILEPATHS;
