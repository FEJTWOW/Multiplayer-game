#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
#include "settings.h"
#include "obstacle.h"
#include "bullet.h"
#include "serversocket.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent =0);
    void initGame();
    void addNewPlayer(QPoint point, QSize size);
    void moveAssets();
    void checkAllCollisions();
    void fireBullet(Player*);  // This might need to be refactored to player or sth
    void generateLayoutOne();
    void killPlayer(Player *);
    void renderGameState();
    QGraphicsScene * graphicsScene;
    QGraphicsScene * clientGraphicsScene;
    QList <Player*> players;
    QList <Score*> playerScores;
    Settings * settings;
    ServerSocket* sock;
    int numOfPlayers;
    QTimer* timer;
    int myPlayerId;
    GameState gameState;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void parseGameState(const QByteArray& data);
    void receivedPlayerId(const int&);
    void gameLoop();
    void playerAction();
    void spawnEnemy();
    void updatePoints();
};

#endif // GAME_H
