#include "Request.h"

QJsonArray Request::getPath() {
    return Path;
}

void Request::setPath(QJsonArray entry) {
    Path = entry;
}
