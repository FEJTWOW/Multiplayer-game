#ifndef GAME_H
#define GAME_H

#include "settings.h"
#include "serversocket.h"


#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget * parent =0);
    void initGame();
    void renderGameState();
    QGraphicsScene * clientGraphicsScene;
    Settings * settings;
    ServerSocket* sock;
    int myPlayerId;
    GameState gameState;
    void showScore(int currentScore);
    void createBullet(QPointF pos);

    QTimer* timer;
    int horizontal;
    int vertical;
    int shooting;
    int shootDirection;
    QMap<int, bool> keys;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void parseGameState(const QByteArray& data);
    void receivedPlayerId(const int&);
    void move();
};

#endif // GAME_H
