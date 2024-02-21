#include "utils/misc_functions.hpp"

QString getDateF()
{
#ifdef Q_OS_LINUX
	FILE  *date	  = popen("date +'%Y-%m-%d %H:%M:%S.%3N'", "r");
	char   buffer[25] = {0};
	size_t length	  = 10;

	if (!date) goto shit_happened;
	fscanf(date, "%10s", buffer);
	buffer[length] = ' ';
	fscanf(date, "%12s", buffer + length + 1);
	return QString(buffer);

shit_happened:
	qDebug()
	    << "DATE COULD NOT BE RETREIVED. USING 1970-01-01 00:00:00.000";
	pclose(date);
	return "1970-01-01 00:00:00.000";
#else
	auto time = QDateTime::currentDateTimeUtc();
	return time.toString("yyyy-dd-MM hh:mm:ss.zzz");
#endif
}

std::optional<MessageType::MessageType> MessageType::toMessageType(QString type)
{
	auto	    temp = type.toUtf8();
	const char *key	 = temp.constData();
	auto	   &map	 = get_map();
	if (!map.contains(key)) return std::nullopt;
	return std::make_optional(map[key]);
}
QString MessageType::toString(MessageType type)
{
	return types[static_cast<size_t>(
	    type)]; // TYPES DECLARATIONS MUST BE IN ORDER!
}

QHash<const char *, MessageType::MessageType> MessageType::init_hash()
{
	auto ret = QHash<const char *, MessageType>();
	for (unsigned short i = 0;
	     i < static_cast<unsigned short>(MessageType::LAST_ELEMENT);
	     ++i)
		ret.insert(types[i], static_cast<MessageType>(i));
	return ret;
}
QHash<const char *, MessageType::MessageType> &MessageType::get_map()
{
	static QHash<const char *, MessageType> reverse_map = init_hash();
	return reverse_map;
}
