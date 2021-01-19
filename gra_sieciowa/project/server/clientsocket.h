#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socket.h"

// for future improvement
class ClientSocket : public Socket
{
    Q_OBJECT

    public:
        explicit ClientSocket(QTcpSocket* socket, QObject *parent = nullptr) : Socket(parent, socket) {}
};

#endif // CLIENTSOCKET_H
