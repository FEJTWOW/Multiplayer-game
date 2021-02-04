#include <QtTest>
#include "socket.h"
#include <QTcpSocket>
// add necessary includes here

class tst_socket_test : public QObject
{
    Q_OBJECT

private slots:
    void onReadyReadTest()
    {
        QTcpSocket* tcpSocket = new QTcpSocket();
        Socket socket(nullptr,tcpSocket);
        QVERIFY(tcpSocket == socket.tcpSocket);

        QSignalSpy spy(&socket, SIGNAL(message(const QByteArray&)));
        socket.onReadyRead();
        QCOMPARE(spy.count(), 1);
    }

    void onDisconnectedTest()
    {
        QTcpSocket* tcpSocket = new QTcpSocket();
        Socket socket(nullptr,tcpSocket);
        QSignalSpy spy(&socket, SIGNAL(disconnected()));
        socket.onDisconnected();
        QCOMPARE(spy.count(), 1);
    }

};


QTEST_APPLESS_MAIN(tst_socket_test)

#include "tst_socket_test.moc"
