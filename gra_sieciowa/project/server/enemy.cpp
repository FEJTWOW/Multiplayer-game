#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include <QDebug>

Enemy::Enemy()
{
    int randPos = rand() & 700;
    setPos(randPos, 0);
    setRect(0,0,100,100);
}
