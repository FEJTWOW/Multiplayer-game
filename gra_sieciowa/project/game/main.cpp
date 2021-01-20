#include <QApplication>


#include "game.h"
#include <QDebug>

Game * newGame;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "Elo!";
    newGame = new Game();
    newGame->initGame();
    newGame->generateObstacles(2);
    newGame->addNewPlayer(QPoint(newGame->settings->player_point), QSize(newGame->settings->player_size));
    newGame->show();



    return app.exec();
}
