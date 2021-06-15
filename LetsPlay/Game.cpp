#include "Game.h"
#include "crossBar.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QJsonArray>
#include <QGraphicsTextItem>
#include <QDebug>

Game::Game(QJsonObject mode, int nPlayers, int maxGoals)
{
    jsonObj = mode;

    numPlayers = nPlayers;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,610,410);
    scene->setBackgroundBrush(QBrush(QImage(":/images/field.jpg")));
    setScene(scene);

    QStringList positions;

    crossBar *crossbar1 = new crossBar(10, 173);
    scene->addItem(crossbar1);

    crossBar *crossbar2 = new crossBar(570, 173);
    scene->addItem(crossbar2);

    posX << "100" << "485" << "100" << "485" << "130" << "455" << "130" << "455" << "160" << "425" << "220" << "365" << "220" << "365";
    posY << "140" << "140" << "240" << "240" << "50" << "50" << "330" << "330" << "190" << "190" << "130" << "130" << "250" << "250";

    ball = new Ball(posX, posY, nPlayers);
    scene->addItem(ball);

    ball->lvl1 = new QGraphicsRectItem();
    ball->lvl1->setRect(0,0,30,20);
    ball->lvl1->setPos(575, 17);
    ball->lvl1->setBrush(Qt::white);
    scene->addItem(ball->lvl1);

    ball->lvl2 = new QGraphicsRectItem();
    ball->lvl2->setRect(0,0,30,20);
    ball->lvl2->setPos(575, 37);
    ball->lvl2->setBrush(Qt::white);
    scene->addItem(ball->lvl2);

    ball->lvl3 = new QGraphicsRectItem();
    ball->lvl3->setRect(0,0,30,20);
    ball->lvl3->setPos(575, 57);
    ball->lvl3->setBrush(Qt::white);
    scene->addItem(ball->lvl3);

    ball->lvl4 = new QGraphicsRectItem();
    ball->lvl4->setRect(0,0,30,20);
    ball->lvl4->setPos(575, 77);
    ball->lvl4->setBrush(Qt::white);
    scene->addItem(ball->lvl4);

    ball->lvl5 = new QGraphicsRectItem();
    ball->lvl5->setRect(0,0,30,20);
    ball->lvl5->setPos(575, 97);
    ball->lvl5->setBrush(Qt::darkGreen);
    scene->addItem(ball->lvl5);

    QJsonArray arrayObj;
    QJsonObject obj;

    for (int i=0; i < nPlayers*2; i++) {
        if ((i+1)%2 != 0) {
            buildPlayer(posX[i].toInt(), posY[i].toInt(), ":/images/germany.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/20);
            obj["PosY"] = posY[i].toInt()/20;
            obj["Team"] = 1;
        }else{
            buildPlayer(posX[i].toInt(), posY[i].toInt(), ":/images/brazil.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/20);
            obj["PosY"] = posY[i].toInt()/20;
            obj["Team"] = 2;
        }
        arrayObj.append(obj);
    }
    jsonObj["Players"] = arrayObj;

    ball->Connect();
    ball->sendMessage(jsonConverter::convert(jsonObj));

    ball->createButton();

    ball->score = new Score(maxGoals);
    scene->addItem(ball->score);

    setFixedSize(610,410);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::buildPlayer(int x, int y, QString image)
{
    build = new Players(x, y, image);
    scene->addItem(build);
    build = nullptr;
}

void Game::mousePressEvent(QMouseEvent *event)
{
    ball->setShootDest(event->pos());
}
