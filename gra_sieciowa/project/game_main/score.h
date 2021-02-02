#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include "settings.h"

class Score: public QGraphicsTextItem
{

public:
    Score(QGraphicsItem * parent = 0);
    void setupScore(int currentScore);
};

#endif // SCORE_H
