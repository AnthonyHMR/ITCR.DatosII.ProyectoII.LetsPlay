#include "Spawner.h"
#include "Players.h"

#include <QGraphicsScene>

void Spawner::spawnPlayers()
{
    Players *player = new Players();
    scene()->addItem(player);
}
