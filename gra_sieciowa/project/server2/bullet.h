#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Bullet(int direction, int player_id, const QPointF& playerPos);
    QPointF moveSet;
    int direction;
    int player_id;
    void move();
};

#endif // BULLET_H
