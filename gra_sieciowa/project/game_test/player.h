#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include "bullet.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(int x, int y, int w, int h);
    void keyPressEvent(QKeyEvent * event);
    Bullet * playerBullets;
    int bulletMax;
    int xPos;
    int yPos;
    int movingX, movingY;
public slots:
    void spawn();
    void takeOver();
};

#endif // PLAYER_H
