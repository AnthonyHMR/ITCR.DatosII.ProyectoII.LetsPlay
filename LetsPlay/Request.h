#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QStringList>
#include <QJsonArray>

class Request
{
public:
    QJsonArray getPath();
    void setPath(QJsonArray);
private:
    QJsonArray Path;
};

#endif // REQUEST_H
