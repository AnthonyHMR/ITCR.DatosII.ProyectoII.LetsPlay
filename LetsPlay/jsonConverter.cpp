#include "jsonConverter.h"

QByteArray jsonConverter::convert(QJsonObject obj)
{
    QByteArray data_json;
    QJsonDocument doc;

    doc.setObject(obj);
    data_json = doc.toJson();

    return data_json;
}

QJsonObject jsonConverter::getJsonObjectFromString(const QString jsonString) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if (jsonDocument.isNull()) {
        qDebug()<< "===> please check the string" << jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
