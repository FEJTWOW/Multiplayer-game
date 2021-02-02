#include "serversocket.h"
#include <QDebug>
ServerSocket::ServerSocket(const QHostAddress &address, quint16 port,
                           QObject *parent) : Socket(parent)
{

     tcpSocket->connectToHost(address, port);
     tcpSocket->waitForConnected();
     connect(this,SIGNAL(message(const QString&)), this, SLOT(onMessage(const QString&)));
     connect(this,SIGNAL(message(const QByteArray&)), this, SLOT(onMessage(const QByteArray&)));
     qDebug() << "Debuguje Server Socket koniec!";
}

void ServerSocket::onMessage(const QString& message) const
{
//    qDebug() << "CZYTAM STRINGA";
    qDebug() << message;
}

void ServerSocket::onMessage(const QByteArray& data) const
{

    if (data.size() == 4)
    {
        int ourId = 5;
        memcpy(&ourId, data.data(), data.size());
        emit newPlayerId(ourId);
//        qDebug() << "Got id from server" << ourId;
    }
    else if (data.size() == sizeof(GameState))
    {
//        qDebug() << "Rozmiar gameState!" << data.size();
        emit newGameState(data);
    } else
    {
       qDebug() << "Dostalem kupe i nie dzialam!" << data.size();
    }

}

void ServerSocket::sendPlayerAction(const PlayerAction &playerAction) const
{
//    QByteArray byteArray;

//    QDataStream stream(&byteArray, QIODevice::WriteOnly);
//    stream.setVersion(QDataStream::Qt_5_9);

//    stream << playerAction.action << playerAction.posX << playerAction.posY;w
    sendData(QByteArray(static_cast<char*>((void*)&playerAction), sizeof(playerAction)));

}

GameState ServerSocket::parseGameState(const QByteArray& data) const
{
    GameState gameState;

    memcpy(&gameState,data.data(), sizeof(gameState));
    //qDebug() << gameState.bulletPosition[1][1] << gameState.playerPosition[1][2];
    return gameState;
}
