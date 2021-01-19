#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * newGame;

Obstacle::Obstacle()
{
    int randsizeX = newGame->settings->obstacle_min_size + (rand() & newGame->settings->obstacle_max_size);
    int randsizeY = newGame->settings->obstacle_min_size + (rand() & newGame->settings->obstacle_max_size);
    int randposX = randsizeX + rand() % (newGame->settings->screen_size.width() - randsizeX);
    int randposY = randsizeY + rand() % (newGame->settings->screen_size.height() - randsizeY);
    setPos(randposX, randposY);
    setRect(0,0,randsizeX,randsizeY);
}
