#include "serversocket.h"
#include <QDebug>
ServerSocket::ServerSocket(const QHostAddress &address, quint16 port,
                           QObject *parent) : Socket(parent)
{

     tcpSocket->connectToHost(address, port);
     tcpSocket->waitForConnected();
     connect(this,SIGNAL(message(const QString&)), this, SLOT(onMessage(const QString&)));
     connect(this,SIGNAL(message(const QByteArray&)), this, SLOT(onMessage(const QByteArray&)));
}

void ServerSocket::onMessage(const QString& message) const
{
    qDebug() << message;
}

void ServerSocket::onMessage(const QByteArray& data) const
{
    emit newGameState(data);
}

void ServerSocket::sendPlayerAction(const PlayerAction &playerAction) const
{
    sendData(QByteArray(static_cast<char*>((void*)&playerAction), sizeof(playerAction)));
}

GameState ServerSocket::parseGameState(const QByteArray& data) const
{
    GameState gameState;
    memcpy(&gameState,data.data(), sizeof(gameState));
    return gameState;
}
