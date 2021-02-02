#include "score.h"

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{

}

void Score::setupScore(int currentScore)
{
    this->setPlainText(QString("Current score:") + QString::number(currentScore));
}
