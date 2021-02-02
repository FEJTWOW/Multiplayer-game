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
    QList <Bullet*> playerBullets;
    bool movementDirection[4] = {false};
    int shootingDirection;
    bool shotFired = true;
    bool isShooting = false;
    bool dead = false;
    bool invulnerable = false;
    int id;
    QTimer * respawnTimer;
    QTimer * invulTimer;

    int horizontalMove;
    int verticalMove;
    void move(int speed);

public slots:
    void canShoot();
    void respawn();
    void resetInvulnerability();
};

#endif // PLAYER_H
