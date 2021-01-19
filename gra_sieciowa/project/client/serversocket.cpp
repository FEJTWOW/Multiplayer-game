#include "serversocket.h"

ServerSocket::ServerSocket(const QHostAddress &address, quint16 port,
                           QObject *parent) : Socket(parent)
{
     tcpSocket->connectToHost(address, port);
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
