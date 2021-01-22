#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include "bullet.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT};

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(QPoint x, QSize h);
    Bullet * playerBullets;
    int bulletMax;
    bool movementDirection[4] = {false};
    bool shotFired = true;
    bool isShooting = false;
public slots:
    void takeOver();
    void canShoot();
};

#endif // PLAYER_H
