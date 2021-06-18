#include "Path.h"

#include <qmath.h>
#include <QGraphicsScene>
#include <QDebug>

Path::Path(QJsonArray path)
{
    QJsonArray pos = path[0].toArray();
    pathArray = path;
    QJsonArray positions = pathArray[ind].toArray();

    setRect(0,0,1,1);
    setBrush(Qt::yellow);
    setPos(pos[0].toInt(), pos[1].toInt());

    posX = positions[0].toInt();
    posY = positions[1].toInt();



    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(100);
}

void Path::move()
{
    int STEP_SIZE = 5;
    double theta = rotation();

    double dy = STEP_SIZE * sin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * cos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    if(pos().y() + rect().height() < 0 or pos().x() + rect().width() < 0 or pos().y() + rect().height() > 420 or pos().x() + rect().width() > 630) {
        scene()->removeItem(this);
        delete(this);
        delete(timer);
    }
    if (x() >= posX){
        pathArray.removeFirst();

        if(pathArray.isEmpty()){
            delete(this);
            delete(timer);
        }else{
            QJsonArray positions = pathArray[ind].toArray();

            posX = positions[0].toInt();
            posY = positions[1].toInt();

            setDest();
        }
    }
}

void Path::setDest()
{
    QGraphicsRectItem *point = new QGraphicsRectItem();
    point->setRect(0,0,5,5);
    point->setPos(posX, posY);
    point->setBrush(Qt::white);
    scene()->addItem(point);

    QLineF ln(QPointF(x(), y()), QPointF(posX, posY));
    int angle = -1 * ln.angle();

    this->setRotation(angle);
}
