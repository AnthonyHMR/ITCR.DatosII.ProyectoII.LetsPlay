#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "Request.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>

class jsonConverter
{
public:
    QByteArray convert(QJsonObject);
    QJsonObject getJsonObjectFromString(const QString);
    QJsonArray readResultsJson(QJsonObject);
    Request *request = new Request();
private:
    QString fileName;
};

#endif // JSONCONVERTER_H
