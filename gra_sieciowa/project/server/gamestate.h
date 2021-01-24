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

struct PlayerAction
{
    QPointF pos;
};


class GameState
{
public:
    QList<PlayerInfo> player;
    QList<BulletInfo> bullet;
    QList<EnemyInfo> enemy;
    QList<ObstacleInfo> obstacle;

};



#endif // GAMESTATE_H
