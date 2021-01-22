#include "bullet.h"
#include "obstacle.h"
#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

extern Game * newGame;

Bullet::Bullet()
{
    setRect(QRectF(newGame->settings->bullet_point, newGame->settings->bullet_size));

    //auto timer = new QTimer();
    //connect(timer,SIGNAL(timeout()), newGame, SLOT(newGame->checkAllCollistions()));
    //timer->start(newGame->settings->bullet_timer_in_ms);

    this->setBrush(newGame->settings->bullet_color);
    this->setPen(QPen(newGame->settings->bullet_color, 15, Qt::DashDotLine, Qt::RoundCap));    // TRZEBA JAKOS SAMEMU ZROBIC FAJNA GRAFIKE

}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid(*(colliding_items[i])) == typeid(Enemy))
        {
            //newGame->curr_score->increase();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Obstacle))
        {
            delete this;
            return;
        }
        else break;
    }

    setPos(x(), y()-newGame->settings->bullet_speed);
    if(pos().y() + rect().height() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
