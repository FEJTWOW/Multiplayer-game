#include "game.h"
#include <QDebug>
#include <QKeyEvent>


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

    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
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

void Game::generateObstacles(int count)
{
    for(int i = 0; i < count; i++)
    {
        auto newObstacle = new Obstacle();
        graphicsScene->addItem(newObstacle);
    }
}


void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && pos().x() > 0)
        players[0]->movementDirection[LEFT] = true;
    else if(event->key() == Qt::Key_Right && pos().x() + this->settings->player_size.width() < this->settings->screen_size.width())
        players[0]->movementDirection[RIGHT] = true;
    else if(event->key() == Qt::Key_Up  && pos().y() > 0)
        players[0]->movementDirection[UP] = true;
    else if(event->key() == Qt::Key_Down  && pos().y() + this->settings->player_size.height() < this->settings->screen_size.height())
        players[0]->movementDirection[DOWN] = true;
    else if(event->key() == Qt::Key_Space)
    {
        auto newBullet = new Bullet();
        newBullet->setPos(players[0]->x()+(this->settings->player_size.width()/2),players[0]->y()-(this->settings->player_size.height()+1));
        this->graphicsScene->addItem(newBullet);
    }
    else if(event->key() == Qt::Key_Escape)
    {
        exit(EXIT_SUCCESS);
    }
    movePlayer();
}


void Game::movePlayer() {
    if (players[0]->movementDirection[UP] && players[0]->movementDirection[RIGHT] && pos().x() > 0 && pos().x() + this->settings->player_size.width() < this->settings->screen_size.width())
        players[0]->moveBy(this->settings->player_speed, -this->settings->player_speed);
    else if (players[0]->movementDirection[DOWN] && players[0]->movementDirection[LEFT] && pos().x() > 0 && pos().y() + this->settings->player_size.height() < this->settings->screen_size.height())
        players[0]->moveBy(-this->settings->player_speed, this->settings->player_speed);
    else if (players[0]->movementDirection[UP] && players[0]->movementDirection[LEFT] && pos().x() > 0)
        players[0]->moveBy(-this->settings->player_speed, -this->settings->player_speed);
    else if (players[0]->movementDirection[DOWN] && players[0]->movementDirection[RIGHT] && pos().x() + this->settings->player_size.width() < this->settings->screen_size.width() && pos().y() + this->settings->player_size.height() < this->settings->screen_size.height())
        players[0]->moveBy(this->settings->player_speed, this->settings->player_speed);
    else if (players[0]->movementDirection[RIGHT] && pos().x() + this->settings->player_size.width() < this->settings->screen_size.width())
        players[0]->moveBy(this->settings->player_speed, 0);
    else if (players[0]->movementDirection[LEFT] && pos().x() > 0)
        players[0]->moveBy(-this->settings->player_speed, 0);
    else if (players[0]->movementDirection[DOWN] && pos().x() > 0 && pos().y() + this->settings->player_size.height() < this->settings->screen_size.height())
        players[0]->moveBy(0, this->settings->player_speed);
    else if (players[0]->movementDirection[UP] && pos().x() > 0)
        players[0]->moveBy(0, -this->settings->player_speed);
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key() )
    {
    case Qt::Key_Up:
        players[0]->movementDirection[UP] = 0;
        break;
    case Qt::Key_Left:
        players[0]->movementDirection[LEFT] = 0;
        break;
    case Qt::Key_Down:
        players[0]->movementDirection[DOWN] = 0;
        break;
    case Qt::Key_Right:
        players[0]->movementDirection[RIGHT] = 0;
        break;
    }
}


void Game::checkAllCollistions() {
    QList<QGraphicsItem *> all_items = graphicsScene->items();
    for(int i =0; i < all_items.length(); i++) {
        if(typeid(*(all_items[i])) == typeid(Bullet)) {
            QList<QGraphicsItem *> colliding_items = all_items[i]->collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; ++i)
            {
                if(typeid(*(colliding_items[i])) == typeid(Enemy))
                {
                    //newGame->curr_score->increase();
                    scene()->removeItem(colliding_items[i]);
                    scene()->removeItem(all_items[i]);
                    delete all_items[i];
                    delete all_items[i];
                    return;
                }
                else if(typeid(*(colliding_items[i])) == typeid(Obstacle))
                {
                    delete all_items[i];
                    return;
                }
                else break;
            }
        }
        all_items[i]->setPos(all_items[i]->x(), all_items[i]->y()-newGame->settings->bullet_speed);
        if(all_items[i]->pos().y() + this->settings->bullet_size < 0)
        {
            scene()->removeItem(all_items[i]);
            delete all_items[i];
        }
    }
}
