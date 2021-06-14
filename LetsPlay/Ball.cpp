#include "Ball.h"
#include "Players.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <qmath.h>

extern Game *game;

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
    shoot_dest = QPointF(300, 0);
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
            conditions();
            return;
        }
    }

    //move bullet up
    //setPos(x()+speed, y());
    int STEP_SIZE = speed;
    double theta = rotation();

    double dy = STEP_SIZE * sin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * cos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    if(pos().y() + rect().height() < 0 or pos().x() + rect().width() < 0 or pos().y() + rect().height() > 420 or pos().x() + rect().width() > 630) {
        conditions();
    }

    if (collide == true) {
        collide = false;
    }else{
        collide = true;
    }

}

void Ball::conditions()
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
}
