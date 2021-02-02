#include <QtTest>
#include "socket.h"
#include "clientsocket.h"
#include "enemy.h"
#include "settings.h"


// add necessary includes here

class SertTest : public QObject
{
    Q_OBJECT

public:
    SertTest();
    ~SertTest();

private slots:
    void test_case1();

};

SertTest::SertTest()
{

}

SertTest::~SertTest()
{

}

void SertTest::test_case1()
{
    Socket* socket = new Socket();
    //ClientSocket* clientSocket = new ClientSocket();
    //Enemy* enemy = new Enemy();
    Settings* settings = new Settings();
}

QTEST_APPLESS_MAIN(SertTest)

#include "tst_serttest.moc"
