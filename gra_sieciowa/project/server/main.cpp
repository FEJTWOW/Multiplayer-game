#include "mainwindow.h"


#include <QApplication>
#include "network.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Network network(12345);
    return app.exec();
}
