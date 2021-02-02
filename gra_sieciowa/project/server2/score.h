#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent = 0);
    void setupScore(int playerID);
    void increasePassive();
    void increaseKill();
    int getScore();
    int curr_score;
};

#endif // SCORE_H
