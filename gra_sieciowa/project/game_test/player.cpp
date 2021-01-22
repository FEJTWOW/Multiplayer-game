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


Player::Player(QPoint point, QSize size, int id) : id(id)
{
    this->setRect(QRectF(point, size));
    //this->setPos(125, newGame->settings->screen_size.height()-newGame->settings->player_size.height());
    this->setPos(newGame->settings->player_spawns[id]);

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

void Player::canShoot()
{
    this->shotFired = false;
}

void Player::respawn()
{
    qDebug() << "Doing respawn!";
    delete respawnTimer;
    dead = false;
    movementDirection[0] = false;
    movementDirection[1] = false;
    movementDirection[2] = false;
    movementDirection[3] = false;
    this->setPos(newGame->settings->player_spawns[id]);
    newGame->graphicsScene->addItem(this);
    qDebug() << "Respawned!";
}
