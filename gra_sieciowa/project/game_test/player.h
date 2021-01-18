#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
};

#endif // PLAYER_H
