#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>

class jsonConverter
{
public:
    QByteArray convert(QJsonObject);
    QJsonObject getJsonObjectFromString(const QString);
};

#endif // JSONCONVERTER_H
