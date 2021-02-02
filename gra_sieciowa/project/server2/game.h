#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
#include "settings.h"
#include "obstacle.h"
#include "bullet.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "gamestate.h"
#include "network.h"
#include "playeraction.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent =0);
    void initGame();
    void addNewPlayer(QPoint point, QSize size, int playerID);
    void moveAssets();
    void checkAllCollisions();
    void fireBullet(Player*);  // This might need to be refactored to player or sth
    void generateLayoutOne();
    void killPlayer(Player *);
    QGraphicsScene * graphicsScene;
    //QList <Player*> players;
    QMap<int, Player*> playersMap;  // int jest takie same jak int w clientsMap w network.h; dzieki temu mamy polaczenie player-client
    QMap<int, Score*> playerScoresMap;
    Settings * settings;
    //int numOfPlayers;
    int numOfEnemies;
    QTimer* timer;
    GameState gameInfo;

protected:
    //void keyPressEvent(QKeyEvent *event) override;
    //void keyReleaseEvent(QKeyEvent *event) override;
    GameState dumpGameInfo();

public slots:
    void onConnection(int id);
    void gameLoop();
    void playerAction();
    void spawnEnemy();
    void updatePoints();
    void handlePlayerAction(const PlayerAction& playerAction);
    void onPlayerDisconnected(int playerID);
    void respawnPlayer(Player* player);
public:
    Network* network;
};

#endif // GAME_H
