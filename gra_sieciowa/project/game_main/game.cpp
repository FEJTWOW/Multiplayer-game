#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QHostAddress>
#include <QtAlgorithms>
#include <QTimer>

Game::Game(QWidget *parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30);
}

void Game::initGame()
{
    sock = new ServerSocket(QHostAddress::LocalHost,12345, this);
    connect(sock, SIGNAL(newPlayerId(int)), this, SLOT(receivedPlayerId(int)));
    connect(sock, SIGNAL(newGameState(const QByteArray&)), this, SLOT(parseGameState(const QByteArray&)));

    horizontal = 0;
    vertical = 0;
    shooting = 0;
    shootDirection = 0;

    settings = new Settings();
    clientGraphicsScene = new QGraphicsScene();
    clientGraphicsScene->setSceneRect(QRectF(settings->screen_point, settings->screen_size));
    setScene(clientGraphicsScene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(settings->screen_size);
    this->setFocus();
}

void Game::move() {
    int newHorizontal = 0;
    int newVertical = 0;
    int newShooting = 0;
    int newShootDirection = 0;

    if(keys[Qt::Key_Up])
        newVertical = -1;
    if(keys[Qt::Key_Down])
        newVertical = 1;
    if(keys[Qt::Key_Left])
        newHorizontal = -1;
    if(keys[Qt::Key_Right])
        newHorizontal = 1;
    if(keys[Qt::Key_W]) {
        newShooting = 1;
        newShootDirection = 0;
    }
    if(keys[Qt::Key_S]) {
        newShooting = 1;
        newShootDirection = 2;
    }
    if(keys[Qt::Key_A]) {
        newShooting = 1;
        newShootDirection = 1;
    }
    if(keys[Qt::Key_D]) {
        newShooting = 1;
        newShootDirection = 3;
    }

    if(horizontal != newHorizontal || vertical != newVertical || shooting != newShooting || shootDirection != newShootDirection) {
        vertical = newVertical;
        horizontal = newHorizontal;
        shooting = newShooting;
        shootDirection = newShootDirection;

        PlayerAction action;
        action.id = this->myPlayerId;
        action.horizontal = horizontal;
        action.vertical = vertical;
        action.shooting = shooting;
        action.shootDirection = shootDirection;
        sock->sendPlayerAction(action);
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
}


void Game::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
}

void Game::parseGameState(const QByteArray &data)
{
    GameState receivedGameState;
    memcpy(&receivedGameState,data.data(), sizeof(receivedGameState));
    for(int i=0; i < 20; i++)
    {
        this->gameState.obstacle[i] = receivedGameState.obstacle[i];
    }
    for(int i =0; i < 5; i++)
    {

        this->gameState.player[i] = receivedGameState.player[i];
    }
    for(int i =0; i < 25; i++)
    {
        this->gameState.bullet[i] = receivedGameState.bullet[i];
    }
    for(int i=0; i<25; i++)
    {
        //this->gameState.enemy[i] = receivedGameState.enemy[i];
    }
    //this->gameState.player[this->myPlayerId].currentScore = receivedGameState.player[this->myPlayerId].currentScore;
    renderGameState();
}

void Game::renderGameState()
{
    clientGraphicsScene->clear();
    for(int i=0; i < 20; i++)
    {

        QGraphicsRectItem* obstacle = new QGraphicsRectItem();
        obstacle->setRect(QRectF(gameState.obstacle[i].pos, settings->obstacle_size));
        //qDebug() << "Rendering: " << obstacle->rect().x() << " " << obstacle->rect().y();
        clientGraphicsScene->addItem(obstacle);
    }
    for(int i =0; i< 5; i++)
    {

        if(gameState.player[i].pos.x() == 0 && gameState.player[i].pos.y() == 0)
            continue;

        QGraphicsRectItem* player = new QGraphicsRectItem();
        player->setRect(QRectF(gameState.player[i].pos, settings->player_size));
        player->setBrush(settings->player_colors[gameState.player[i].id]);
        clientGraphicsScene->addItem(player);
    }
    for(int i =0; i< 25; i++)
    {
        if(gameState.bullet[i].pos.x() == 0 && gameState.bullet[i].pos.y() == 0)
            continue;

        createBullet(gameState.bullet[i].pos);
//        QGraphicsRectItem* bullet = new QGraphicsRectItem();
//        bullet->setRect(QRectF(gameState.bullet[i].pos, settings->bullet_size));
//        bullet->setBrush(settings->bullet_color);
//        bullet->setPen(QPen(settings->bullet_color, 15, Qt::DashDotLine, Qt::RoundCap));
//        clientGraphicsScene->addItem(bullet);
    }
    for(int i =0; i <10; i++)
    {
        if(gameState.enemy[i].pos.x() == 0 && gameState.enemy[i].pos.y() == 0)
            continue;

        QGraphicsRectItem* enemy = new QGraphicsRectItem();
        enemy->setRect(QRectF(gameState.enemy[i].pos, settings->enemy_size));
        clientGraphicsScene->addItem(enemy);
    }
//    qDebug() << "Received score: " << gameState.player[this->myPlayerId].currentScore;
     showScore(gameState.player[this->myPlayerId].currentScore);
}


void Game::receivedPlayerId(const int &id)
{
    myPlayerId = id;
}

void Game::showScore(int currentScore)
{
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPlainText(QString("Current score:") + QString::number(currentScore));
    io->setDefaultTextColor(settings->score_color);
    io->setFont(settings->score_font);
    this->clientGraphicsScene->addItem(io);
}

void Game::createBullet(QPointF pos)
{
    QGraphicsRectItem* bullet = new QGraphicsRectItem();
    bullet->setRect(QRectF(pos, settings->bullet_size));
    bullet->setBrush(settings->bullet_color);
    bullet->setPen(QPen(settings->bullet_color, 15, Qt::DashDotLine, Qt::RoundCap));
    clientGraphicsScene->addItem(bullet);
}
