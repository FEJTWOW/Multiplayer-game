#include <QtTest>
#include "servergame.h"


// add necessary includes here

class servergame_test : public QObject
{
    Q_OBJECT

    ServerGame* serverGame;
    QApplication* extremeDummy;
    void createApplication()
    {
        int dummy = 1;
        int& superDummy = dummy;
        extremeDummy = new QApplication(superDummy,nullptr);
        serverGame = new ServerGame();
        serverGame->initGame();
    }

    void deleteApplication()
    {
        delete serverGame;
        delete extremeDummy;
    }

private slots:
    void initGameTest()
    {
        createApplication();
        QList<QGraphicsItem *> allItems = serverGame->graphicsScene->items();
        QCOMPARE(allItems.length(),0);
        deleteApplication();
    }

    void addNewPlayerTest()
    {
        createApplication();
        serverGame->addNewPlayer(0);
        QCOMPARE(serverGame->playersMap[0]->score,0);
        QList<QGraphicsItem *> allItems = serverGame->graphicsScene->items();
        QCOMPARE(allItems.length(),1);
        deleteApplication();
    }

    void spawnEnemyTest()
    {
        createApplication();
        QCOMPARE(serverGame->numOfEnemies,0);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,1);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,2);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,3);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,4);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,5);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,6);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,7);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,8);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,9);
        QList<QGraphicsItem *> allItems = serverGame->graphicsScene->items();
        QCOMPARE(allItems.length(),9);
        serverGame->spawnEnemy();
        QCOMPARE(serverGame->numOfEnemies,9);
        allItems = serverGame->graphicsScene->items();
        QCOMPARE(allItems.length(),9);
        deleteApplication();
    }

    void updatePointsTest()
    {
        createApplication();
        serverGame->addNewPlayer(0);
        serverGame->addNewPlayer(2);

        serverGame->updatePoints();
        QCOMPARE(serverGame->playersMap[0]->score, scorePassiveValue);
        QCOMPARE(serverGame->playersMap[2]->score, scorePassiveValue);
        serverGame->playersMap[0]->dead = true;

        serverGame->updatePoints();
        QCOMPARE(serverGame->playersMap[0]->score, scorePassiveValue);
        QCOMPARE(serverGame->playersMap[2]->score, 2*scorePassiveValue);
        deleteApplication();
    }

    void collisionTest() {
        createApplication();
        serverGame->addNewPlayer(0);
        serverGame->addNewPlayer(2);


        serverGame->playersMap[2]->setPos(serverGame->playersMap[0]->pos());

        serverGame->checkAllCollisions();

        QVERIFY(serverGame->playersMap[2]->dead);
        QVERIFY(serverGame->playersMap[0]->dead);
    }

    void fireBulletsTest() {
        createApplication();
        serverGame->addNewPlayer(0);

        serverGame->playersMap[0]->shootingDirection = 0;

        serverGame->fireBullet(serverGame->playersMap[0]);

        auto all = serverGame->graphicsScene->items();

        Bullet* b;

        for(int i = 0; i < all.length(); i++) {
            if(typeid(*(all[i])) == typeid(Bullet))
                b = dynamic_cast<Bullet *>(all[i]);
        }

        QVERIFY(b);
    }

    void moveTest() {
        createApplication();
        serverGame->addNewPlayer(0);

        serverGame->playersMap[0]->shootingDirection = 0;

        serverGame->fireBullet(serverGame->playersMap[0]);

        auto all = serverGame->graphicsScene->items();

        Bullet* b;

        for(int i = 0; i < all.length(); i++) {
            if(typeid(*(all[i])) == typeid(Bullet))
                b = dynamic_cast<Bullet *>(all[i]);
        }

        QVERIFY(b);

        auto pos = b->pos();

        serverGame->moveAssets();

        QVERIFY(pos.y() != b->pos().y());
    }

    void killPlayerTest() {
        createApplication();
        serverGame->addNewPlayer(0);

        serverGame->killPlayer(serverGame->playersMap[0]);

        QVERIFY(serverGame->playersMap[0]->dead);
    }
};

QTEST_APPLESS_MAIN(servergame_test)

#include "tst_servergame_test.moc"
