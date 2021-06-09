#include "Ball.h"
#include "Players.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>

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
    if(event->key() == Qt::Key_Space){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(move()));

        timer->start(50);
    }
}

void Ball::move()
{
    setAcceptHoverEvents(false);
    // if bullet colides with enemy, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Players) and collide == true) {
            //increase the score
            //game->score->increase();

            int team;

            int ind;
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
            obj["shoot"] = shooter;

            TcpClient::sendMessage(json->convert(obj));

            if (count==nPlayers*2-1){
                count = 0;
                id = 1;
            }else {
                count++;
                id++;
            }

            delete(timer);
            return;
        }
    }

    //move bullet up
    setPos(x()+10, y());
    if(pos().y() + rect().height() < 0 or pos().x() + rect().width() < 0) {
        scene()->removeItem(this);
        this->setPos(0, 0);;
    }

    if (collide == true) {
        collide = false;
    }else{
        collide = true;
    }

}
