#include "Game.h"
#include "TcpClient.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QJsonArray>

Game::Game(QJsonObject mode)
{
    jsonObj = mode;
}

void Game::show(int nPlayers)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,630,420);
    scene->setBackgroundBrush(QBrush(QImage(":/images/field.jpg")));

    QStringList positions;

    scene->addItem(ball);

    QStringList posX;
    posX << "120" << "485" << "120" << "485" << "150" << "455" << "150" << "455" << "180" << "425" << "240" << "365" << "240" << "365";

    QStringList posY;
    posY << "140" << "240" << "50" << "330" << "190" << "130" << "250";

    QJsonArray arrayObj;
    QJsonObject obj;

    int count = 0;
    for (int i=0; i < nPlayers*2; i++) {
        if ((i+1)%2 != 0) {
            buildPlayer(posX[i].toInt(), posY[count].toInt(), ":/images/germany.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/10);
            obj["PosY"] = posY[count].toInt()/10;
            obj["Team"] = 1;
        }else{
            buildPlayer(posX[i].toInt(), posY[count].toInt(), ":/images/brazil.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/10);
            obj["PosY"] = posY[count].toInt()/10;
            obj["Team"] = 2;
            count++;
        }
        arrayObj.append(obj);
    }
    jsonObj["Players"] = arrayObj;

    TcpClient *client = new TcpClient();
    client->sendMessage(jsonConverter::convert(jsonObj));

    //add a view
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //show the view
    view->show();
    view->setFixedSize(630,420);
}

void Game::buildPlayer(int x, int y, QString image)
{
    build = new Players(x, y, image);
    scene->addItem(build);
    build = nullptr;
}
