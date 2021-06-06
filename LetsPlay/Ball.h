#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QObject>

class Ball : public QObject, public QGraphicsRectItem
{
public:
    Ball();
};

#endif // BALL_H
