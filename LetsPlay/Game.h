#ifndef GAME_H
#define GAME_H

#include "Players.h"
#include "Ball.h"
#include "jsonConverter.h"
#include "Button.h"
#include "TcpClient.h"

#include <QJsonObject>
#include <QObject>

class Game : public QObject, public QGraphicsPixmapItem, public jsonConverter
{
    Q_OBJECT
public:
    Game(QJsonObject);
    void show(int);
    void buildPlayer(int, int, QString);
    void createButton();
public slots:
    void play();
public:
    QGraphicsScene *scene;
    Ball *ball;
    Players *build = nullptr;
    QJsonObject jsonObj;
    Button *playButton;
private:
    int numPlayers;
    QStringList posX;
    QStringList posY;
};

#endif // GAME_H
