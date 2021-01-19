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
    newGame->playerScores[newGame->numOfPlayers]->setPlainText(QString("Current score:") + QString::number((newGame->playerScores[newGame->numOfPlayers]->curr_score)));
    newGame->playerScores[newGame->numOfPlayers]->setDefaultTextColor(newGame->settings->score_color);
    newGame->playerScores[newGame->numOfPlayers]->setFont(newGame->settings->score_font);
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
