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
    playerScore = new Score();
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

    qDebug() << "Pressed:" << action.key << " " << action.mode << " " << action.id;
}


void Game::keyReleaseEvent(QKeyEvent *event)
{
    PlayerAction action;
    action.key = event->key();
    action.mode = event->type();
    action.id = this->myPlayerId;

    sock->sendPlayerAction(action);
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
    this->gameState.player[this->myPlayerId].currentScore = receivedGameState.player[this->myPlayerId].currentScore;
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
    qDebug() << gameState.player[this->myPlayerId].currentScore << " ESZKERE";
      this->playerScore->setupScore(gameState.player[this->myPlayerId].currentScore);
//    this->setPlainText(QString("Current score:") + QString::number(gameState.player[this->myPlayerId].currentScore));
//    newGame->playerScores[newGame->numOfPlayers]->setDefaultTextColor(newGame->settings->score_color);
//    newGame->playerScores[newGame->numOfPlayers]->setFont(newGame->settings->score_font);

}


void Game::receivedPlayerId(const int &id)
{
    myPlayerId = id;
}
