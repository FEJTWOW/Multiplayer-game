#include "clientsocket.h"
#include <QDataStream>
#include <QByteArray>

void ClientSocket::sendGameState(const GameState& gameState, int playerID) const
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    gameState.insertToDataStream(stream, playerID);

    sendData(byteArray);
}
