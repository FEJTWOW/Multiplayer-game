#include "score.h"
#include <QDebug>
Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{

}

void Score::setupScore(int currentScore)
{
    qDebug() << "Kurwa " << currentScore;
//    this->setPlainText(QString("Current score:") + QString::number(currentScore));
}
