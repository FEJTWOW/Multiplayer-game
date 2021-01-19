#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "game.h"
#include <QDebug>

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
        this->movementDirection[LEFT] = true;
    else if(event->key() == Qt::Key_Right && pos().x() + 100 < 800)
        this->movementDirection[RIGHT] = true;
    else if(event->key() == Qt::Key_Up  && pos().y() > 0)
        this->movementDirection[UP] = true;
    else if(event->key() == Qt::Key_Down  && pos().y() < 500)
        this->movementDirection[DOWN] = true;
    else if(event->key() == Qt::Key_Space)
    {
        auto newBullet = new Bullet();
        newBullet->setPos(x()+50,y()-51);
        newGame->graphicsScene->addItem(newBullet);
    }
    movePlayer();
}


void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key() )
    {
    case Qt::Key_Up:
        this->movementDirection[UP] = 0;
        break;
    case Qt::Key_Left:
        this->movementDirection[LEFT] = 0;
        break;
    case Qt::Key_Down:
        this->movementDirection[DOWN] = 0;
        break;
    case Qt::Key_Right:
        this->movementDirection[RIGHT] = 0;
        break;
    }
}



void Player::movePlayer() {
    if (this->movementDirection[UP] && this->movementDirection[RIGHT])
        setPos(x()+10, y()-10);
    else if (this->movementDirection[DOWN] && this->movementDirection[LEFT])
        setPos(x()-10, y()+10);
    else if (this->movementDirection[UP] && this->movementDirection[LEFT])
        setPos(x()-10, y()-10);
    else if (this->movementDirection[DOWN] && this->movementDirection[RIGHT])
        setPos(x()+10, y()+10);
    else if (this->movementDirection[RIGHT])
        setPos(x()+10, y());
    else if (this->movementDirection[LEFT])
        setPos(x()-10, y());
    else if (this->movementDirection[DOWN])
        setPos(x(), y()+10);
    else if (this->movementDirection[UP])
        setPos(x(), y()-10);
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
