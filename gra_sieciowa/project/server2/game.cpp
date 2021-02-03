#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <enemy.h>
#include <gameSettings.h>


Game::Game(QWidget *parent)
{
    numOfEnemies = 0;
    network = new Network(12345, this);
}

void Game::initGame()
{
    // Create the game map
    graphicsScene = new QGraphicsScene();
    // Set the size of the map
    graphicsScene->setSceneRect(QRectF(screenPoint, screenSize));
    // Create our view
    setScene(graphicsScene);
    // Disable sidebars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set the size of the view
    setFixedSize(screenSize);

    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    connect(network, SIGNAL(playerMadeAction(const PlayerAction&)), this, SLOT(handlePlayerAction(const PlayerAction&)));
    connect(network, SIGNAL(newClientConnected(int)), this, SLOT(onConnection(int)));

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(gameTimerRes);

    auto scoreTimer = new QTimer();
    QObject::connect(scoreTimer, SIGNAL(timeout()), this, SLOT(updatePoints()));
    scoreTimer->start(scorePassiveIntervalInMs);

    auto enemyTimer = new QTimer();
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    enemyTimer->start(2000);

    connect(network, SIGNAL(gameDisconnect(int)), this, SLOT(onPlayerDisconnected(int)));
}

void Game::addNewPlayer(QPoint point, QSize size, int playerID)
{
    playersMap[playerID] = new Player(playerPoint, playerSize,playerID);
    graphicsScene->addItem(playersMap[playerID]);
    playersMap[playerID]->score = 0; // niepotrzbne
    //playersMap[playerID]->setupScore();    // bezsensu po stronie serwera

    show();
}

/*void Game::keyPressEvent(QKeyEvent *event)  // TODO delete
{
    // Player id (players[id]) will be received from the client through the socket
    // for now :
    int player_id = 0;
    Player* player = playersMap[player_id];
    if(!player->dead)
    {
        if(event->key() == Qt::Key_Left)
            player->movementDirection[LEFT] = true;
        else if(event->key() == Qt::Key_Right)
            player->movementDirection[RIGHT] = true;
        else if(event->key() == Qt::Key_Up)
            player->movementDirection[UP] = true;
        else if(event->key() == Qt::Key_Down)
            player->movementDirection[DOWN] = true;
        else if(event->key() == Qt::Key_W)
        {
                player->isShooting = true;
                player->shootingDirection = 0;
        }
        else if(event->key() == Qt::Key_A)
        {
                player->isShooting = true;
                player->shootingDirection = 1;
        }
        else if(event->key() == Qt::Key_S)
        {
                player->isShooting = true;
                player->shootingDirection = 2;
        }
        else if(event->key() == Qt::Key_D)
        {
                player->isShooting = true;
                player->shootingDirection = 3;
        }
        else if(event->key() == Qt::Key_Escape)
        {
            exit(EXIT_SUCCESS);
        }
    }

    //movePlayer();
}

void Game::keyReleaseEvent(QKeyEvent *event)    // TODO delete
{
    // In final cut this would be changed on server based on clients sending input (not local keyEvents)
    Player* player = playersMap[0];
    if(!player->dead)
    {
        switch ( event->key() )
        {
        case Qt::Key_Up:
            player->movementDirection[UP] = 0;
            break;
        case Qt::Key_Left:
            player->movementDirection[LEFT] = 0;
            break;
        case Qt::Key_Down:
            player->movementDirection[DOWN] = 0;
            break;
        case Qt::Key_Right:
            player->movementDirection[RIGHT] = 0;
            break;
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
            player->isShooting = false;
            break;
        }
    }
}*/

void Game::playerAction() {
    int playerSpeed = playerSpeed;

    for(const auto& id : playersMap.keys())
    {
        Player* player = playersMap[id];
        if(!player->dead)   // Bandaid, prob can disable keyEvents altogether
        {
            if(player->isShooting && !player->shotFired)
            {
                fireBullet(player);
            }

            player->move(playerSpeed);
        }
    }
}

void Game::spawnEnemy()
{
    if(numOfEnemies < 9)
    {
        auto newEnemy = new Enemy();
        int randPos = rand() & 750;
        newEnemy->setRect(QRectF(QPoint(randPos, 0), enemySize));

        scene()->addItem(newEnemy);
        numOfEnemies++;
    }
    //qDebug() << "On spawn: " << numOfEnemies;
}

void Game::updatePoints()
{
    for(const auto& id : playersMap.keys())
    {
        if(!playersMap[id]->dead)
            playersMap[id]->score += scorePassiveValue;
    }
    this->dumpGameInfo();
}

void Game::handlePlayerAction(const PlayerAction &playerAction)
{
    qDebug() << "Handle player action!";
    Player* player = playersMap[playerAction.id];

    player->horizontalMove = playerAction.horizontal;
    player->verticalMove = playerAction.vertical;

    player->isShooting = playerAction.shooting;
    player->shootingDirection = playerAction.shootDirection;
}

void Game::gameLoop() {
    playerAction();
    moveAssets();
    checkAllCollisions();
    GameState gameState = dumpGameInfo();
    //qDebug() << "gameLoop before sendAll";
    network->sendAll(gameState);
    //qDebug() << "gameLoop aftersendAll";
}

void Game::moveAssets() {

    QList<QGraphicsItem *> all_items = graphicsScene->items();
    for(int i =0; i < all_items.length(); i++)
    {
        if(typeid(*(all_items[i])) == typeid(Bullet))
        {
            Bullet * bullet = dynamic_cast<Bullet *>(all_items[i]);
            bullet->move();
            if(all_items[i]->pos().y() + bulletSize.height() < 0 || all_items[i]->pos().y() > screenSize.height()
                    || all_items[i]->pos().x() < 0 || all_items[i]->pos().x() > screenSize.width() )       // If out of bounds
            {
                graphicsScene->removeItem(all_items[i]);               
                auto index = playersMap[bullet->player_id]->playerBullets.indexOf(bullet);
                playersMap[bullet->player_id]->playerBullets.takeAt(index);
                delete bullet;
                continue;
            }
        }
        else if(typeid(*(all_items[i])) == typeid(Enemy))
        {
            all_items[i]->moveBy(0, enemySpeed);
            if(all_items[i]->pos().y() > screenSize.height())
            {
                numOfEnemies--;
                //qDebug() << "On delete(move): " << numOfEnemies;
                graphicsScene->removeItem(all_items[i]);
                delete all_items[i];
            }
        }
    }
}

void Game::checkAllCollisions() {
    QList<QGraphicsItem *> toBeDeleted;
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
            if(typeid(*(colliding_items[0])) == typeid(Bullet))
            {
                if(!toBeDeleted.contains(all_items[i]))
                    toBeDeleted.push_back(all_items[i]);
                if(!toBeDeleted.contains(colliding_items[0]))
                    toBeDeleted.push_back(colliding_items[0]);
            }
            else if(typeid(*(colliding_items[0])) == typeid(Enemy))
            {
                if(!toBeDeleted.contains(all_items[i]))
                    toBeDeleted.push_back(all_items[i]);
                if(!toBeDeleted.contains(colliding_items[0]))
                    toBeDeleted.push_back(colliding_items[0]);
            }
            else if (typeid(*(colliding_items[0])) == typeid(Player))
            {
                Player * player = dynamic_cast<Player *>(colliding_items[0]);
                Bullet * bullet = dynamic_cast<Bullet *>(all_items[i]);
                if(player->dead || player->id == bullet->player_id)
                {
                    continue;
                }
                else if(player->invulnerable)
                {
                    if(!toBeDeleted.contains(all_items[i]))
                        toBeDeleted.push_back(all_items[i]);
                    continue;
                }
                else
                {
                    qDebug() << "Player o id: " << bullet->player_id << "zabil!";
                    playersMap[bullet->player_id]->score -= scoreKillValue;
                    if(!toBeDeleted.contains(all_items[i]))
                        toBeDeleted.push_back(all_items[i]);
                    killPlayer(player);
                    continue;
                }
            }
            else
            {
                if(!toBeDeleted.contains(all_items[i]))
                    toBeDeleted.push_back(all_items[i]);
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
                        killPlayer(player);
                    }
                }
            }
        }
    }

    for(int i =0; i < toBeDeleted.size(); i++)
    {
        scene()->removeItem(toBeDeleted[i]);
        if( typeid(*(toBeDeleted[i])) == typeid(Enemy))
        {
            numOfEnemies--;
            qDebug() << "On delete: " << numOfEnemies;
        }

        if( typeid(*(toBeDeleted[i])) == typeid(Bullet))
        {
            Bullet * bullet = dynamic_cast<Bullet *>(toBeDeleted[i]);
            auto index = playersMap[bullet->player_id]->playerBullets.indexOf(bullet);
            playersMap[bullet->player_id]->playerBullets.takeAt(index);
        }
        else delete toBeDeleted[i];
    }

}

void Game::killPlayer(Player * player)
{
    player->kill();
    graphicsScene->removeItem(player);
    connect(player, SIGNAL(respawn(Player*)), this, SLOT(respawnPlayer(Player*)));
}

void Game::respawnPlayer(Player* player) {
    graphicsScene->addItem(player);
}


void Game::fireBullet(Player* player)
{
    if(player->playerBullets.size() < playerMaxBullets)
    {
        auto newBullet = new Bullet(player->shootingDirection, player->id, player->pos());
        player->playerBullets.append(newBullet);
        this->graphicsScene->addItem(newBullet);
        player->shotFired = true;
    }

}

void Game::generateLayoutOne()
{
    // Needs proper scaling

    QList<Obstacle *> obstacleLayout;
    QSize size = obstacleSize;

    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();

    int count = 0;
    for(int i = 0.2*screenWidth; i < screenWidth; i+= 0.2*screenWidth)
    {
        for(int j = 1; j < 4; j++)
        {
            count++;
            generateObstacle(QPoint(i,screenHeight -j*size.height()), size);
        }

    }
    for(int i = 0.33 *screenWidth; i < screenWidth-size.width(); i+= 0.33*screenWidth)
    {
        for(int j = 1; j < 5; j++)
        {
            count++;
            generateObstacle(QPoint(i,0.4*screenHeight -j*size.height()), size);
        }
    }
}


void Game::generateObstacle(QPoint point, QSize size) {
    auto obstacle = new Obstacle();
    obstacle->setPos(0,0);
    obstacle->setRect(point.x(),point.y(),size.width(),size.height());
    graphicsScene->addItem(obstacle);
}

GameState Game::dumpGameInfo()
{
    QList<QGraphicsItem*> allItems = graphicsScene->items();
    GameState gameInfo;

    int bulletCount =0;
    int playerCount =0;
    int enemyCount =0;
    int obstacleCount =0;
    for (auto* i : allItems)
    {

        if (typeid(*i) == typeid(Bullet))
        {
            Bullet* tempBullet = dynamic_cast<Bullet*>(i);
            BulletInfo bulletInfo = { .pos = tempBullet->pos(), .direction = tempBullet->moveSet };
            gameInfo.bullet[bulletCount] = bulletInfo;
            bulletCount++;
        }
        if (typeid(*i) == typeid(Player))
        {
            Player* tempPlayer = dynamic_cast<Player*>(i);
            // sth is crashing here after disconnect
            PlayerInfo playerInfo = { .pos = tempPlayer->pos(), .id = tempPlayer->id, .currentScore = this->playersMap[tempPlayer->id]->score };
            gameInfo.player[playerCount] = playerInfo;
            playerCount++;
        }
        if (typeid(*i) == typeid(Obstacle))
        {
            Obstacle* tempObstacle = dynamic_cast<Obstacle*>(i);
            QPointF point(tempObstacle->rect().x(), tempObstacle->rect().y());
            ObstacleInfo obstacleInfo = { .pos = point};
            gameInfo.obstacle[obstacleCount] = obstacleInfo;
            obstacleCount++;
        }
        if (typeid(*i) == typeid(Enemy))
        {
            Enemy* tempEnemy = dynamic_cast<Enemy*>(i);
            QPointF point(tempEnemy->rect().x(),tempEnemy->pos().y());
            //qDebug() << tempEnemy->rect().x() << tempEnemy->pos().y() << "IS THE ENEMY";
            EnemyInfo enemyInfo = { .pos = point };
            gameInfo.enemy[enemyCount] = enemyInfo;
            enemyCount++;

        }
    }
    return gameInfo;
}

void Game::onConnection(int id)
{
    qDebug() << "New player with id " << id;

    network->send(id);
    addNewPlayer(QPoint(playerPoint), QSize(playerSize), id);
}


void Game::onPlayerDisconnected(int playerID) {
    qDebug() << " Game::onDisconnected, playerID: " << playerID;

    if(playersMap[playerID])
        graphicsScene->removeItem(playersMap[playerID]);
    playersMap.remove(playerID);
    network->clientsMap.remove(playerID);
    qDebug() << "Removed from playersMap & clientMap";
}

