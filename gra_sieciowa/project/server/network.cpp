#include "network.h"

Network::Network(quint16 port)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    if (!listen(QHostAddress::Any, port))
    {
           close();
           qDebug() << "Error in listen!";
    }

    qDebug() << "Server started on port" << serverPort();
}

void Network::onNewConnection()
{
    QTcpSocket* clientSock = nextPendingConnection();
    ClientSocket* sockHandle = new ClientSocket(clientSock);

    this->clients.push_back(sockHandle);

    // emitujemy sygnal na nowego klienta TODO
    qDebug() << "Client connected!";
    connect(sockHandle, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}

void Network::onDisconnected()
{
    qDebug() << "ServerNetwork::onDisconnected" << endl;
    auto client = static_cast<ClientSocket*>(sender()); // nw czy sender() zadziala bo do QObject posyłamy nullptr ale to Qt wiec kij wie co tam sie dzieje
    clients.removeOne(client);
    delete client;
}

void Network::sendAll(const QString &message) const
{
    for (auto socket : clients)
    {
        socket->sendString(message);
    }
}
