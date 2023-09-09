#include "widget.h"
#include "utils/properties.h"

#include <QApplication>
#include <QTranslator>

#include <cstring>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    for(int i = 0; i < argc; ++i)
    {
        if (!std::strcmp(argv[i], "-l"))
            SERVERS.loginServer = argv[++i];
        if (!std::strcmp(argv[i], "-w"))
            SERVERS.cdnServer = argv[++i];
    }

    DEBUG("this is savepoint" << SERVERS.cdnServer);

    Widget w;
    w.show();
    return a.exec();
}
