#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <QDateTime>
#include <QDebug>
#include <QHash>
#include <QLayout>
#include <QString>
#include <QWidget>
#include <QtSystemDetection>

#include <optional>
#define DELETEPTR(pointer)                                                     \
	do {                                                                   \
		delete pointer;                                                \
		pointer = nullptr;                                             \
	} while (0)

QString getDateF();

inline void deleteLayoutWidgets(const QLayout *p)
{
	int	     i = 0;
	QLayoutItem *w;
	while (nullptr != (w = p->itemAt(i))) {
		if (!w->isEmpty()) delete w->widget();
	}
}

namespace MessageType
{

enum MessageType : unsigned short {
	// Administration
	ADMIN_CHANNELS_CREATE,
	ADMIN_CHANNELS_DELETE,
	ADMIN_CHANNELS_SETTINGS_EXTERNAL_NAME,
	ADMIN_CHANNELS_USERS_ADD,
	ADMIN_CHANNELS_USERS_REMOVE,
	// Account management
	USER_CHANNELS_JOIN,
	USER_CHANNELS_LEAVE,
	// Communication
	USER_CHANNELS_MESSAGES_POST_NEW,
	USER_CHANNELS_MESSAGES_POST_FOWARD_MESSAGE,
	USER_CHANNELS_MESSAGES_POST_FORWARD_POST,
	USER_CHANNELS_MESSAGES_EDIT,
	USER_CHANNELS_MESSAGES_DELETE,
	USER_CHANNELS_MESSAGES_REACTIONS_ADD,
	USER_CHANNELS_MESSAGES_REACTIONS_REMOVE,
	// System
	SYSTEM_CHANNELS_LISTEN_ADD,
	SYSTEM_CHANNELS_LISTEN_REMOVE,

	LAST_ELEMENT
};

// THESE MUST BE IN THE SAME ORDER AS MESSAGE_TYPE
constexpr const char *types[] = {
    // Administration
    "ADMIN-CHANNELS-CREATE",
    "ADMIN-CHANNELS-DELETE",
    "ADMIN-CHANNELS-SETTINGS-EXTERNAL-NAME",
    "ADMIN-CHANNELS-USERS-ADD",
    "ADMIN-CHANNELS-USERS-REMOVE",
    // Account management
    "USER-CHANNELS-JOIN",
    "USER-CHANNELS-LEAVE",
    // Communication
    "5CF", // TODO: change everything to hexadecimal
    "USER-CHANNELS-MESSAGES-POST-FOWARD-MESSAGE",
    "USER-CHANNELS-MESSAGES-POST-FORWARD-POST",
    "USER-CHANNELS-MESSAGES-EDIT",
    "USER-CHANNELS-MESSAGES-DELETE",
    "USER-CHANNELS-MESSAGES-REACTIONS-ADD",
    "USER-CHANNELS-MESSAGES-REACTIONS-REMOVE",
    // System
    "SYSTEM-CHANNELS-LISTEN-ADD",
    "SYSTEM-CHANNELS-LISTEN-REMOVE",
};

QHash<const char *, MessageType>  init_hash();
QHash<const char *, MessageType> &get_map();

std::optional<MessageType> toMessageType(QString type);
QString			   toString(MessageType type);

} // namespace MessageType

#endif // MISC_FUNCTIONS_H
