/* ----------------------------------------------------------------------------
   gigachat-linux-client - A linux client for gigachat digital ecosystem
   Copyright (C) 2024 Sotov Konstantin A

   This file is part of linux client for gigachat.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------------
*/

//! initializations of variable in this file should happen on startup

#pragma once

#include <vector>

#include <QByteArray>
#include <QString>
#include <QUrl>

typedef struct {
	QByteArray	    token;
	qint64		    userID;
	std::vector<qint64> activeChannels, *passiveChannels;
	QString		    username;
} USER_PROPERTIES_T;

typedef struct {
	QByteArray UID;
	QByteArray secret;
	QByteArray key;
} TOKEN_PARTS_T;

typedef struct {
	QString loginServer, rtcdServer, dlbServer, rtcdAuth, cloud;
} SERVERS_T;

typedef struct {
	QString dbName, cacheFolder;
} FILEPATHS_T;

inline SERVERS_T	 SERVERS;
inline FILEPATHS_T	 FILEPATHS;
inline TOKEN_PARTS_T	 TOKEN_PARTS;
inline USER_PROPERTIES_T USER_PROPERTIES
#ifdef QT_DEBUG
	{.token		  = "user"
			    ".1"
			    ".2b05fcb8258766a46792c0673da54f45f36430895fd1e84bc800bf2dcfdad20f773a"
			    "668e"
			    ".iRfM87XTe2G0290unVMYWY4C3Vq0k_OHYFdF6B7JfnM-Saqu",
	 .userID	  = 1,
	 .activeChannels  = {},
	 .passiveChannels = {},
	 .username	  = "justanothercatgirl"}
#endif
;
