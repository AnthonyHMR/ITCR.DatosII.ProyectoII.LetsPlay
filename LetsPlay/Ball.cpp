#include "Ball.h"
#include "Players.h"
#include "Game.h"
#include "crossBar.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <qmath.h>
#include <QMouseEvent>
#include <QDebug>

Ball::Ball(QStringList X, QStringList Y, int nP)
{
    posX = X;
    posY = Y;
    nPlayers = nP;

    setRect(0,0,12,12);
    setBrush(QImage(":/images/ball.jpg"));
    setPos(307, 195);
}

void Ball::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        QLineF ln(QPointF(x(), y()), shoot_dest);
        int angle = -1 * ln.angle();

        this->setRotation(angle);

        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(move()));

        timer->start(50);
    }else if(event->key() == Qt::Key_Up){
        if (changeColor == 1){
            lvl4->setBrush(Qt::green);
            speed += 3;
            changeColor++;
        }else if(changeColor == 2){
            lvl3->setBrush(Qt::yellow);
            speed += 3;
            changeColor++;
        }else if(changeColor == 3){
            lvl2->setBrush(Qt::red);
            speed += 3;
            changeColor++;
        }else{
            speed += 3;
            lvl1->setBrush(Qt::darkRed);
        }
    }
}

void Ball::move()
{
    setAcceptHoverEvents(false);

    // if bullet colides with enemy, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Players) and collide == true) {
            if(!multiplayer and maquina == true){
                conditionsSingleplayer(false);
            }else{
                conditionsMultiplayer(false);
            }
            return;
        }else if(typeid(*(colliding_items[i])) == typeid(crossBar) and collide == true){
            if(!multiplayer and maquina == true){
                conditionsSingleplayer(true);
            }else{
                conditionsMultiplayer(true);
            }
        }
    }

    int STEP_SIZE = speed;
    double theta = rotation();

    double dy = STEP_SIZE * sin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * cos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    if(pos().y() + rect().height() < 0 or pos().x() + rect().width() < 0 or pos().y() + rect().height() > 420 or pos().x() + rect().width() > 630) {
        if(!multiplayer and maquina == true){
            conditionsSingleplayer(false);
        }else{
            conditionsMultiplayer(false);
        }
    }

    if (collide == true) {
        collide = false;
    }else{
        collide = true;
    }

}

void Ball::createButton(bool mplayer)
{
    multiplayer = mplayer;

    playButton = new Button(QString("Play"), 200, 50);
    int bxPos = 200;
    int byPos = 300;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    scene()->addItem(playButton);
}

void Ball::play()
{
    QJsonObject obj;
    QJsonObject shooter;
    shooter["ID"] = 1;
    shooter["Team"] = 1;
    obj["Shoot"] = shooter;

    sendMessage(json->convert(obj));
    setPos(posX[0].toInt()+21, posY[0].toInt()+4);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    scene()->removeItem(playButton);
}

void Ball::conditionsSingleplayer(bool gol)
{
    qDebug() << "passed";
    int ind;
    int team;

    if ((count+1)%2 != 0) {
        ind = +21;
        team = 1;
    }else{
        ind = -13;
        team = 2;
    }
    this->setPos(posX[count].toInt()+ind, posY[count].toInt()+4);

    if(gol){
        if(team == 1) {
            if(score->increaseTeam1()){
                scene()->removeItem(this);
            }
        }else{
            if(score->increaseTeam2()){
                scene()->removeItem(this);
            }
        }
    }

    QJsonObject obj;
    QJsonObject shooter;
    shooter["ID"] = id;
    shooter["Team"] = team;
    obj["Shoot"] = shooter;

    TcpClient::sendMessage(json->convert(obj));

    if (count==nPlayers*2-1){
        count = 0;
        id = 1;
    }else {
        count++;
        id++;
    }

    changeColor = 1;
    speed = 10;
    lvl1->setBrush(Qt::white);
    lvl2->setBrush(Qt::white);
    lvl3->setBrush(Qt::white);
    lvl4->setBrush(Qt::white);

    delete(timer);

    QLineF ln(QPointF(x(), y()), QPointF(10, 200));
    int angle = -1 * ln.angle();

    this->setRotation(angle);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);

    if (maquina == true){
        maquina = false;
    }else{
        maquina = true;
    }
}

void Ball::conditionsMultiplayer(bool gol)
{
    int ind;
    int team;

    if ((count+1)%2 != 0) {
        ind = +21;
        team = 1;
    }else{
        ind = -13;
        team = 2;
    }
    this->setPos(posX[count].toInt()+ind, posY[count].toInt()+4);

    if(gol){
        if(team == 1) {
            if(score->increaseTeam1()){
                scene()->removeItem(this);
            }
        }else{
            if(score->increaseTeam2()){
                scene()->removeItem(this);
            }
        }
    }

    QJsonObject obj;
    QJsonObject shooter;
    shooter["ID"] = id;
    shooter["Team"] = team;
    obj["Shoot"] = shooter;

    TcpClient::sendMessage(json->convert(obj));

    if (count==nPlayers*2-1){
        count = 0;
        id = 1;
    }else {
        count++;
        id++;
    }

    changeColor = 1;
    speed = 5;
    lvl1->setBrush(Qt::white);
    lvl2->setBrush(Qt::white);
    lvl3->setBrush(Qt::white);
    lvl4->setBrush(Qt::white);

    delete(timer);

    if (maquina == true){
        maquina = false;
    }else{
        maquina = true;
    }
}

void Ball::setShootDest(QPointF destination)
{
    shoot_dest = destination;
}
