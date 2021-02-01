#include "score.h"
#include "game.h"

#include <QString>
#include <QFont>
#include <QDebug>

extern Game * newGame;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    curr_score = 0;
}

void Score::setupScore()
{
    int numOfPlayers = newGame->network->clients.length()-1;
    newGame->playerScores[numOfPlayers]->setPlainText(QString("Current score:") + QString::number((newGame->playerScores[numOfPlayers]->curr_score)));
    newGame->playerScores[numOfPlayers]->setDefaultTextColor(newGame->settings->score_color);
    newGame->playerScores[numOfPlayers]->setFont(newGame->settings->score_font);
}

void Score::increasePassive()
{
    curr_score += newGame->settings->score_passive_value;
    setPlainText(QString("Current score:") + QString::number(curr_score));

}

void Score::increaseKill()
{
    curr_score += newGame->settings->score_kill_value;
    setPlainText(QString("Current score:") + QString::number(curr_score));
}

int Score::getScore()
{
    return curr_score;
}
