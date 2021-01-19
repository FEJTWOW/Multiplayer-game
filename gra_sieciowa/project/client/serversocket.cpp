#include "serversocket.h"

ServerSocket::ServerSocket(const QHostAddress &address, quint16 port,
                           QObject *parent) : Socket(parent)
{
     tcpSocket->connectToHost(address, port);
}
