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
			SERVERS.cdnServer = argv[++i];
		}

		if (!std::strcmp(argv[i], "--history-server") ||
		    !std::strcmp(argv[i], "--load-server") ||
		    !std::strcmp(argv[i], "--history-load-server")) {
			SERVERS.hlbServer = argv[++i];
		}
		if (!std::strcmp(argv[i], "--token-server")) {
			SERVERS.tokengenServer = argv[++i];
		}
	}

	Widget w;
	w.show();
	int status_code = a.exec();
	return status_code;
}
