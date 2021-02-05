#ifndef GAMESTATE_HA
#define GAMESTATE_HA
#include <QPoint>
#include <QList>
#include <QDataStream>

struct PlayerInfo
{
    QPointF pos;
    int id;
    int currentScore;
    bool invulnerable;
};

struct BulletInfo
{
    QPointF pos;
    QPointF direction;
    int playerID;
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
    int playerID;
    QList<ObstacleInfo> obstacleList;
    QList<BulletInfo> bulletList;
    QList<EnemyInfo> enemyList;
    QMap<int, PlayerInfo> playersInfoMap;
    void insertToDataStream( QDataStream& dataStream, int playerIdentification ) const;
    void extractFromDataStream( QDataStream& dataStream );

private:
    void insertQPointF(QDataStream& dataStream, const QPointF& pointf) const;
    void extractQPointF(QDataStream& dataStream, QPointF& pointf);
};

//QDataStream& operator<<( QDataStream& dataStream, const GameState& gameState );
//QDataStream& operator>>( QDataStream& dataStream, GameState& gameState );


#endif // GAMESTATE_HA
