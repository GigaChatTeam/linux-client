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

#include "utils/misc_functions.hpp"
#include "utils/properties.hpp"
#include "ui/widget.hpp"

// TODO: use these bad guys
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDir>
#include <QTranslator>
#include <cstring>

#ifndef SHARE_DIRECTORY
#define SHARE_DIRECTORY "~/.local/share/gigachat"
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QDir shareDir(SHARE_DIRECTORY);
	if (!shareDir.exists()) shareDir.mkpath(".");

	for (int i = 0; i < argc; ++i) {
		if (!std::strcmp(argv[i], "--help")) {
			qInfo() << "some help options";
			a.exit(0);
		}

		if (!std::strcmp(argv[i], "--login-server") ||
		    !std::strcmp(argv[i], "--auth-server")) {
			SERVERS.loginServer = argv[++i];
		}

		if (!std::strcmp(argv[i], "--rtcd-server") ||
		    !std::strcmp(argv[i], "--websocket-server")) {
			SERVERS.rtcdServer = argv[++i];
		}

		if (!std::strcmp(argv[i], "--history-server") ||
		    !std::strcmp(argv[i], "--load-server") ||
		    !std::strcmp(argv[i], "--history-load-server")) {
			SERVERS.dlbServer = argv[++i];
		}
		if (!std::strcmp(argv[i], "--token-server")) {
			SERVERS.rtcdAuth = argv[++i];
		}
	}

	Widget w;
	w.show();
	int status_code = a.exec();
	return status_code;
}
