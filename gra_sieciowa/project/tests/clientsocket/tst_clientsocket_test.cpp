#include <QtTest>
#include "clientsocket.h"
#include "gamestate.h"
// add necessary includes here

class clientsocket_test : public QObject
{
    Q_OBJECT

    GameState* gameState;
    void createGameStateStruct()
    {
        gameState = new GameState;
        QPointF pointObstacle(1, 2);
        ObstacleInfo obstacleInfo = { .pos = pointObstacle};
        QPointF pointEnemy(2,3);
        EnemyInfo enemyInfo = { .pos = pointEnemy };
        QPointF pointBullet(3,4);
        QPointF pointDirection(1,1);
        BulletInfo bulletInfo = { .pos = pointBullet, .direction = pointDirection };
        QPointF pointPlayer(4,5);
        PlayerInfo playerInfo = { .pos = pointPlayer, .id = 1, .currentScore = 10 };
        gameState->bulletList.append(bulletInfo);
        gameState->obstacleList.append(obstacleInfo);
        gameState->enemyList.append(enemyInfo);
        gameState->playersInfoMap[1] = playerInfo;
    }

private slots:
    void convertGameStateToByteArray()
    {
//        createGameStateStruct();
//        ClientSocket clientSocket(0,0);
//        QByteArray tempArray = clientSocket.convertGameStateToByteArray(*gameState,0);
//        GameState tempGameState;
//        memcpy(&tempGameState, &tempArray, sizeof(GameState));
//        QVERIFY(tempGameState.obstacleList.at(0).pos.x() == 1);
//        QVERIFY(tempGameState.obstacleList.at(0).pos.y() == 2);
//        QVERIFY(tempGameState.enemyList.at(0).pos.x() == 2);
//        QVERIFY(tempGameState.enemyList.at(0).pos.y() == 3);
//        QVERIFY(tempGameState.bulletList.at(0).pos.x() == 3);
//        QVERIFY(tempGameState.bulletList.at(0).pos.y() == 4);
//        QVERIFY(tempGameState.bulletList.at(0).direction.x() == 1);
//        QVERIFY(tempGameState.bulletList.at(0).direction.y() == 1);
//        QVERIFY(tempGameState.playersInfoMap[1].pos.x() == 4);
//        QVERIFY(tempGameState.playersInfoMap[1].pos.y() == 5);
//        QVERIFY(tempGameState.playersInfoMap[1].id == 1);
//        QVERIFY(tempGameState.playersInfoMap[1].currentScore == 10);


    }


};


QTEST_APPLESS_MAIN(clientsocket_test)

#include "tst_clientsocket_test.moc"
