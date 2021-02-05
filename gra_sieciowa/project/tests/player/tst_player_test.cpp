#include <QtTest>

#include "player.h"
#include "gameSettings.h"

class player_test : public QObject
{
    Q_OBJECT


private slots:
    void playerCreation()
    {
        QPoint pos = { 0, 0 };
        QSize size = { playerSize.width(), playerSize.height() };

        Player p(pos, size, 0);
    }

    void playerMove() {
        QPoint pos = { 0, 0 };
        QSize size = { playerSize.width(), playerSize.height() };
        int speed = 10;

        Player p(pos, size, 0);

        auto px = p.pos().x();
        auto py = p.pos().y();

        p.move(speed);

        QCOMPARE(px, p.pos().x());
        QCOMPARE(py, p.pos().y());

        p.horizontalMove = 1; // move left

        p.move(speed);

        QCOMPARE(px + speed, p.pos().x());
        QCOMPARE(py, p.pos().y());

        p.move(speed);
        p.move(speed);

        QCOMPARE(px + 3*speed, p.pos().x());
        QCOMPARE(py, p.pos().y());

        px = p.pos().x();
        py = p.pos().y();

        p.verticalMove = -1; // move left and up

        p.move(speed);

        QCOMPARE(px + speed, p.pos().x());
        QCOMPARE(py - speed, p.pos().y());
    }

    void playerDontMoveOutsideScreen() {
        QPoint pos = { 1, 1 };
        QSize size = { playerSize.width(), playerSize.height() };
        int speed = 10;

        Player p(pos, size, 0);

        p.setPos(pos);

        p.verticalMove = 1;
        p.horizontalMove = 1; // move towards 0,0

        p.move(speed);

        QVERIFY(p.pos().x() >= 0);
        QVERIFY(p.pos().y() >= 0);

        p.move(speed);
        p.move(speed);


        QVERIFY(p.pos().x() >= 0);
        QVERIFY(p.pos().y() >= 0);

        auto posX = screenSize.width() - speed/2;
        auto posY = screenSize.height() - speed/2; // position nearby right upper corner
        p.setPos(posX, posY);

        p.verticalMove = -1;
        p.horizontalMove = -1;

        p.move(speed);

        QVERIFY(p.pos().x() <= screenSize.width());
        QVERIFY(p.pos().y() <= screenSize.height());

        p.move(speed);
        p.move(speed);

        QVERIFY(p.pos().x() <= screenSize.width());
        QVERIFY(p.pos().y() <= screenSize.height());
    }

    void testDead() {
        QPoint pos = { 1, 1 };
        QSize size = { playerSize.width(), playerSize.height() };

        Player p(pos, size, 0);

        p.score = 100;

        p.kill();

        QVERIFY(p.dead);
        QVERIFY(p.score == 100 - scoreKillValue);
    }

};


QTEST_APPLESS_MAIN(player_test)

#include "tst_player_test.moc"
