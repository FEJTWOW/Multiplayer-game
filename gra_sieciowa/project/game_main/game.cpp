#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QHostAddress>
#include <QtAlgorithms>


Game::Game(QWidget *parent)
{
}

void Game::initGame()
{
    sock = new ServerSocket(QHostAddress::LocalHost,12345, this);
    connect(sock, SIGNAL(newPlayerId(int)), this, SLOT(receivedPlayerId(int)));
    connect(sock, SIGNAL(newGameState(const QByteArray&)), this, SLOT(parseGameState(const QByteArray&)));

    settings = new Settings();
    clientGraphicsScene = new QGraphicsScene();
    clientGraphicsScene->setSceneRect(QRectF(settings->screen_point, settings->screen_size));
    setScene(clientGraphicsScene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(settings->screen_size);
    this->setFocus();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    PlayerAction action;
    action.key = event->key();
    action.mode = event->type();
    action.id = this->myPlayerId;

    sock->sendPlayerAction(action);
    // Player id (players[id]) will be received from the client through the socket
    // for now :
//    int player_id = 0;

//    if(!players[player_id]->dead)
//    {
//        if(event->key() == Qt::Key_Left)
//            players[player_id]->movementDirection[LEFT] = true;
//        else if(event->key() == Qt::Key_Right)
//            players[player_id]->movementDirection[RIGHT] = true;
//        else if(event->key() == Qt::Key_Up)
//            players[player_id]->movementDirection[UP] = true;
//        else if(event->key() == Qt::Key_Down)
//            players[player_id]->movementDirection[DOWN] = true;
//        else if(event->key() == Qt::Key_W)
//        {
//                players[player_id]->isShooting = true;
//                players[player_id]->shootingDirection = 0;
//        }
//        else if(event->key() == Qt::Key_A)
//        {
//                players[player_id]->isShooting = true;
//                players[player_id]->shootingDirection = 1;
//        }
//        else if(event->key() == Qt::Key_S)
//        {
//                players[player_id]->isShooting = true;
//                players[player_id]->shootingDirection = 2;
//        }
//        else if(event->key() == Qt::Key_D)
//        {
//                players[player_id]->isShooting = true;
//                players[player_id]->shootingDirection = 3;
//        }
//        else if(event->key() == Qt::Key_Escape)
//        {
//            exit(EXIT_SUCCESS);
//        }
//    }
    qDebug() << "Pressed:" << action.key << " " << action.mode << " " << action.id;
    //movePlayer();
}


void Game::keyReleaseEvent(QKeyEvent *event)
{
    PlayerAction action;
    action.key = event->key();
    action.mode = event->type();
    action.id = this->myPlayerId;

    sock->sendPlayerAction(action);
    // In final cut this would be changed on server based on clients sending input (not local keyEvents)
//    if(!players[0]->dead)
//    {
//        switch ( event->key() )
//        {
//        case Qt::Key_Up:
//            players[0]->movementDirection[UP] = 0;
//            break;
//        case Qt::Key_Left:
//            players[0]->movementDirection[LEFT] = 0;
//            break;
//        case Qt::Key_Down:
//            players[0]->movementDirection[DOWN] = 0;
//            break;
//        case Qt::Key_Right:
//            players[0]->movementDirection[RIGHT] = 0;
//            break;
//        case Qt::Key_W:
//        case Qt::Key_A:
//        case Qt::Key_S:
//        case Qt::Key_D:
//            players[0]->isShooting = false;
//            break;
//        }
//    }
    qDebug() << "Released:" << action.key << " " << action.mode << " " << action.id;
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
        this->gameState.enemy[i] = receivedGameState.enemy[i];
    }
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
        clientGraphicsScene->addItem(player);
    }
    for(int i =0; i< 25; i++)
    {
        if(gameState.bullet[i].pos.x() == 0 && gameState.bullet[i].pos.y() == 0)
            continue;

        QGraphicsRectItem* bullet = new QGraphicsRectItem();
        bullet->setRect(QRectF(gameState.bullet[i].pos, settings->bullet_size));
        clientGraphicsScene->addItem(bullet);
    }
    for(int i =0; i <10; i++)
    {
        if(gameState.enemy[i].pos.x() == 0 && gameState.enemy[i].pos.y() == 0)
            continue;

        QGraphicsRectItem* enemy = new QGraphicsRectItem();
        enemy->setRect(QRectF(gameState.enemy[i].pos, settings->enemy_size));
        clientGraphicsScene->addItem(enemy);
    }
}


void Game::receivedPlayerId(const int &id)
{
    myPlayerId = id;
}
