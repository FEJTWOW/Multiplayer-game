#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include "bullet.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT};

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(QPoint x, QSize h, int id);
    bool movementDirection[4] = {false};
    int shootingDirection;
    bool shotFired = true;
    bool isShooting = false;
    bool dead = false;
    int id;
    QTimer * respawnTimer;
public slots:
    void canShoot();
    void respawn();
};

#endif // PLAYER_H
