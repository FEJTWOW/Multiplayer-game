#include <QApplication>

#include "serversocket.h"
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerSocket sock(QHostAddress::LocalHost,12345, nullptr);
    return app.exec();
}
