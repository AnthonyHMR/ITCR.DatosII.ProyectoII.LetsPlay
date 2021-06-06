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
    posX << "55" << "550" << "125" << "480" << "125" << "480" << "155" << "450" << "155" << "450" << "185" << "420" << "245" << "360" << "245" << "360";

    QStringList posY;
    posY << "190" << "140" << "240" << "50" << "330" << "190" << "140" << "240";

    QJsonArray arrayObj;
    QJsonObject obj;

    int count = 0;
    for (int i=0; i < nPlayers*2; i++) {
        if ((i+1)%2 != 0) {
            buildPlayer(posX[i].toInt(), posY[count].toInt(), ":/images/germany.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = posX[i];
            obj["PosY"] = posY[count];
            obj["Team"] = 1;
        }else{
            buildPlayer(posX[i].toInt(), posY[count].toInt(), ":/images/brazil.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = posX[i];
            obj["PosY"] = posY[count];
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
