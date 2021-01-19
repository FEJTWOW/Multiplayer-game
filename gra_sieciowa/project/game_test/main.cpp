#include <QApplication>


#include "game.h"

Game * newGame;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    newGame = new Game();
    newGame->initGame();
    newGame->addNewPlayer(QPoint(0,0), QSize(100,100));
    newGame->show();



    return app.exec();
}
