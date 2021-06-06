#ifndef GAME_H
#define GAME_H

#include "Players.h"
#include "Ball.h"
#include "jsonConverter.h"

#include <QJsonObject>
#include <QObject>

class Game : public QObject, public QGraphicsPixmapItem, public jsonConverter
{
public:
    Game(QJsonObject);
    void show(int);
    void buildPlayer(int, int, QString);
public:
    QGraphicsScene *scene;
    Ball *ball = new Ball();
    Players *build = nullptr;
    QJsonObject jsonObj;
};

#endif // GAME_H
