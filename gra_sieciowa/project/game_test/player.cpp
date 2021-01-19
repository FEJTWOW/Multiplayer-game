#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "game.h"

#include <QKeyEvent>
#include <QGraphicsScene>

extern Game * newGame;


Player::Player(int x, int y, int w, int h) : xPos(x), yPos(y)
{
    this->setRect(xPos,yPos,w,h);
    this->setPos(newGame->graphicsScene->width()/2, newGame->graphicsScene->height()-this->rect().height());
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
        newGame->graphicsScene->addItem(newBullet);
    }
}

void Player::spawn()
{
    // This needs to go
    auto new_enemy = new Enemy();
    scene()->addItem(new_enemy);
}

void Player::takeOver()
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}
