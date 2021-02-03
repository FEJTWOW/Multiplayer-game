#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include "socket.h"
#include "playeraction.h"
#include "gamestate.h"

class ServerSocket : public Socket
{
    Q_OBJECT
public:
    ServerSocket(const QHostAddress &address, quint16 port,
            QObject *parent);

    void sendPlayerAction(const PlayerAction& playerAction) const;
    GameState parseGameState(const QByteArray& data) const;

signals:
    void newGameState(const QByteArray& data) const;
    void newPlayerId(const int& playerId) const;

public slots:
    void onMessage(const QString& message) const;
    void onMessage(const QByteArray& data) const;
};

#endif // SERVERSOCKET_H
