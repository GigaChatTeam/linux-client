#pragma once

#include <vector>

#include <QString>
#include <QByteArray>
#include <QUrl>

// may result in data initialization faliure
// TODO: reconsider life choices
typedef struct {
    QByteArray accessToken;
    qint64 userID;
    std::vector<qint64> activeChannels,
                        passiveChannels;
    QString username;
} USER_PROPERTIES_T;

typedef struct {
    QString loginServer,
            cdnServer,
            hlbServer,
            tokengenServer;
} SERVERS_T;

typedef struct {
    QString home,
            var,
            db;
} FILEPATHS_T;

extern USER_PROPERTIES_T USER_PROPERTIES;
extern SERVERS_T SERVERS;
extern FILEPATHS_T FILEPATHS;
