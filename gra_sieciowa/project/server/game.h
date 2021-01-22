#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
#include "settings.h"
#include "obstacle.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "bullet.h"
#include "network.h"

// Generalnie jest zrobione bardzo na szypko i jest bardzo źle

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent =0);
    void initGame();
    void addNewPlayer(QPoint point, QSize size);
    void generateObstacles(int count);
    void moveAssets();
    void checkAllCollisions();
    void fireBullet(Player*);  // This might need to be refactored to player or sth
    QGraphicsScene * graphicsScene;
    QList <Player*> players;
    QList <Score*> playerScores;
    Settings * settings;
    int numOfPlayers;
    QTimer* timer;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void gameLoop();
    void playerAction();
    void spawnEnemy();
    void handlePlayerAction(const PlayerAction& playerAction);

public:
    Network* network;
};

#endif // GAME_H
