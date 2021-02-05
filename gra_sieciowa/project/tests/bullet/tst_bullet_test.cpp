#include <QtTest>

#include <QPointF>
#include "bullet.h"
#include "gameSettings.h"

class bullet_test : public QObject
{
    Q_OBJECT

private slots:
    void bulletCreation()
    {
        Bullet b(1, 0, {0, 0});
    }

    void bulletOrientation() {
        QPointF playerPos = { 0, 0 };
        Bullet b1(0, 0, playerPos); // bullet facing up

        Bullet b2(1, 0, playerPos); // bullet facing left

        QCOMPARE(b1.rect().width(), bulletSize.width());
        QCOMPARE(b1.rect().height(), bulletSize.height());

        QCOMPARE(b2.rect().width(), bulletSize.height());
        QCOMPARE(b2.rect().height(), bulletSize.width());
    }

    void bulletSpawn() {
        QPointF playerPos = { 0, 0 };

        Bullet b1(0, 0, playerPos); // bullet facing up

        Bullet b2(1, 0, playerPos); // bullet facing left

        Bullet b3(2, 0, playerPos); // bullet facing down

        Bullet b4(3, 0, playerPos); // bullet facing right

        QVERIFY(b1.pos().y() < playerPos.y());
        QVERIFY(b2.pos().x() < playerPos.x());
        QVERIFY(b3.pos().y() > playerPos.y());
        QVERIFY(b4.pos().x() > playerPos.x());
    }

    void bulletMove() {
        QPointF playerPos = { 0, 0 };

        Bullet b1(0, 0, playerPos); // bullet facing up

        Bullet b2(1, 0, playerPos); // bullet facing left

        auto bx1 = b1.pos().x();
        auto by1 = b1.pos().y();

        auto bx2 = b2.pos().x();
        auto by2 = b2.pos().y();

        b1.move();
        b2.move();

        QCOMPARE(bx1, b1.pos().x());
        QCOMPARE(by1 - bulletSpeed, b1.pos().y());

        QCOMPARE(bx2 - bulletSpeed, b2.pos().x());
        QCOMPARE(by2, b2.pos().y());

        b1.move();
        b1.move();

        QCOMPARE(bx1, b1.pos().x());
        QCOMPARE(by1 - 3*bulletSpeed, b1.pos().y());
    }

};


QTEST_APPLESS_MAIN(bullet_test)

#include "tst_bullet_test.moc"
