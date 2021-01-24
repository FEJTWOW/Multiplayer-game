#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * newGame;

Obstacle::Obstacle(QPoint point, QSize size)
{
    setPos(0,0);
    setRect(point.x(),point.y(),size.width(),size.height());
}
