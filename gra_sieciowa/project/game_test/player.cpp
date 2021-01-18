#include "player.h"
#include "bullet.h"
#include "enemy.h"

#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player()
{

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && pos().x() > 0)
    {
        setPos(x()-10, y());
    }
    else if(event->key() == Qt::Key_Right && pos().x() + 100 < 800)
    {
        setPos(x()+10, y());
    }
    else if(event->key() == Qt::Key_Up)
    {
        setPos(x(), y()-10);
    }
    else if(event->key() == Qt::Key_Down)
    {
        setPos(x(), y()+10);
    }
    else if(event->key() == Qt::Key_Space)
    {
        auto newBullet = new Bullet();
        newBullet->setPos(x()+50,y()-51);
        scene()->addItem(newBullet);
    }
}

void Player::spawn()
{
    auto new_enemy = new Enemy();
    scene()->addItem(new_enemy);
}
