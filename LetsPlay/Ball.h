#ifndef BALL_H
#define BALL_H

#include "TcpClient.h"
#include "jsonConverter.h"

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class Ball : public TcpClient, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ball(QStringList, QStringList, int);
    void keyPressEvent(QKeyEvent *event);
    bool collide = false;
    QGraphicsRectItem *lvl1;
    QGraphicsRectItem *lvl2;
    QGraphicsRectItem *lvl3;
    QGraphicsRectItem *lvl4;
    QGraphicsRectItem *lvl5;
public slots:
    void move();
private:
    QTimer *timer;
    QStringList posX;
    QStringList posY;
    int count = 1;
    int nPlayers;
    int speed = 5;
    int id = 2;
    jsonConverter *json;
};

#endif // BALL_H
