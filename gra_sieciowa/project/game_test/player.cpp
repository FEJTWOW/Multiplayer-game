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


Player::Player(QPoint point, QSize size)
{
    this->setRect(QRectF(point, size));
    this->setPos(newGame->graphicsScene->width()/2, newGame->graphicsScene->height()-this->rect().height());

    this->setBrush(newGame->settings->player_color);
    this->setPen(QPen(newGame->settings->player_color, 15, Qt::DashDotLine, Qt::RoundCap));    // TRZEBA JAKOS SAMEMU ZROBIC FAJNA GRAFIKE

    //QString filename = ":/new/Player/PackmanPng"; // trzeba by miec wiele png, dla kazdego gracza, lub svg ze zmiennym kolorem
    //QImage image(filename);
    //QPixmap item( QPixmap::fromImage(image));
    //scene()->addPixmap(item);
    //this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    //this->setFocus();
    auto timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(canShoot()));
    timer->start(newGame->settings->player_shot_cd_in_ms);
}

void Player::takeOver()
{
    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();
}

void Player::canShoot()
{
    this->shotFired = false;
}
