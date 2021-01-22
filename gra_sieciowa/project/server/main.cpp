#include <QApplication>


#include "game.h"
#include "network.h"

Game * newGame;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    newGame = new Game();
    newGame->initGame();
    newGame->generateObstacles(2);
    newGame->addNewPlayer(QPoint(newGame->settings->player_point), QSize(newGame->settings->player_size));
    newGame->addNewPlayer(QPoint(newGame->settings->player_point), QSize(newGame->settings->player_size));
    newGame->show();

    newGame->setFocusPolicy(Qt::NoFocus);



    return app.exec();
}
