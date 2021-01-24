#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * newGame;

Obstacle::Obstacle(QPoint point, QSize size)
{
    setRect(point.x(),point.y(),size.width(),size.height());
}
