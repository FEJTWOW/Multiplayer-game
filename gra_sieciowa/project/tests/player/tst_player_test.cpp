#include <QtTest>

// add necessary includes here

class player_test : public QObject
{
    Q_OBJECT


private slots:
    void test_case1()
    {
        return;
    }

};


QTEST_APPLESS_MAIN(player_test)

#include "tst_player_test.moc"
