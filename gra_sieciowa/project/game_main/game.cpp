#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QHostAddress>
#include <QtAlgorithms>
#include <enemy.h>


Game::Game(QWidget *parent)
{
    numOfPlayers = 0;
}

void Game::initGame()
{
    sock = new ServerSocket(QHostAddress::LocalHost,12345, this);
    connect(sock, SIGNAL(newPlayerId(int)), this, SLOT(receivedPlayerId(int)));
    connect(sock, SIGNAL(newGameState(const QByteArray&)), this, SLOT(parseGameState(const QByteArray&)));

    settings = new Settings();
    // Create the game map
    graphicsScene = new QGraphicsScene();
    clientGraphicsScene = new QGraphicsScene();
    // Set the size of the map
    graphicsScene->setSceneRect(QRectF(settings->screen_point, settings->screen_size));
    clientGraphicsScene->setSceneRect(QRectF(settings->screen_point, settings->screen_size));
    // Create our view
    setScene(clientGraphicsScene);
    // Disable sidebars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set the size of the view
    setFixedSize(settings->screen_size);

    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(this->settings->game_timer_res);

    auto scoreTimer = new QTimer();
    QObject::connect(scoreTimer, SIGNAL(timeout()), this, SLOT(updatePoints()));
    scoreTimer->start(settings->score_passive_interval_in_ms);

    auto enemyTimer = new QTimer();
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    enemyTimer->start(2000);
}

void Game::addNewPlayer(QPoint point, QSize size)
{
    players.append(new Player(settings->player_point, settings->player_size,numOfPlayers));
    graphicsScene->addItem(players[numOfPlayers]);
    playerScores.append(new Score());
    graphicsScene->addItem(playerScores[numOfPlayers]);
    playerScores[numOfPlayers]->setupScore();
    numOfPlayers++;

    show();

}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Player id (players[id]) will be received from the client through the socket
    // for now :
    int player_id = 0;

    if(!players[player_id]->dead)
    {
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
    }

    //movePlayer();
}


void Game::playerAction() {
    int playerSpeed = this->settings->player_speed;

    for(int i = 0; i < numOfPlayers; i++)
    {
        if(!players[i]->dead)   // Bandaid, prob can disable keyEvents altogether
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
}

void Game::spawnEnemy()
{
    auto newEnemy = new Enemy();
    scene()->addItem(newEnemy);

}

void Game::updatePoints()
{
    for(int i = 0; i < numOfPlayers; i++)
    {
        if(!players[i]->dead)
            playerScores[i]->increasePassive();
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    // In final cut this would be changed on server based on clients sending input (not local keyEvents)
    if(!players[0]->dead)
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
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
            players[0]->isShooting = false;
            break;
        }
    }
}

void Game::parseGameState(const QByteArray &data)
{
    qDebug() << "1";
    GameState receivedGameState;
    memcpy(&receivedGameState,data.data(), sizeof(receivedGameState));
    for(int i=0; i < 20; i++)
    {
        //qDebug() << "Obstacle[" << i << "] :" << gameState.obstacle[i].pos.x() << " " << gameState.obstacle[i].pos.y();
        this->gameState.obstacle[i] = receivedGameState.obstacle[i];
    }
    qDebug() << "2";
    for(int i =0; i < 5; i++)
    {

        this->gameState.player[i] = receivedGameState.player[i];
    }
    qDebug() << "3";
    for(int i =0; i < 25; i++)
    {
        this->gameState.bullet[i] = receivedGameState.bullet[i];
    }
    qDebug() << "4";
    renderGameState();
}

void Game::renderGameState()
{

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
}


void Game::receivedPlayerId(const int &id)
{
    myPlayerId = id;
}

void Game::gameLoop() {
    playerAction();
    moveAssets();
    checkAllCollisions();
    //updatePoints();
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
                graphicsScene->removeItem(all_items[i]);
                delete all_items[i];
                continue;
            }
        }
        else if(typeid(*(all_items[i])) == typeid(Enemy))
        {
            all_items[i]->moveBy(0, settings->enemy_speed);
            if(all_items[i]->pos().y() > settings->screen_size.height())
            {
                qDebug() << "I am deleted (enemy)";
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
            else if (typeid(*(colliding_items[0])) == typeid(Player))
            {
                qDebug() << "1";
                Player * player = dynamic_cast<Player *>(colliding_items[0]);
                qDebug() << "2";
                Bullet * bullet = dynamic_cast<Bullet *>(all_items[i]);
                qDebug() << "3";
                if(player->dead)
                {
                    qDebug() << "4";
                    continue;
                }
                else if(player->invulnerable)
                {
                    qDebug() << "5";
                    toBeDeleted.insert(all_items[i]);
                    continue;
                }
                else
                {
                    qDebug() << "6";
                    playerScores[bullet->player_id]->increaseKill();
                    toBeDeleted.insert(all_items[i]);
                    killPlayer(player);
                    continue;
                }
                qDebug() << "7";

            }
            else
            {
                toBeDeleted.insert(all_items[i]);
            }


        }
        if(typeid(*(all_items[i])) == typeid(Player))
        {
            QList<QGraphicsItem *> colliding_items = all_items[i]->collidingItems();
            for(int j = 0; j < colliding_items.size(); j++)
            {
                if(typeid(*(colliding_items[j])) == typeid(Obstacle) || typeid(*(colliding_items[j])) == typeid(Enemy))
                {
                    Player * player = dynamic_cast<Player *>(all_items[i]);
                    if(!player->dead && !player->invulnerable)
                    {
                        qDebug() << "erroer3";
                        killPlayer(player);
                        qDebug() << "erroer4";
                    }
                }
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

void Game::killPlayer(Player * player)
{
    qDebug() << "Im here1";
    player->dead = true;
    qDebug() << "Im here2";
    graphicsScene->removeItem(player);
    qDebug() << "Im here3";
    player->respawnTimer = new QTimer();
    qDebug() << "Im here4";
    QObject::connect(player->respawnTimer, SIGNAL(timeout()), player, SLOT(respawn()));
    qDebug() << "Im here5";
    player->respawnTimer->start(settings->respawn_time_in_ms);
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
    this->graphicsScene->addItem(newBullet);
    player->shotFired = true;
}

void Game::generateLayoutOne()
{
    // Needs proper scaling

    QList<Obstacle *> obstacleLayout;
    QSize size = {20,50};

    int screenWidth = settings->screen_size.width();
    int screenHeight = settings->screen_size.height();


    for(int i = 0.2*screenWidth; i <= screenWidth; i+= 0.2*screenWidth)
    {
        for(int j = 1; j < 4; j++)
        {
            auto obstacle = new Obstacle(QPoint(i,screenHeight -j*size.height()), size);
            graphicsScene->addItem(obstacle);
        }

    }


    for(int i = 0.33 *screenWidth; i <= screenWidth-size.width(); i+= 0.33*screenWidth)
    {
        for(int j = 1; j < 5; j++)
        {
            auto obstacle = new Obstacle(QPoint(i,0.4*screenHeight -j*size.height()), size);
            graphicsScene->addItem(obstacle);
        }


    }


}

