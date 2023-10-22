#include "utils/misc_functions.h"

QString getDateF()
{
#ifdef Q_OS_LINUX
    FILE* date = popen("date +'%Y-%m-%d %H:%M:%S.%3N'", "r");
    char buffer[25] = {0};
    size_t length = 10;

    if (!date) goto shit_happened;
    fscanf(date, "%10s", buffer);
    buffer[length] = ' ';
    fscanf(date, "%12s", buffer + length + 1);
    return QString(buffer);

shit_happened:
    qDebug() << "DATE COULD NOT BE RETREIVED. USING 1970-01-01 00:00:00.000";
    pclose(date);
    return "1970-01-01 00:00:00.000";
#else
    return "";
#endif
}
