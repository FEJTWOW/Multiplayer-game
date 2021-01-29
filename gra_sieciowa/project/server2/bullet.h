#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Bullet(QPointF moveSet, int player_id);
    QPointF moveSet;
    int player_id;

};

#endif // BULLET_H
