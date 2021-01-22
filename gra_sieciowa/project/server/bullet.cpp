#include "bullet.h"
#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

extern Game * newGame;

Bullet::Bullet(QPointF moveSet, int player_id) : moveSet(moveSet), player_id(player_id)
{
    QSize bulletShape;
    if(moveSet.x()) // Going LEFT/RIGHT
    {
        bulletShape.setWidth(newGame->settings->bullet_size.height());
        bulletShape.setHeight(newGame->settings->bullet_size.width());
    }
    else
    {
        bulletShape.setWidth(newGame->settings->bullet_size.width());
        bulletShape.setHeight(newGame->settings->bullet_size.height());
    }
    setRect(QRectF(newGame->settings->bullet_point, bulletShape));
    this->setBrush(newGame->settings->bullet_color);
    this->setPen(QPen(newGame->settings->bullet_color, 15, Qt::DashDotLine, Qt::RoundCap));    // TRZEBA JAKOS SAMEMU ZROBIC FAJNA GRAFIKE
    // TODO: tutaj jeszcze zaleznie od moveSet wypada zmienic grafike bulleta (zeby lecial w dobra strone [;d])
}
