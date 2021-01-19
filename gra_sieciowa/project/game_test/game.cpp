#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    numOfPlayers = 0;
}

void Game::initGame()
{
    qDebug() << "1";
    // Create the game map
    graphicsScene = new QGraphicsScene();
    // Set the size of the map
    graphicsScene->setSceneRect(0,0,800,600);
    // Create our view
    setScene(graphicsScene);
    // Disable sidebars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set the size of the view
    setFixedSize(800,600);
    qDebug() << "2";

}

void Game::addNewPlayer(int x, int y, int w, int h)
{

    // A theoretical method to abstract from a single player concept

    players.append(new Player(x,y,w,h));
    players[numOfPlayers]->takeOver();
    qDebug() << "4";
    graphicsScene->addItem(players[numOfPlayers]);
    qDebug() << "5";
    playerScores.append(new Score());
    playerScores[numOfPlayers]->setupScore();

    qDebug() << "6";
    graphicsScene->addItem(playerScores[numOfPlayers]);
    qDebug() << "17";
    //curr_score = new Score();
    // Create player score
    //numOfPlayers++;



    auto timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), players[numOfPlayers], SLOT(spawn()));
    timer->start(2000);

    show();

}
