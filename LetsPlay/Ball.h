#ifndef BALL_H
#define BALL_H

#include "TcpClient.h"
#include "jsonConverter.h"
#include "Button.h"
#include "Score.h"

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QPointF>

class Ball : public TcpClient, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ball(QStringList, QStringList, int);
    bool collide = false;
    QGraphicsRectItem *lvl1;
    QGraphicsRectItem *lvl2;
    QGraphicsRectItem *lvl3;
    QGraphicsRectItem *lvl4;
    QGraphicsRectItem *lvl5;
    void createButton(bool);
    void setShootDest(QPointF);
    Score *score;
    jsonConverter *json;
private:
    void conditionsMultiplayer(bool);
    void conditionsSingleplayer(bool);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void move();
    void play();
private:
    QTimer *timer;
    QStringList posX;
    QStringList posY;
    int count = 1;
    int nPlayers;
    int changeColor = 1;
    int speed = 5;
    int id = 2;
    QPointF shoot_dest;
    Button *playButton;

    Button *pathButton;
    bool multiplayer;
    bool maquina = true;
};

#endif // BALL_H
