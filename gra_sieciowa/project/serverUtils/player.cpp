#include "player.h"

#include <QColor>

Player::Player(QPoint point, QSize size, int id) : id(id)
{
    this->setRect(QRectF(point, size));
    this->setPos(playerSpawns[id]);

    auto timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(canShoot()));
    timer->start(playerShotCd);

    verticalMove = 0;
    horizontalMove = 0;
}

void Player::canShoot()
{
    this->shotFired = false;
}

void Player::kill() {
    this->setPos({10000, 10000});
    this->score -= scoreKillValue;
    if(this->score < 0)
        this->score = 0;
    dead = true;
    respawnTimer = new QTimer(this);
    QObject::connect(respawnTimer, SIGNAL(timeout()), this, SLOT(onRespawn()));
    respawnTimer->start(respawnTime);
}

void Player::onRespawn()
{
    delete respawnTimer;
    dead = false;
    invulnerable = true;
    isShooting = false;

    invulTimer = new QTimer(this);
    connect(invulTimer,SIGNAL(timeout()), this, SLOT(resetInvulnerability()));
    invulTimer->start(playerInvulTime);
    this->setOpacity(playerInvulnerableOpacity);
    this->setPos(playerSpawns[id]);
    emit respawn(this);
}

void Player::resetInvulnerability()
{
    this->setOpacity(1.0);
    delete invulTimer;
    invulnerable = false;
}

void Player::move(int speed) {
    this->moveBy(horizontalMove*speed, verticalMove*speed);

    if(pos().x() < 0)
        setPos(0, pos().y());
    else if(pos().x() + playerSize.width() > screenSize.width())
       setPos(screenSize.width() - playerSize.width(), pos().y());

    if(pos().y() < 0)
        setPos(pos().x(), 0);
    else if(pos().y() + playerSize.height() > screenSize.height())
        setPos(pos().x(), screenSize.height() - playerSize.height());
}
