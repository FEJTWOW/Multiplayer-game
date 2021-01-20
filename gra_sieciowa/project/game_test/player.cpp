#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "game.h"
#include <QDebug>

#include <QKeyEvent>
#include <QGraphicsScene>
#include <settings.h>

extern Game * newGame;


Player::Player(QPoint point, QSize size) : xPos(point.x()), yPos(point.y())
{
    this->setRect(QRectF(point, size));
    this->setPos(newGame->graphicsScene->width()/2, newGame->graphicsScene->height()-this->rect().height());

    this->setBrush(Qt::cyan);
    this->setPen(QPen(Qt::cyan, 15, Qt::DashDotLine, Qt::RoundCap));    // TRZEBA JAKOS SAMEMU ZROBIC FAJNA GRAFIKE

    //QString filename = ":/new/Player/PackmanPng"; // trzeba by miec wiele png, dla kazdego gracza, lub svg ze zmiennym kolorem
    //QImage image(filename);
    //QPixmap item( QPixmap::fromImage(image));
    //scene()->addPixmap(item);
    //this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    //this->setFocus();
}




void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && pos().x() > 0)
        this->movementDirection[LEFT] = true;
    else if(event->key() == Qt::Key_Right && pos().x() + newGame->settings->player_size.width() < newGame->settings->screen_size.width())
        this->movementDirection[RIGHT] = true;
    else if(event->key() == Qt::Key_Up  && pos().y() > 0)
        this->movementDirection[UP] = true;
    else if(event->key() == Qt::Key_Down  && pos().y() + newGame->settings->player_size.height() < newGame->settings->screen_size.height())
        this->movementDirection[DOWN] = true;
    else if(event->key() == Qt::Key_Space)
    {
        auto newBullet = new Bullet();
        newBullet->setPos(x()+(newGame->settings->player_size.width()/2),y()-(newGame->settings->player_size.height()+1));
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
        setPos(x()+newGame->settings->player_speed, y()-newGame->settings->player_speed);
    else if (this->movementDirection[DOWN] && this->movementDirection[LEFT] && pos().x() > 0 && pos().y() + newGame->settings->player_size.height() < newGame->settings->screen_size.height())
        setPos(x()-newGame->settings->player_speed, y()+newGame->settings->player_speed);
    else if (this->movementDirection[UP] && this->movementDirection[LEFT] && pos().x() > 0)
        setPos(x()-newGame->settings->player_speed, y()-newGame->settings->player_speed);
    else if (this->movementDirection[DOWN] && this->movementDirection[RIGHT] && pos().x() + newGame->settings->player_size.width() < newGame->settings->screen_size.width() && pos().y() + newGame->settings->player_size.height() < newGame->settings->screen_size.height())
        setPos(x()+newGame->settings->player_speed, y()+newGame->settings->player_speed);
    else if (this->movementDirection[RIGHT] && pos().x() + newGame->settings->player_size.width() < newGame->settings->screen_size.width())
        setPos(x()+newGame->settings->player_speed, y());
    else if (this->movementDirection[LEFT] && pos().x() > 0)
        setPos(x()-newGame->settings->player_speed, y());
    else if (this->movementDirection[DOWN] && pos().x() > 0 && pos().y() + newGame->settings->player_size.height() < newGame->settings->screen_size.height())
        setPos(x(), y()+newGame->settings->player_speed);
    else if (this->movementDirection[UP] && pos().x() > 0)
        setPos(x(), y()-newGame->settings->player_speed);
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
