#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>

class Obstacle : public QObject
{
    Q_OBJECT
public:
    explicit Obstacle(QObject *parent = nullptr);

signals:

};

#endif // OBSTACLE_H
