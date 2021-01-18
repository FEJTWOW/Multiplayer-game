#include <QApplication>


#include "game.h"

Game * newGame;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    newGame = new Game();
    newGame->show();



    return app.exec();
}
