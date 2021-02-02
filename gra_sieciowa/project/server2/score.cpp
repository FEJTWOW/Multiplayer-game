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

void Score::setupScore(int playerID)
{
    newGame->playerScoresMap[playerID]->setPlainText(QString("Current score:") + QString::number((newGame->playerScoresMap[playerID]->curr_score)));
    newGame->playerScoresMap[playerID]->setDefaultTextColor(newGame->settings->score_color);
    newGame->playerScoresMap[playerID]->setFont(newGame->settings->score_font);
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
