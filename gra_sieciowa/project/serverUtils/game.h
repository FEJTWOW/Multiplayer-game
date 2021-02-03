#ifndef GAME_H
#define GAME_H

#include <QObject>

class game : public QObject
{
    Q_OBJECT
public:
    explicit game(QObject *parent = nullptr);

signals:

};

#endif // GAME_H
