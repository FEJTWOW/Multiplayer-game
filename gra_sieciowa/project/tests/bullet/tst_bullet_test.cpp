#include <QtTest>

// add necessary includes here

class bullet_test : public QObject
{
    Q_OBJECT

private slots:
    void test_case1()
    {
        return;
    }

};


QTEST_APPLESS_MAIN(bullet_test)

#include "tst_bullet_test.moc"
