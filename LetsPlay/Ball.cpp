#include "Ball.h"
#include "Players.h"

#include <QGraphicsScene>

Ball::Ball()
{
    setRect(0,0,30,30);

    setPos(250, 250);
}

void Ball::spawnPlayers()
{
    Players *player = new Players();
    scene()->addItem(player);
}


