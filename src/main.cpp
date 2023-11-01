#include "widget.h"
#include "utils/properties.h"

// TODO: use these bad guys
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QApplication>
#include <QTranslator>
#include <QDir>

#include <cstring>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir shareDir(SHARE_DIRECTORY);
    if(!shareDir.exists())
        shareDir.mkpath(".");

    for(int i = 0; i < argc; ++i)
    {

        if(!std::strcmp(argv[i], "--help"))
        {
            qInfo() << "some help options";
            a.exit(0);
            return 0; //is this code reachable?
        }

        if (!std::strcmp(argv[i], "--login-server")   ||
            !std::strcmp(argv[i], "--auth-server"))
        {
            SERVERS.loginServer = argv[++i];
        }

        if (!std::strcmp(argv[i], "--rtcd-server")    ||
            !std::strcmp(argv[i], "--websocket-server"))
        {
            SERVERS.cdnServer = argv[++i];
        }

        if (!std::strcmp(argv[i], "--history-server") ||
            !std::strcmp(argv[i], "--load-server")    ||
            !std::strcmp(argv[i], "--history-load-server"))
        {
            SERVERS.hlbServer = argv[++i];
        }
    }

    Widget w;
    w.show();
    return a.exec();
}
