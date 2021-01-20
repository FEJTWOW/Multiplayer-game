#include "serversocket.h"

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
    qDebug() << "Jestę klientem i czytam!";
    qDebug() << message;
}

void ServerSocket::onMessage(const QByteArray& data) const
{
    qDebug() << "Jestę klientem i czytam se data!";
    qDebug() << data;
}

void ServerSocket::sendPlayerAction(const PlayerAction &playerAction) const
{
//    QByteArray byteArray;

//    QDataStream stream(&byteArray, QIODevice::WriteOnly);
//    stream.setVersion(QDataStream::Qt_5_9);

//    stream << playerAction.action << playerAction.posX << playerAction.posY;
    sendData(QByteArray(static_cast<char*>((void*)&playerAction), sizeof(playerAction)));

}
