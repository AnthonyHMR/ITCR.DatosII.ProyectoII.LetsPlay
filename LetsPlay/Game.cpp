#include "Game.h"
#include "TcpClient.h"
#include "Players.h"
#include "Ball.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QImage>
#include <QBrush>

Game::Game(QJsonObject obj)
{
    QByteArray data_json;
    QJsonDocument doc;

    doc.setObject(obj);
    data_json = doc.toJson();

    TcpClient *client = new TcpClient();
    client->sendMessage(data_json);
}

void Game::show(int nPlayers)
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,630,400);
    scene->setBackgroundBrush(QBrush(QImage(":/images/field.jpg")));


    Players *player = new Players();
    scene->addItem(player);

    Ball *ball = new Ball();
    scene->addItem(ball);

    //add a view
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //show the view
    view->show();
    view->setFixedSize(630,400);
}
