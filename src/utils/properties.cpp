#include "properties.h"
SERVERS_T SERVERS{"https://ru.gigacht.com", "wss://ru.gigacht.com", "https://???.com", ""};

USER_PROPERTIES_T USER_PROPERTIES
#ifdef QT_DEBUG
    {
        .token = "user"
                       ".1"
                       ".2b05fcb8258766a46792c0673da54f45f36430895fd1e84bc800bf2dcfdad20f773a668e"
                       ".iRfM87XTe2G0290unVMYWY4C3Vq0k_OHYFdF6B7JfnM-Saqu",
        .userID = 1,
        .activeChannels = {},
        .passiveChannels = {},
        .username = "justanothercatgirl"
    }
#endif
;
FILEPATHS_T FILEPATHS;
TOKEN_PARTS_T TOKEN_PARTS;
