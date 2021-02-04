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
        clientGame->gameState.playersInfoMap[0] = playerInfo;
    }

private slots:
    void initGameTest()
    {
        createApplication();
        clientGame->initGame(QHostAddress("127.0.0.1"),12345);
        QCOMPARE(clientGame->horizontal,0);
        QCOMPARE(clientGame->vertical,0);
        QCOMPARE(clientGame->shooting,0);
        QCOMPARE(clientGame->shootDirection,0);
        QVERIFY(clientGame->clientGraphicsScene != nullptr);
    }

    void moveTest()
    {

        clientGame->setFocus();
        QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        extremeDummy->sendEvent(clientGame,event);
        extremeDummy->processEvents();
        clientGame->move();
        QCOMPARE(clientGame->vertical,-1);
    }

    void renderGameStateTest()
    {
        createGameStateStruct();
        clientGame->renderGameState();
        QList<QGraphicsItem *> allItems = clientGame->clientGraphicsScene->items();
        QCOMPARE(allItems.length(),5);
    }


};


QTEST_APPLESS_MAIN(clientgame_test)

#include "tst_clientgame_test.moc"
