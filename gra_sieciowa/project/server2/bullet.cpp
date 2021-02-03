#include "bullet.h"
#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Bullet::Bullet(int direction, int player_id, const QPointF& playerPos) : direction(direction), player_id(player_id)
{
    QSize bulletShape = bullet_size;

    if(direction == 1 || direction == 3)
        bulletShape.transpose();

    QColor color = Qt::blue;

    setRect(QRectF(bullet_point, bulletShape));

    switch (direction) {
        case 0:
            setPos(playerPos.x()+(player_size.width()/2)-(bullet_size.width()/2),playerPos.y()-(player_size.height()+1));
            break;
        case 1:
            //setPos(playerPos.x()-player->rect().width() -1, player->y() + player->rect().height()/2);
            setPos(playerPos.x() - player_size.width() -1, playerPos.y() + player_size.height()/2);
            break;
        case 2:
            //newBullet->setPos(player->x()+(this->settings->player_size.width()/2),player->y()+(this->settings->player_size.height()+12));           // ??????
            setPos(playerPos.x()+(player_size.width()/2)-(bullet_size.width()/2),playerPos.y()+(player_size.height()+1));
            break;
        case 3:
            setPos(playerPos.x() + 2*player_size.width() -1, playerPos.y() + player_size.height()/2);
            //newBullet->setPos(player->x()+settings->player_size.width()+12, player->y() +settings->player_size.height()/2 + 1);         // Needs fixing
            break;
        default:
            break;
    }

    this->setBrush(color);
    this->setPen(QPen(color, 15, Qt::DashDotLine, Qt::RoundCap));
}

void Bullet::move() {
    switch(direction) {
        case 0:
            moveBy(0, -bullet_speed);
            break;
        case 1:
            moveBy(-bullet_speed, 0);
            break;
        case 2:
            moveBy(0, bullet_speed);
            break;
        case 3:
            moveBy(bullet_speed, 0);
            break;
    }
}
