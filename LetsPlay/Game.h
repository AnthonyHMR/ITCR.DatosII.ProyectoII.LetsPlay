#ifndef GAME_H
#define GAME_H

#include "Players.h"
#include "Ball.h"
#include "jsonConverter.h"
#include "Button.h"
#include "TcpClient.h"
#include "Score.h"

#include <QJsonObject>
#include <QMouseEvent>
#include <QGraphicsView>

class Game : public QGraphicsView, public jsonConverter
{
public:
    Game(QJsonObject, int, int, int);
    void buildPlayer(int, int, QString);
    void mousePressEvent(QMouseEvent *event);
private:
    QGraphicsScene *scene;
    Ball *ball;
    Players *build = nullptr;
    QJsonObject jsonObj;
    int numPlayers;
    QStringList posX;
    QStringList posY;
};

#endif // GAME_H
