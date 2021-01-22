#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <enemy.h>


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

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(this->settings->game_timer_res);

    auto enemyTimer = new QTimer();
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    enemyTimer->start(2000);
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
    if(event->key() == Qt::Key_Left)
        players[0]->movementDirection[LEFT] = true;
    else if(event->key() == Qt::Key_Right)
        players[0]->movementDirection[RIGHT] = true;
    else if(event->key() == Qt::Key_Up)
        players[0]->movementDirection[UP] = true;
    else if(event->key() == Qt::Key_Down)
        players[0]->movementDirection[DOWN] = true;
    else if(event->key() == Qt::Key_Space)
    {
            players[0]->isShooting = true;
    }
    else if(event->key() == Qt::Key_Escape)
    {
        exit(EXIT_SUCCESS);
    }
    //movePlayer();
}


void Game::playerAction() {
    int playerSpeed = this->settings->player_speed;

    if(players[0]->movementDirection[UP] && players[0]->pos().y() > 0) {
        players[0]->moveBy(0, -playerSpeed);
    }
    if(players[0]->movementDirection[DOWN] && players[0]->pos().y() + settings->player_size.height()< settings->screen_size.height()) {
        players[0]->moveBy(0, playerSpeed);
    }
    if(players[0]->movementDirection[LEFT] && players[0]->pos().x() > 0) {
        players[0]->moveBy(-playerSpeed, 0);
    }
    if(players[0]->movementDirection[RIGHT] && players[0]->pos().x() + settings->player_size.width() < settings->screen_size.width()) {
        players[0]->moveBy(playerSpeed, 0);
    }
    if(players[0]->isShooting && !players[0]->shotFired) {
        auto newBullet = new Bullet();
        newBullet->setPos(players[0]->x()+(this->settings->player_size.width()/2),players[0]->y()-(this->settings->player_size.height()+1));
        this->graphicsScene->addItem(newBullet);
        players[0]->shotFired = true;
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
    case Qt::Key_Space:
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
    for(int i =0; i < all_items.length(); i++) {
        if(typeid(*(all_items[i])) == typeid(Bullet)) {
            all_items[i]->moveBy(0, -this->settings->bullet_speed);
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
            //qDebug() << "Enemy +5y";
            if(all_items[i]->pos().y() > settings->screen_size.height())
            {
                //qDebug() << "remove Enemy";
                graphicsScene->removeItem(all_items[i]);
                delete all_items[i];
            }

        }
    }
}

void Game::checkAllCollisions() {
    QSet<QGraphicsItem *> toBeDeleted;

    QList<QGraphicsItem *> all_items = graphicsScene->items();
    //qDebug() << "Size: " << all_items.size();
    for(int i =0; i < all_items.length(); i++) {
        if(typeid(*(all_items[i])) == typeid(Bullet)) {
            QList<QGraphicsItem *> colliding_items = all_items[i]->collidingItems();
            if(!colliding_items.size()) {   // nie ma zadnych kolidujacych
                continue;
            }
            qDebug() << "There is a collision!";
            if(typeid(*(colliding_items[0])) == typeid(Bullet) || typeid(*(colliding_items[0])) == typeid(Enemy)) {
                toBeDeleted.insert(all_items[i]);
                toBeDeleted.insert(colliding_items[0]);
            } else if(typeid(*(colliding_items[0])) == typeid(Score)) {
                continue;
            }
            else {
                toBeDeleted.insert(all_items[i]);
            }

        }
    }

    QSet<QGraphicsItem *>::iterator i;
    for (i = toBeDeleted.begin(); i != toBeDeleted.end(); ++i) {
        scene()->removeItem(*i);
        delete *i;
    }




//    for(int i =0; i < all_items.length(); i++)
//    {
//        if(typeid(*(all_items[i])) == typeid(Bullet))
//        {
//            QList<QGraphicsItem *> colliding_items = all_items[i]->collidingItems();
//            for(int i = 0, n = colliding_items.size(); i < n; ++i)
//            {
//                if(typeid(*(colliding_items[i])) == typeid(Enemy))
//                {
//                    //newGame->curr_score->increase();
//                    qDebug() << "if";
//                    graphicsScene->removeItem(colliding_items[i]);
//                    qDebug() << "if2";
//                    graphicsScene->removeItem(all_items[i]);
//                    qDebug() << "after if2";
//                    delete colliding_items[i];
//                    qDebug() << "after delete if2";
//                    delete all_items[i];
//                    qDebug() << "after delete2 if2";
//                    break;
//                }
//                else if(typeid(*(colliding_items[i])) == typeid(Obstacle))
//                {
//                    qDebug() << "Coliding item address: " << &colliding_items[i];
//                    graphicsScene->removeItem(all_items[i]);

//                    delete all_items[i];
//                    break;
//                }
//                else if(all_items[i]->pos().y() + this->settings->bullet_size.height() < 0)
//                {
//                    qDebug() << "else if";
//                    graphicsScene->removeItem(all_items[i]);
//                    delete all_items[i];
//                    break;
//                }
//                else break;
//            }

//            if(colliding_items.size() == 0) {
//                all_items[i]->setPos(all_items[i]->x(), all_items[i]->y() - this->settings->bullet_speed);
//            }
//        }
//    }
}
