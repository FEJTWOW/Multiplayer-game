#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include <QDebug>

extern Game * newGame;

Enemy::Enemy()
{
    int randPos = rand() & 750;
    setRect(QRectF(QPoint(randPos, 0), newGame->settings->enemy_size));
}
