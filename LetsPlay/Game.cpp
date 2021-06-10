#include "Game.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QJsonArray>
#include <QGraphicsTextItem>

Game::Game(QJsonObject mode)
{
    jsonObj = mode;
}

void Game::show(int nPlayers)
{
    numPlayers = nPlayers;

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,630,420);
    scene->setBackgroundBrush(QBrush(QImage(":/images/field.jpg")));

    QStringList positions;

    QGraphicsRectItem *crossbar1 = new QGraphicsRectItem();
    crossbar1->setRect(0,0,15,55);
    crossbar1->setPos(26, 173);
    scene->addItem(crossbar1);

    QGraphicsRectItem *crossbar2 = new QGraphicsRectItem();
    crossbar2->setRect(0,0,15,55);
    crossbar2->setPos(584, 173);
    scene->addItem(crossbar2);

    posX << "120" << "485" << "120" << "485" << "150" << "455" << "150" << "455" << "180" << "425" << "240" << "365" << "240" << "365";
    posY << "140" << "140" << "240" << "240" << "50" << "50" << "330" << "330" << "190" << "190" << "130" << "130" << "250" << "250";

    ball = new Ball(posX, posY, nPlayers);
    scene->addItem(ball);

    ball->lvl1 = new QGraphicsRectItem();
    ball->lvl1->setRect(0,0,30,20);
    ball->lvl1->setPos(590, 17);
    ball->lvl1->setBrush(Qt::white);
    scene->addItem(ball->lvl1);

    ball->lvl2 = new QGraphicsRectItem();
    ball->lvl2->setRect(0,0,30,20);
    ball->lvl2->setPos(590, 37);
    ball->lvl2->setBrush(Qt::white);
    scene->addItem(ball->lvl2);

    ball->lvl3 = new QGraphicsRectItem();
    ball->lvl3->setRect(0,0,30,20);
    ball->lvl3->setPos(590, 57);
    ball->lvl3->setBrush(Qt::white);
    scene->addItem(ball->lvl3);

    ball->lvl4 = new QGraphicsRectItem();
    ball->lvl4->setRect(0,0,30,20);
    ball->lvl4->setPos(590, 77);
    ball->lvl4->setBrush(Qt::white);
    scene->addItem(ball->lvl4);

    ball->lvl5 = new QGraphicsRectItem();
    ball->lvl5->setRect(0,0,30,20);
    ball->lvl5->setPos(590, 97);
    ball->lvl5->setBrush(Qt::green);
    scene->addItem(ball->lvl5);

    QJsonArray arrayObj;
    QJsonObject obj;

    for (int i=0; i < nPlayers*2; i++) {
        if ((i+1)%2 != 0) {
            buildPlayer(posX[i].toInt(), posY[i].toInt(), ":/images/germany.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/10);
            obj["PosY"] = posY[i].toInt()/10;
            obj["Team"] = 1;
        }else{
            buildPlayer(posX[i].toInt(), posY[i].toInt(), ":/images/brazil.jpg");
            obj["ID"] = i+1;
            obj["PosX"] = abs(posX[i].toInt()/10);
            obj["PosY"] = posY[i].toInt()/10;
            obj["Team"] = 2;
        }
        arrayObj.append(obj);
    }
    jsonObj["Players"] = arrayObj;

    ball->Connect();
    ball->sendMessage(jsonConverter::convert(jsonObj));

    createButton();

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

void Game::createButton()
{
//    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Footbolin"));
//    QFont titleFont("comic sans", 50);
//    titleText->setFont(titleFont);
//    int txPos = 100;
//    int tyPos = 150;
//    titleText->setPos(txPos, tyPos);
//    scene->addItem(titleText);

    playButton = new Button(QString("Play"));
    int bxPos = 215;
    int byPos = 300;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    scene->addItem(playButton);
}

void Game::play()
{
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Footbolin"));
    QFont titleFont("comic sans", 15);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor("white");
    titleText->setPlainText("Cambio");

    int txPos = 30;
    int tyPos = 385;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    QJsonObject obj;
    QJsonObject shooter;
    shooter["ID"] = 1;
    shooter["Team"] = 1;
    obj["shoot"] = shooter;

    ball->sendMessage(jsonConverter::convert(obj));
    scene->addItem(ball);
    ball->setPos(posX[0].toInt()+21, posY[0].toInt()+4);
    ball->setFlag(QGraphicsItem::ItemIsFocusable);
    ball->setFocus();
    scene->removeItem(playButton);
}
