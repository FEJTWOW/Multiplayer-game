#include "clientsocket.h"


void ClientSocket::sendGameState(const GameState& gameState) const
{
    sendData(QByteArray(static_cast<char*>((void*)&gameState), sizeof(gameState)));
}


//void ClientSocket::onDisconnected() {
//    qDebug() << "ClientSocket disconnected";
//}
