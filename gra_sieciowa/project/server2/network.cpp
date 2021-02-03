#include "network.h"
#include "gameSettings.h"

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

    if(this->clientsMap.size() >= playerMaxCount) {
        qDebug() << "Max players limit has been reached!";
        delete sockHandle;
    }

    int clientMapId = addClientToMap(sockHandle);
    //this->clients.push_back(sockHandle);

    qDebug() << "New connection, with id: " << clientMapId;
    emit newClientConnected(clientMapId);
    qDebug() << "Client connected!";
    connect(sockHandle, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(sockHandle, SIGNAL(message(const QString&)), this, SLOT(onMessage(const QString&)));
    connect(sockHandle, SIGNAL(message(const QByteArray&)), this, SLOT(onMessage(const QByteArray&)));
}


int Network::addClientToMap(ClientSocket* clientSocket) {
    for (int i = 0; i < playerMaxCount; ++i) {
       if(!clientsMap.contains(i)) {
           clientsMap[i] = clientSocket;
           return i;
       }
    }
    qDebug() << "Should be impossible! Max players should be checked before this function call";
    exit(EXIT_FAILURE);
}

void Network::onDisconnected()
{
    qDebug() << "ServerNetwork::onDisconnected, clientsLen:" << clientsMap.size() << endl;

    int disconnecteSocketID = getDisconnectedSocketID();
    if(disconnecteSocketID == -1) {
        qDebug() << "disconnecteSocketID == -1!";
        exit(EXIT_FAILURE);
    }

    auto client = static_cast<ClientSocket*>(sender()); // nw czy sender() zadziala bo do QObject posyłamy nullptr ale to Qt wiec kij wie co tam sie dzieje
    //clients.removeOne(client);
    //delete client;
    emit gameDisconnect(disconnecteSocketID);

    //clientsMap.remove(disconnecteSocketID);
}

int Network::getDisconnectedSocketID() {
    for (const auto& id : clientsMap.keys()) {
        if(clientsMap[id]->tcpSocket->state() != QTcpSocket::ConnectedState) {
            clientsMap[id]->tcpSocket->disconnect();
            clientsMap[id]->tcpSocket->disconnectFromHost();
            clientsMap[id]->tcpSocket->deleteLater();
            return id;
        }
    }
    return -1;
}

void Network::sendAll(const QString &message) const
{
    for (const auto& socket : clientsMap.values())
    {
        socket->sendString(message);
    }
}

void Network::sendAll(const QByteArray &data) const
{
    for (const auto& socket : clientsMap.values())
    {
        socket->sendData(data);
    }
}

void Network::sendAll(const GameState& gameState) const
{
    for (const auto& socket : clientsMap.values())
    {
        socket->sendGameState(gameState);
    }
}

void Network::send(const int playerID) const
{
    clientsMap[playerID]->sendData(QByteArray(static_cast<char *>((void*)&playerID), sizeof(int)));
}


void Network::onMessage(const QString& message) const
{
    //sendAll(message);
    qDebug() << "String" << message;
}


void Network::onMessage(const QByteArray& data) const
{
    //qDebug() << "Data" << data;
    qDebug() << "Received!!";
    PlayerAction pA = parsePlayerAction(data);
    //GameState test{1,2,3,4,200,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    emit playerMadeAction(pA);
    //sendAll(test);
}

PlayerAction Network::parsePlayerAction(const QByteArray& data) const
{
    PlayerAction playerAction;
    qDebug() << "Received!!";
    memcpy(&playerAction,data.data(), sizeof(playerAction));
    //qDebug() << playerAction.actions << playerAction.posX << playerAction.posY;
    return playerAction;

}

