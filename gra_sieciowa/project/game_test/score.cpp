#include "score.h"
#include "game.h"

#include <QString>
#include <QFont>
#include <QDebug>

extern Game * newGame;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{


}

void Score::setupScore()
{
    qDebug() << newGame->numOfPlayers << " " << newGame->playerScores[newGame->numOfPlayers]->curr_score;
    newGame->playerScores[newGame->numOfPlayers]->setPlainText(QString("Current score:") + QString::number((newGame->playerScores[newGame->numOfPlayers]->curr_score)));
    newGame->playerScores[newGame->numOfPlayers]->setDefaultTextColor(Qt::red);
    qDebug() << "score1";
    newGame->playerScores[newGame->numOfPlayers]->setFont(QFont("System", 14));
}

void Score::increase()
{
    curr_score += 10;
    setPlainText(QString("Current score:") + QString::number(curr_score));

}

int Score::getScore()
{
    return curr_score;
}
