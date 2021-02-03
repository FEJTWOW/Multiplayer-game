#ifndef BASEGAME_H
#define BASEGAME_H

#include <QObject>

class BaseGame : public QObject
{
    Q_OBJECT
public:
    explicit BaseGame(QObject *parent = nullptr);

signals:

};

#endif // BASEGAME_H
