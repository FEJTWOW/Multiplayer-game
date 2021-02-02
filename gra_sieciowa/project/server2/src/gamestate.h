#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <QPoint>
#include <QList>

struct PlayerInfo
{
    QPointF pos;
    int id;
    int currentScore;
};

struct BulletInfo
{
    QPointF pos;
    QPointF direction;
};

struct ObstacleInfo
{
    QPointF pos;
};

struct EnemyInfo
{
    QPointF pos;
};

class GameState
{
public:
    ObstacleInfo obstacle[20];
    PlayerInfo player[5];
    BulletInfo bullet[25];
    EnemyInfo enemy[10];
//    QList<PlayerInfo> player;
//    QList<BulletInfo> bullet;
//    QList<EnemyInfo> enemy;
//    QList<ObstacleInfo> obstacle;

};



#endif // GAMESTATE_H
