#include <QtTest>
#include "settings.h"
#include "socket.h"
#include "score.h"
#include "network.h"

// add necessary includes here

class ServerTests : public QObject
{
    Q_OBJECT

public:
    ServerTests();
    ~ServerTests();

private slots:
    void test_case1();

};

ServerTests::ServerTests()
{

}

ServerTests::~ServerTests()
{

}

void ServerTests::test_case1()
{
    //Settings* settings = new Settings();
    Socket* s = new Socket();
    //Score* score = new Score();
    Network* n = new Network();
}

QTEST_APPLESS_MAIN(ServerTests)

#include "tst_servertests.moc"
