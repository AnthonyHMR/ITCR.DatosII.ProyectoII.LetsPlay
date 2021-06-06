#ifndef BUILD_H
#define BUILD_H

#include <QGraphicsRectItem>
#include <QObject>

class BuildPlayer : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public slots:
    void BuildNewPlayer();
};

#endif // BUILD_H
