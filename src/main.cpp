#include "widget.h"
#include "utils/properties.h"

#include <QApplication>
#include <QTranslator>

#include <cstring>

#ifdef QT_DEBUG
    #include "utils/misc_functions.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef QT_DEBUG
    qInfo() <<  ROOT_DIRECTORY << SHARE_DIRECTORY << BIN_DIRICTORY;
    qInfo() << "ME TRYING TO GET DATE: " << getDateF();
#endif

    for(int i = 0; i < argc; ++i)
    {
        if (!std::strcmp(argv[i], "-l"))
            SERVERS.loginServer = argv[++i];
        if (!std::strcmp(argv[i], "-w"))
            SERVERS.cdnServer = argv[++i];
    }

    Widget w;
    w.show();
    return a.exec();
}
