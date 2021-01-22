#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <enemy.h>


Game::Game(QWidget *parent)
{
    numOfPlayers = 0;

    network = new Network(12345, this);
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

    /*timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(this->settings->game_timer_res);*/
    //connect(network, SIGNAL(playerAction(const PlayerAction& playerAction)), this, SLOT(handlePlayerAction(const PlayerAction& playerAction)));
    connect(network, SIGNAL(playerMadeAction(const PlayerAction&)), this, SLOT(handlePlayerAction(const PlayerAction&)));
    /*auto enemyTimer = new QTimer();
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    enemyTimer->start(2000);*/
}

void Game::handlePlayerAction(const PlayerAction& playerAction) {
    qDebug() << playerAction.newX << playerAction.newY << playerAction.shootingDirection;
}

void Game::addNewPlayer(QPoint point, QSize size)
{
    // This does not really use the given arguments. (raeds from settings for now)
    // A theoretical method to abstract from a single player concept

    players.append(new Player(settings->player_point, settings->player_size,numOfPlayers));
    graphicsScene->addItem(players[numOfPlayers]);
    playerScores.append(new Score());
    playerScores[numOfPlayers]->setupScore();

    graphicsScene->addItem(playerScores[numOfPlayers]);
    numOfPlayers++;

    show();

}

void Game::generateObstacles(int count)
{
    for(int i = 0; i < count; i++)
    {
        auto newObstacle = new Obstacle();
        graphicsScene->addItem(newObstacle);
        qDebug() << "Obstacle address: " << &newObstacle;
    }
}


void Game::keyPressEvent(QKeyEvent *event)
{
    // Player id (players[id]) will be received from the client through the socket
    // for now :
    int player_id = 0;

    if(event->key() == Qt::Key_Left)
        players[player_id]->movementDirection[LEFT] = true;
    else if(event->key() == Qt::Key_Right)
        players[player_id]->movementDirection[RIGHT] = true;
    else if(event->key() == Qt::Key_Up)
        players[player_id]->movementDirection[UP] = true;
    else if(event->key() == Qt::Key_Down)
        players[player_id]->movementDirection[DOWN] = true;
    else if(event->key() == Qt::Key_W)
    {
            players[player_id]->isShooting = true;
            players[player_id]->shootingDirection = 0;
    }
    else if(event->key() == Qt::Key_A)
    {
            players[player_id]->isShooting = true;
            players[player_id]->shootingDirection = 1;
    }
    else if(event->key() == Qt::Key_S)
    {
            players[player_id]->isShooting = true;
            players[player_id]->shootingDirection = 2;
    }
    else if(event->key() == Qt::Key_D)
    {
            players[player_id]->isShooting = true;
            players[player_id]->shootingDirection = 3;
    }
    else if(event->key() == Qt::Key_Escape)
    {
        exit(EXIT_SUCCESS);
    }
    //movePlayer();
}


void Game::playerAction() {
    int playerSpeed = this->settings->player_speed;

    for(int i = 0; i < numOfPlayers; i++)
    {
        if(players[i]->movementDirection[UP] && players[i]->pos().y() > 0)
        {
            players[i]->moveBy(0, -playerSpeed);
        }
        if(players[i]->movementDirection[DOWN] && players[i]->pos().y() + settings->player_size.height()< settings->screen_size.height())
        {
            players[i]->moveBy(0, playerSpeed);
        }
        if(players[i]->movementDirection[LEFT] && players[i]->pos().x() > 0)
        {
            players[i]->moveBy(-playerSpeed, 0);
        }
        if(players[i]->movementDirection[RIGHT] && players[i]->pos().x() + settings->player_size.width() < settings->screen_size.width())
        {
            players[i]->moveBy(playerSpeed, 0);
        }
        if(players[i]->isShooting && !players[i]->shotFired)
        {
            fireBullet(players[i]);
        }
    }

}

void Game::spawnEnemy()
{
    auto newEnemy = new Enemy();
    scene()->addItem(newEnemy);
    qDebug() << "Should be spawned (Enemy)";
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    // In final cut this would be changed on server based on clients sending input (not local keyEvents)
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
    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_D:
        players[0]->isShooting = false;
        break;
    }

}

void Game::gameLoop() {
    playerAction();
    moveAssets();
    checkAllCollisions();
}

void Game::moveAssets() {

    QList<QGraphicsItem *> all_items = graphicsScene->items();
    for(int i =0; i < all_items.length(); i++)
    {
        if(typeid(*(all_items[i])) == typeid(Bullet))
        {
            Bullet * bullet = dynamic_cast<Bullet *>(all_items[i]);
            //qDebug() << bullet->moveSet.x() << " " << bullet->moveSet.y();
            //all_items[i]->moveBy(all_items[i]->moveSet.x(), all_items[i]->moveSet.y());
            bullet->moveBy(bullet->moveSet.x(), bullet->moveSet.y());
            if(all_items[i]->pos().y() + this->settings->bullet_size.height() < 0)
            {
                //qDebug() << "remove bullet";
                graphicsScene->removeItem(all_items[i]);
                delete all_items[i];
                continue;
            }
        }
        else if(typeid(*(all_items[i])) == typeid(Enemy))
        {
            all_items[i]->moveBy(0, 5);
            if(all_items[i]->pos().y() > settings->screen_size.height())
            {
                graphicsScene->removeItem(all_items[i]);
                delete all_items[i];
            }

        }
    }
}

void Game::checkAllCollisions() {
    QSet<QGraphicsItem *> toBeDeleted;
    QList<QGraphicsItem *> all_items = graphicsScene->items();

    for(int i =0; i < all_items.length(); i++)
    {
        if(typeid(*(all_items[i])) == typeid(Bullet))
        {
            QList<QGraphicsItem *> colliding_items = all_items[i]->collidingItems();
            if(!colliding_items.size())
            {
                continue;
            }
            if(typeid(*(colliding_items[0])) == typeid(Bullet) || typeid(*(colliding_items[0])) == typeid(Enemy))
            {
                toBeDeleted.insert(all_items[i]);
                toBeDeleted.insert(colliding_items[0]);
            }
            else if(typeid(*(colliding_items[0])) == typeid(Score))
            {
                continue;
            }
            else
            {
                toBeDeleted.insert(all_items[i]);
            }

        }
    }

    QSet<QGraphicsItem *>::iterator i;
    for (i = toBeDeleted.begin(); i != toBeDeleted.end(); ++i)
    {
        scene()->removeItem(*i);
        delete *i;
    }

}

void Game::fireBullet(Player* player)
{
    QPointF directions;
    switch (player->shootingDirection)
    {
        case 0:
            directions.setX(0);
            directions.setY(-settings->bullet_speed);
            break;
        case 1:
            directions.setX(-settings->bullet_speed);
            directions.setY(0);
            break;
        case 2:
            directions.setX(0);
            directions.setY(settings->bullet_speed);
            break;
        case 3:
            directions.setX(settings->bullet_speed);
            directions.setY(0);
            break;
        default:
            break;

    }
    auto newBullet = new Bullet(directions, player->id);
    qDebug() << "Created a new bullet: " << directions.x() << " " << directions.y() << " ";
//    newBullet->setPos(100,100);
    switch (player->shootingDirection)
    {
        case 0:
            newBullet->setPos(player->x()+(this->settings->player_size.width()/2),player->y()-(this->settings->player_size.height()+1));
            break;
        case 1:
            newBullet->setPos(player->x()- player->rect().width() -1, player->y() + player->rect().height()/2);
            break;
        case 2:
            newBullet->setPos(player->x()+(this->settings->player_size.width()/2),player->y()+(this->settings->player_size.height()+12));           // ??????
            break;
        case 3:
            newBullet->setPos(player->x()+settings->player_size.width()+12, player->y() +settings->player_size.height()/2 + 1);         // Needs fixing
            break;
        default:
            break;

    }
    //newBullet->setPos(players[i]->x()+(this->settings->player_size.width()/2),players[i]->y()-(this->settings->player_size.height()+1));
    this->graphicsScene->addItem(newBullet);
    player->shotFired = true;
}
