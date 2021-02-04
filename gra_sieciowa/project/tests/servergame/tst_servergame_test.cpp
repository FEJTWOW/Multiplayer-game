#include <QtTest>

// add necessary includes here

class servergame_test : public QObject
{
    Q_OBJECT


private slots:
    void test_case1()
    {
        return;
    }

};

QTEST_APPLESS_MAIN(servergame_test)

#include "tst_servergame_test.moc"
