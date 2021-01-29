#include "network.h"

Network::Network(quint16 port, QObject* parent) : QTcpServer(parent)
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

    emit newClientConnected(clients.indexOf(sockHandle));
    qDebug() << "Client connected!";
    connect(sockHandle, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(sockHandle, SIGNAL(message(const QString&)), this, SLOT(onMessage(const QString&)));
    connect(sockHandle, SIGNAL(message(const QByteArray&)), this, SLOT(onMessage(const QByteArray&)));

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

void Network::sendAll(const QByteArray &data) const
{
    for (auto socket : clients)
    {
        socket->sendData(data);
    }
}

void Network::sendAll(const GameState& gameState) const
{
    for(auto socket : clients)
    {
        socket->sendGameState(gameState);
    }
}

void Network::send(const int id, const int game_id) const
{
   clients.at(id)->sendData(QByteArray(static_cast<char *>((void*)&game_id), sizeof(game_id)));
}


void Network::onMessage(const QString& message) const
{
    //sendAll(message);
    qDebug() << "String" << message;
}


void Network::onMessage(const QByteArray& data) const
{
    //qDebug() << "Data" << data;

    PlayerAction pA = parsePlayerAction(data);
    //GameState test{1,2,3,4,200,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    emit playerMadeAction(pA);
    //sendAll(test);
}

PlayerAction Network::parsePlayerAction(const QByteArray& data) const
{
    PlayerAction playerAction;

    memcpy(&playerAction,data.data(), sizeof(playerAction));
    //qDebug() << playerAction.actions << playerAction.posX << playerAction.posY;
    return playerAction;

}

