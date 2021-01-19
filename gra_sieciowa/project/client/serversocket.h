#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include "socket.h"


class ServerSocket : public Socket
{
    Q_OBJECT
public:
    ServerSocket(const QHostAddress &address, quint16 port,
            QObject *parent);


signals:

};

#endif // SERVERSOCKET_H
