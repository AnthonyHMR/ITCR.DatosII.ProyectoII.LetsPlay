#ifndef PATH_H
#define PATH_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QJsonArray>
#include <QObject>
#include <QPointF>

class Path : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Path(QJsonArray);
public slots:
    void move();
private:
    QTimer *timer;
    int posX;
    int posY;
    QJsonArray pathArray;
    int ind = 1;
    void setDest();
};

#endif // PATH_H
