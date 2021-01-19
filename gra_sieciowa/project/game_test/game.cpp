#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    numOfPlayers = 0;
}

void Game::initGame()
{
    settings = new Settings();
    // Create the game map
    graphicsScene = new QGraphicsScene();
    // Set the size of the map
    graphicsScene->setSceneRect(QRectF(settings->screen_point, settings->screen_size));
    // Create our view
    setScene(graphicsScene);
    // Disable sidebars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set the size of the view
    setFixedSize(settings->screen_size);

}

void Game::addNewPlayer(QPoint point, QSize size)
{
    // This does not really use the given arguments. (raeds from settings for now)
    // A theoretical method to abstract from a single player concept

    players.append(new Player(settings->player_point, settings->player_size));
    players[numOfPlayers]->takeOver();
    graphicsScene->addItem(players[numOfPlayers]);
    playerScores.append(new Score());
    playerScores[numOfPlayers]->setupScore();

    graphicsScene->addItem(playerScores[numOfPlayers]);
    //numOfPlayers++;

    auto timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), players[numOfPlayers], SLOT(spawn()));
    timer->start(2000);

    show();

}
