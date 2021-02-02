#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QColor>
#include <QTimer>
#include "bullet.h"
#include "gameSettings.h"


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

    void kill();
signals:
    void respawn(Player* player);

public slots:
    void canShoot();
    void onRespawn();
    void resetInvulnerability();
};

#endif // PLAYER_H
