#include <QtTest>
#include <QHostAddress>
#include "clientgame.h"
#include <QApplication>
#include "bullet.h"
#include "enemy.h"
#include "obstacle.h"


// add necessary includes here

class clientgame_test : public QObject
{
    Q_OBJECT

    ClientGame* clientGame;
    QApplication* extremeDummy;

    void createApplication()
    {
        int dummy = 1;
        int& superDummy = dummy;
        extremeDummy = new QApplication(superDummy,nullptr);
        clientGame = new ClientGame(nullptr);
        clientGame->initGame(QHostAddress("127.0.0.1"),12345);
    }

    void deleteApplication()
    {
        delete extremeDummy;
        delete clientGame;
    }

    void createGameStateStruct()
    {
        QPointF pointObstacle(1, 2);
        ObstacleInfo obstacleInfo = { .pos = pointObstacle};
        QPointF pointEnemy(2,3);
        EnemyInfo enemyInfo = { .pos = pointEnemy };
        QPointF pointBullet(3,4);
        QPointF pointDirection(1,1);
        BulletInfo bulletInfo = { .pos = pointBullet, .direction = pointDirection };
        QPointF pointPlayer(4,5);
        PlayerInfo playerInfo = { .pos = pointPlayer, .id = 1, .currentScore = 10 };
        clientGame->gameState.bulletList.append(bulletInfo);
        clientGame->gameState.obstacleList.append(obstacleInfo);
        clientGame->gameState.enemyList.append(enemyInfo);
        clientGame->gameState.playersInfoMap[1] = playerInfo;
    }

private slots:
    void initGameTest()
    {
        createApplication();
        QCOMPARE(clientGame->horizontal,0);
        QCOMPARE(clientGame->vertical,0);
        QCOMPARE(clientGame->shooting,0);
        QCOMPARE(clientGame->shootDirection,0);
        QVERIFY(clientGame->clientGraphicsScene != nullptr);
        deleteApplication();
    }

    void moveTest()
    {
        createApplication();
        clientGame->setFocus();
        QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        extremeDummy->sendEvent(clientGame,event);
        extremeDummy->processEvents();
        clientGame->move();
        QCOMPARE(clientGame->vertical,-1);
        deleteApplication();
    }

    void clearGameStateTest()
    {
        createApplication();
        createGameStateStruct();
        clientGame->clearGameState();

        QVERIFY(clientGame->gameState.enemyList.empty() == true);
        QVERIFY(clientGame->gameState.bulletList.empty() == true);
        QVERIFY(clientGame->gameState.obstacleList.empty() == true);
        QVERIFY(clientGame->gameState.playersInfoMap.empty() == true);
        deleteApplication();
    }

    void renderGameStateTest()
    {
        createApplication();
        createGameStateStruct();
        clientGame->renderGameState();
        QList<QGraphicsItem *> allItems = clientGame->clientGraphicsScene->items();
        QCOMPARE(allItems.length(),5);
        deleteApplication();
    }


    void parseGameStateTest()
    {
        createApplication();
        createGameStateStruct();
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        clientGame->gameState.insertToDataStream(stream, 0);
        clientGame->clearGameState();
        clientGame->parseGameState(byteArray);
        QVERIFY(clientGame->gameState.obstacleList.at(0).pos.x() == 1);
        QVERIFY(clientGame->gameState.obstacleList.at(0).pos.y() == 2);
        QVERIFY(clientGame->gameState.enemyList.at(0).pos.x() == 2);
        QVERIFY(clientGame->gameState.enemyList.at(0).pos.y() == 3);
        QVERIFY(clientGame->gameState.bulletList.at(0).pos.x() == 3);
        QVERIFY(clientGame->gameState.bulletList.at(0).pos.y() == 4);
        QVERIFY(clientGame->gameState.bulletList.at(0).direction.x() == 1);
        QVERIFY(clientGame->gameState.bulletList.at(0).direction.y() == 1);
        QVERIFY(clientGame->gameState.playersInfoMap[1].pos.x() == 4);
        QVERIFY(clientGame->gameState.playersInfoMap[1].pos.y() == 5);
        QVERIFY(clientGame->gameState.playersInfoMap[1].id == 1);
        QVERIFY(clientGame->gameState.playersInfoMap[1].currentScore == 10);
        deleteApplication();
    }

    void receivedPlayerIdTest()
    {
        createApplication();
        clientGame->receivedPlayerId(2);
        QCOMPARE(clientGame->myPlayerId,2);
        deleteApplication();
    }

    void showScoreTest()
    {
        createApplication();
        clientGame->showScore(10);
        QList<QGraphicsItem *> allItems = clientGame->clientGraphicsScene->items();
        QCOMPARE(allItems.length(),1);
        deleteApplication();
    }

    void createBulletTest()
    {
        createApplication();
        QPointF pointBullet(2,3);
        clientGame->createBullet(pointBullet, 0);
        QList<QGraphicsItem *> allItems = clientGame->clientGraphicsScene->items();
        QCOMPARE(allItems.length(),1);
        deleteApplication();
    }
};


QTEST_APPLESS_MAIN(clientgame_test)

#include "tst_clientgame_test.moc"
