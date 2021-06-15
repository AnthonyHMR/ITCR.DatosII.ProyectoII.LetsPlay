#ifndef DIRECTION_H
#define DIRECTION_H

#include <QMouseEvent>
#include <QGraphicsView>

class Direction : QGraphicsView
{
public:
    Direction();
    void mousePressEvent(QMouseEvent *event);
};

#endif // DIRECTION_H
