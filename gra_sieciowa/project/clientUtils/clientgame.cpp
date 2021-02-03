#include "clientgame.h"
#include <QDebug>
#include <QKeyEvent>
#include <QHostAddress>
#include <QtAlgorithms>
#include <QTimer>
#include <QPainter>

ClientGame::ClientGame(QWidget *parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30);
}

void ClientGame::initGame(const QHostAddress& address, quint16 port)
{
    sock = new ServerSocket(address,port, this);
    connect(sock, SIGNAL(newPlayerId(int)), this, SLOT(receivedPlayerId(int)));
    connect(sock, SIGNAL(newGameState(const QByteArray&)), this, SLOT(parseGameState(const QByteArray&)));

    horizontal = 0;
    vertical = 0;
    shooting = 0;
    shootDirection = 0;

    clientGraphicsScene = new QGraphicsScene();
    clientGraphicsScene->setSceneRect(QRectF(screenPoint, screenSize));
    setScene(clientGraphicsScene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenSize);
    this->setFocus();
}

void ClientGame::move() {
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

void ClientGame::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
}


void ClientGame::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
}

void ClientGame::parseGameState(const QByteArray &data)
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
    for(int i=0; i<10; i++)
    {
        this->gameState.enemy[i] = receivedGameState.enemy[i];
    }
    //this->gameState.player[this->myPlayerId].currentScore = receivedGameState.player[this->myPlayerId].currentScore;
    renderGameState();
}

void ClientGame::renderGameState()
{
    clientGraphicsScene->clear();
    for(int i=0; i < 20; i++)
    {

        QGraphicsRectItem* obstacle = new QGraphicsRectItem();
        obstacle->setRect(QRectF(gameState.obstacle[i].pos, obstacleSize));
        //qDebug() << "Rendering: " << obstacle->rect().x() << " " << obstacle->rect().y();
        clientGraphicsScene->addItem(obstacle);
    }
    for(int i =0; i< 5; i++)
    {

        if(gameState.player[i].pos.x() == 0 && gameState.player[i].pos.y() == 0)
            continue;
//        QPainter* painter = new QPainter();

        QGraphicsRectItem* player = new QGraphicsRectItem();
//        QImage boximg("../../../gra_sieciowa/project/wolf.jpeg");

//        painter->drawImage(QRectF(gameState.player[i].pos, playerSize), boximg);
//        player->paint(painter,0,this);
//        player->
        player->setRect(QRectF(gameState.player[i].pos, playerSize));
//        QBrush tempBrush;
//        tempBrush.setTexture(QPixmap("../../../gra_sieciowa/project/wolf2.png"));
        player->setBrush(player_colors[gameState.player[i].id]);
        clientGraphicsScene->addItem(player);
    }
    for(int i =0; i< 25; i++)
    {
        if(gameState.bullet[i].pos.x() == 0 && gameState.bullet[i].pos.y() == 0)
            continue;

        createBullet(gameState.bullet[i].pos);
    }
    for(int i =0; i <10; i++)
    {
        if(gameState.enemy[i].pos.x() == 0 && gameState.enemy[i].pos.y() == 0)
            continue;

        QGraphicsRectItem* enemy = new QGraphicsRectItem();
        enemy->setRect(QRectF(gameState.enemy[i].pos, enemySize));
        clientGraphicsScene->addItem(enemy);
    }
//    qDebug() << "Received score: " << gameState.player[this->myPlayerId].currentScore;
     showScore(gameState.player[this->myPlayerId].currentScore);
}


void ClientGame::receivedPlayerId(const int &id)
{
    myPlayerId = id;
}

void ClientGame::showScore(int currentScore)
{
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPlainText(QString("Current score:") + QString::number(currentScore));
    io->setDefaultTextColor(scoreColor);
    io->setFont(scoreFont);
    this->clientGraphicsScene->addItem(io);
}

void ClientGame::createBullet(QPointF pos)
{
    QGraphicsRectItem* bullet = new QGraphicsRectItem();
    bullet->setRect(QRectF(pos, bulletSize));
    bullet->setBrush(bulletColor);
    bullet->setPen(QPen(bulletColor, 15, Qt::DashDotLine, Qt::RoundCap));
    clientGraphicsScene->addItem(bullet);
}
