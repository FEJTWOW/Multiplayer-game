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
    QDataStream receivedStream(data);
    receivedGameState.extractFromDataStream(receivedStream);
    myPlayerId = receivedGameState.playerID;    // TODO usunac myPlayerID
    clearGameState();
    for(int i=0; i < receivedGameState.obstacleList.length(); i++)
    {
        this->gameState.obstacleList.append(receivedGameState.obstacleList[i]);
    }
    for(auto playerID : receivedGameState.playersInfoMap.keys()) {
        this->gameState.playersInfoMap[playerID] = receivedGameState.playersInfoMap[playerID];
    }
    for(int i =0; i < receivedGameState.bulletList.length(); i++)
    {
        this->gameState.bulletList.append(receivedGameState.bulletList[i]);
    }
    for(int i=0; i<receivedGameState.enemyList.length(); i++)
    {
        this->gameState.enemyList.append(receivedGameState.enemyList[i]);
    }
    renderGameState();
}

void ClientGame::clearGameState() {
      gameState.obstacleList.clear();
      gameState.bulletList.clear();
      gameState.enemyList.clear();

      gameState.playersInfoMap.clear();
}

void ClientGame::renderGameState()
{
    clientGraphicsScene->clear();
    for(QList<ObstacleInfo>::iterator i= gameState.obstacleList.begin(); i != gameState.obstacleList.end(); ++i)
    {
        QGraphicsRectItem* obstacle = new QGraphicsRectItem();
        obstacle->setRect(QRectF(i->pos, obstacleSize));
        clientGraphicsScene->addItem(obstacle);
    }
    for(auto playerID : gameState.playersInfoMap.keys())
    {
//        QPainter* painter = new QPainter();

        QGraphicsRectItem* player = new QGraphicsRectItem();
//        QImage boximg("../../../gra_sieciowa/project/wolf.jpeg");

//        painter->drawImage(QRectF(gameState.player[i].pos, playerSize), boximg);
//        player->paint(painter,0,this);
//        player->
        player->setRect(QRectF(gameState.playersInfoMap[playerID].pos, playerSize));
//        QBrush tempBrush;
//        tempBrush.setTexture(QPixmap("../../../gra_sieciowa/project/wolf2.png"));
        player->setBrush(player_colors[playerID]);
        clientGraphicsScene->addItem(player);
    }
    for(QList<BulletInfo>::iterator i= gameState.bulletList.begin(); i != gameState.bulletList.end(); ++i)
    {
        createBullet(i->pos);
    }
    for(QList<EnemyInfo>::iterator i= gameState.enemyList.begin(); i != gameState.enemyList.end(); ++i)
    {
        QGraphicsRectItem* enemy = new QGraphicsRectItem();
        enemy->setRect(QRectF(i->pos, enemySize));
        clientGraphicsScene->addItem(enemy);
    }

    showScore(gameState.playersInfoMap[this->myPlayerId].currentScore);
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
