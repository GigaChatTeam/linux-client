#pragma once

#include <Qt>
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


template <typename T, typename...Ts>
concept is_one_of = (std::is_same<T, Ts>::value || ...);

template <typename T>
concept json_type = is_one_of<
    T,
    bool,
    int,
    qint64,
    double,
    QString,
    QJsonObject,
    QJsonArray
>;

template <json_type T>
std::optional<T> getJsonSafe(QString key, const QJsonObject& o)
{
    if (!o.contains(key))
        return std::nullopt;
    QJsonValue v = o.value(key);
    if(v.isNull() || v.isUndefined())
        return std::nullopt;

    QVariant var = v.toVariant();
    if constexpr (std::is_arithmetic_v<T>)
            return v.isBool() || v.isDouble()
                ? std::make_optional<T>(var.value<T>())
                : std::nullopt;
    else if constexpr (std::is_same_v<T, QString>)
            return v.isString()
                ? std::make_optional<T>(v.toString())
                : std::nullopt;
    else if constexpr (std::is_same_v<T, QJsonArray>)
            return v.isArray()
                ? std::make_optional<T>(v.toArray())
                : std::nullopt;
    else if constexpr (std::is_same_v<T, QJsonObject>)
            return v.isObject()
                ? std::make_optional<T>(v.toObject())
                : std::nullopt;
    return std::nullopt;
}
