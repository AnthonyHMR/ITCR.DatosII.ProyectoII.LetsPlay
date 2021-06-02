#ifndef GAME_H
#define GAME_H

#include <QJsonObject>
#include <QObject>
#include <QGraphicsPixmapItem>

class Game : public QObject, public QGraphicsPixmapItem
{
public:
    Game(QJsonObject);
    void show(int);
};

#endif // GAME_H
