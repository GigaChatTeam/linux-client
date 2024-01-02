#pragma once

#include <vector>

#include <QByteArray>
#include <QString>
#include <QUrl>

typedef struct {
	QByteArray	    token;
	qint64		    userID;
	std::vector<qint64> activeChannels, passiveChannels;
	QString		    username;
} USER_PROPERTIES_T;

typedef struct {
	QByteArray UID;
	QByteArray secret;
	QByteArray key;
} TOKEN_PARTS_T;

typedef struct {
	QString loginServer, cdnServer, hlbServer, tokengenServer;
} SERVERS_T;

typedef struct {
	QString home, var, db;
} FILEPATHS_T;

inline SERVERS_T SERVERS{
    "https://ru.gigacht.com", "wss://ru.gigacht.com", "https://???.com", ""};
inline FILEPATHS_T	 FILEPATHS;
inline TOKEN_PARTS_T	 TOKEN_PARTS;
inline USER_PROPERTIES_T USER_PROPERTIES
#ifdef QT_DEBUG
    {.token =
	 "user"
	 ".1"
	 ".2b05fcb8258766a46792c0673da54f45f36430895fd1e84bc800bf2dcfdad20f773a"
	 "668e"
	 ".iRfM87XTe2G0290unVMYWY4C3Vq0k_OHYFdF6B7JfnM-Saqu",
     .userID	      = 1,
     .activeChannels  = {},
     .passiveChannels = {},
     .username	      = "justanothercatgirl"}
#endif
;
