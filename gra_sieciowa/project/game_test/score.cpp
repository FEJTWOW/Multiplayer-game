#include "score.h"

#include <QString>
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    curr_score = 0;

    setPlainText(QString("Current score:") + QString::number(curr_score));
    setDefaultTextColor(Qt::red);
    setFont(QFont("System", 14));
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
