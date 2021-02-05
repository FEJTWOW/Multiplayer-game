#include "socket.h"
#include <QDebug>

Socket::Socket(QObject *parent, QTcpSocket* socket) : QObject(parent)
{
    if(socket == nullptr)
    {
        this->tcpSocket = new QTcpSocket(this);
    }
    else
    {
        this->tcpSocket = socket;
    }

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}


void Socket::onReadyRead()
{
    emit message(tcpSocket->readAll());
}

void Socket::onDisconnected() const
{
    qDebug() << "Socket::onDisconnected!";
    emit disconnected();
}


void Socket::sendString(const QString& string)
{
    qDebug() << "lel";
    this->tcpSocket->write(string.toUtf8().constData(),string.length());
}

void Socket::sendData(const QByteArray& data) const
{
    tcpSocket->write(data);
}
