#include <QtTest>

// add necessary includes here

class clientgame_test : public QObject
{
    Q_OBJECT


private slots:
    void test_case1()
    {
        return;
    }

};


QTEST_APPLESS_MAIN(clientgame_test)

#include "tst_clientgame_test.moc"
