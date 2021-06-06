#include "Players.h"

#include <QTimer>
#include <QImage>
#include <QBrush>

Players::Players(int x, int y, QString image)
{
    setRect(0,0,20,20);
    setBrush(QImage(image));
    setPos(x, y);
}
