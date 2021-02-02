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
    this->setPos(newGame->settings->player_spawns[id]);

    this->setBrush(newGame->settings->player_color);
    //this->setPen(QPen(newGame->settings->player_color, 15, Qt::DashDotLine, Qt::RoundCap));

    auto timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(canShoot()));
    timer->start(newGame->settings->player_shot_cd_in_ms);

    verticalMove = 0;
    horizontalMove = 0;
}

void Player::canShoot()
{
    this->shotFired = false;
}

void Player::respawn()
{
    delete respawnTimer;
    dead = false;
    movementDirection[0] = false;
    movementDirection[1] = false;
    movementDirection[2] = false;
    movementDirection[3] = false;
    invulnerable = true;
    isShooting = false;

    invulTimer = new QTimer();
    connect(invulTimer,SIGNAL(timeout()), this, SLOT(resetInvulnerability()));
    invulTimer->start(newGame->settings->player_invul_time_in_ms);
    this->setOpacity(0.2);

    this->setPos(newGame->settings->player_spawns[id]);
    newGame->graphicsScene->addItem(this);
}

void Player::resetInvulnerability()
{
    this->setOpacity(1.0);
    delete invulTimer;
    invulnerable = false;
}

void Player::move(int speed) {
    qDebug() << "Ruch" << horizontalMove << verticalMove;
    this->moveBy(horizontalMove*speed, verticalMove*speed);

    if(pos().x() < 0)
        setPos(0, pos().y());
    else if(pos().x() + newGame->settings->player_size.width() > newGame->settings->screen_size.width())
       setPos(newGame->settings->screen_size.width() - newGame->settings->player_size.width(), pos().y());

    if(pos().y() < 0)
        setPos(pos().x(), 0);
    else if(pos().y() + newGame->settings->player_size.height() > newGame->settings->screen_size.height())
        setPos(pos().x(), newGame->settings->screen_size.height() - newGame->settings->player_size.height());
}
