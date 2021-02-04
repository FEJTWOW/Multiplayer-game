#include <QtTest>

// add necessary includes here

class network_test : public QObject
{
    Q_OBJECT

private slots:
    void test_case1()
    {
        return;
    }

};


QTEST_APPLESS_MAIN(network_test)

#include "tst_network_test.moc"
