#include "Ball.h"
#include "Players.h"
#include "Game.h"

#include <QGraphicsScene>

extern Game *game;

Ball::Ball()
{
    setRect(0,0,12,12);
    setBrush(QImage(":/images/ball.jpg"));
    setPos(350, 190);
}


