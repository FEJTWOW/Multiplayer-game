#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include "clientsocket.h"

class Network : public QTcpServer
{
    Q_OBJECT
public:
    explicit Network(quint16 port = 0); // port jest 2 bajtowa liczba
    quint16 port() const { return serverPort(); }


signals:

public slots:
    void sendAll(const QString &message) const;
    void onNewConnection();
    void onDisconnected();
    void onMessage(const QString& message) const;

protected:
    QList<Socket*> clients;
};

#endif // NETWORK_H
