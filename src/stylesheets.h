#ifndef GIGACHAT_STYLESHEETS_LINUX
#define GIGACHAT_STYLESHEETS_LINUX

#include <QString>

namespace StyleSheets
{

// Removing const to later implement themes
// TODO: implement themes
/*const*/ extern QString
    SVGBGSS,
    FailedAuthSS,
    LabelSS,
    CheckboxSS,
#ifdef QT_DEBUG
    MessageDBGSS,
#endif
    MessageSS,
    MessageSenderSS,
    MessageErrorSS
    ;

}

#endif //GIGACHAT_STYLESHEETS_LINUX
