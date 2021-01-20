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
//    qDebug() << "Czytam se";
    emit message(tcpSocket->readAll());
}

void Socket::onDisconnected() const
{
    qDebug() << "disconnected!";
}


void Socket::sendString(const QString& string)
{
    qDebug() << "lel";
    this->tcpSocket->write(string.toUtf8().constData(),string.length());
}

void Socket::sendData(const QByteArray& data) const
{
//    qDebug() << "Wysyłanie" << data;

    tcpSocket->write(data);
}
