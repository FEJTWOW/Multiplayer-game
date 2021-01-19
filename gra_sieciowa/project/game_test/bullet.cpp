#include "bullet.h"
#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

extern Game * newGame;

Bullet::Bullet()
{
    setRect(0,0,10,50);

    auto timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        qDebug() << "XD";

        if(typeid(*(colliding_items[i])) == typeid(Enemy))
        {
            //qDebug() << "XD1";
            //newGame->curr_score->increase();
            qDebug() << "XD1.1";
            scene()->removeItem(colliding_items[i]);
            qDebug() << "XD1.2";
            scene()->removeItem(this);
            qDebug() << "XD2";
            delete colliding_items[i];
            delete this;
            return;
        }
        else
        {
            break;
        }
    }

    setPos(x(), y()-10);
    if(pos().y() + rect().height() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
