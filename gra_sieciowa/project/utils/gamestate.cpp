#include "gamestate.h"
#include <QDebug>

//QDataStream &operator<<(QDataStream &out, const GameState &gameState)
//{
//    out << gameState.obstacleList.count();
//    for(int i = 0; i < gameState.obstacleList.count(); ++i) {
//        int x = gameState.obstacleList[i].pos.toPoint().x();
//        int y = gameState.obstacleList[i].pos.toPoint().y();
//        out << x << y;
//    }
//    return out;
//}

//QDataStream &operator>>(QDataStream &in, GameState &gameState)
//{
//    int obstacleCount;
//    in >> obstacleCount;
//    for(int i = 0; i < obstacleCount; ++i) {
//        ObstacleInfo obstacleInfo;
//        int x, y;
//        in >> x >> y;
//        obstacleInfo.pos.setX(x);
//        obstacleInfo.pos.setY(y);
//        gameState.obstacleList.append(obstacleInfo);
//    }
//    return in;
//}


void GameState::insertToDataStream( QDataStream& dataStream, int playerIdentification ) const{
    dataStream << playerIdentification;

    dataStream << obstacleList.count();
    for(int i = 0; i < obstacleList.count(); ++i) {
        insertQPointF(dataStream, obstacleList[i].pos);
    }

    dataStream << bulletList.count();
    for(int i = 0; i < bulletList.count(); ++i) {
        insertQPointF(dataStream, bulletList[i].pos);
        insertQPointF(dataStream, bulletList[i].direction);
    }

    dataStream << enemyList.count();
    for(int i = 0; i < enemyList.count(); ++i) {
        insertQPointF(dataStream, enemyList[i].pos);
    }

    dataStream << playersInfoMap.count();
    for(auto key : playersInfoMap.keys()) {
        insertQPointF(dataStream, playersInfoMap[key].pos);
        dataStream << playersInfoMap[key].id;
        dataStream << playersInfoMap[key].currentScore;
    }
    //dataStream << obstacleList[0].pos.toPoint().x() << obstacleList[0].pos.toPoint().y();
}


void GameState::extractFromDataStream( QDataStream& dataStream )
{
    dataStream >> playerID;

    quint32 listCount = 0;
    dataStream >> listCount;
    for(int i = 0; i < listCount; ++i) {
        ObstacleInfo obstacleInfo;
        extractQPointF(dataStream, obstacleInfo.pos);
        obstacleList.append(obstacleInfo);
    }

    dataStream >> listCount;
    for(int i = 0; i < listCount; ++i) {
        BulletInfo bulletInfo;
        extractQPointF(dataStream, bulletInfo.pos);
        extractQPointF(dataStream, bulletInfo.direction);
        bulletList.append(bulletInfo);
    }

    dataStream >> listCount;
    for(int i = 0; i < listCount; ++i) {
        EnemyInfo enemyInfo;
        extractQPointF(dataStream, enemyInfo.pos);
        enemyList.append(enemyInfo);
    }

    dataStream >> listCount;
    for(int i = 0; i < listCount; ++i) {
        PlayerInfo playerInfo;
        extractQPointF(dataStream, playerInfo.pos);
        dataStream >> playerInfo.id;
        dataStream >> playerInfo.currentScore;
        playersInfoMap[playerInfo.id] = playerInfo;
    }
}


void GameState::insertQPointF(QDataStream& dataStream, const QPointF& pointf)  const{
    QPoint point = pointf.toPoint();
    dataStream << point.rx() << point.ry();
}

void GameState::extractQPointF(QDataStream& dataStream, QPointF& pointf) {
    int xp,yp;
    dataStream >> xp >> yp;
    pointf.setX(xp);
    pointf.setY(yp);
}
