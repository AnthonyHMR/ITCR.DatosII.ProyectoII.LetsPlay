#include "Game.h"
#include "TcpClient.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>

Game::Game()
{
    TcpClient *client = new TcpClient();
}

void Game::show()
{
    QGraphicsScene *scene = new QGraphicsScene();

    QGraphicsRectItem *rect = new QGraphicsRectItem();
    scene->addItem(rect);

    //add a view
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //show the view
    view->show();
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);
}
