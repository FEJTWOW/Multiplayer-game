#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socket.h"
#include "gamestate.h"

// for future improvement
class ClientSocket : public Socket
{
    Q_OBJECT

    public:
        explicit ClientSocket(QTcpSocket* socket, QObject *parent = nullptr) : Socket(parent, socket) {}
        void sendGameState(const GameState& gameState, int playerID) const;

//    void onDisconnected() Q_DECL_OVERRIDE;
};

#endif // CLIENTSOCKET_H
