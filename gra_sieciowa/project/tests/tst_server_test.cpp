#include <QtTest>
#include "socket.h"

// add necessary includes here

class server_test : public QObject
{
    Q_OBJECT

public:
    server_test();
    ~server_test();

private slots:
    void test_case1();

};

server_test::server_test()
{

}

server_test::~server_test()
{

}

void server_test::test_case1()
{
    Socket* socket = new Socket();
}

QTEST_APPLESS_MAIN(server_test)

#include "tst_server_test.moc"
