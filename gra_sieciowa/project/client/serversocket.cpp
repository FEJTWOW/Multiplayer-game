#include "serversocket.h"

ServerSocket::ServerSocket(const QHostAddress &address, quint16 port,
                           QObject *parent) : Socket(parent)
{
     tcpSocket->connectToHost(address, port);
     connect(this,SIGNAL(message(const QString&)), this, SLOT(onMessage(const QString&)));
}

void ServerSocket::onMessage(const QString& message) const
{
    qDebug() << "Jestę klientem i czytam!";
    qDebug() << message;
}
