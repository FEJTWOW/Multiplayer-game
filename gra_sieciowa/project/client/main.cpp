#include <QApplication>

#include "serversocket.h"
#include <QHostAddress>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerSocket sock(QHostAddress::LocalHost,12345, nullptr);
    for (int i=0; i<2; ++i)
    {
        if (i==0)
        {
            sock.sendString("kupa");
            QThread::sleep(2);
        }
        if (i==1)
        {
            sock.sendData(QByteArray("aab"));
            QThread::sleep(2);
        }
    }
    sock.sendString("kupa");
    QThread::sleep(2);
    sock.sendData(QByteArray("aab"));
    return app.exec();
}
