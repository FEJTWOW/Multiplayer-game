#include "game.h"

Game::Game(QWidget *parent)
{
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

    // Create a player object
    player = new Player();
    // Set players x,y,h,w
    player->setRect(0,0,100,100);
    player->setPos(width()/2, height()-player->rect().height());
    // Make player capable of receiving keyEvents
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // Add the player to the scene
    graphicsScene->addItem(player);

    // Create player score
    curr_score = new Score();
    graphicsScene->addItem(curr_score);





    auto timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);

    show();
}
