#include "mainwindow.h"

#include <QApplication>
#include "servergame.h"

ServerGame * newGame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
