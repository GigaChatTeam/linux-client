#include "widget.h"
#include "utils/properties.h"

#include <QApplication>
#include <QTranslator>
#include <QDir>

#include <cstring>

#ifdef QT_DEBUG
    #include "utils/misc_functions.h"
//    #ifdef SHARE_DIRECTORY
//        #undef SHARE_DIRECTORY
//        #define SHARE_DIRECTORY "/home/main/coding/linux-client/build/Debug/share"
//    #endif
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir shareDir(SHARE_DIRECTORY);
    if(!shareDir.exists())
        shareDir.mkpath(".");

#ifdef QT_DEBUG
    qInfo() << "ROOT DIRECTORY\t\t" << "SHARE_DIRECTORY\t\t" << "BIN DIRECTORY\t\t";
    qInfo() <<  ROOT_DIRECTORY<<"\t\t"<<SHARE_DIRECTORY<<"\t\t"<<BIN_DIRICTORY;
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
