#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include "clientsocket.h"
#include "playeraction.h"


class Network : public QTcpServer
{
    Q_OBJECT
public:
    explicit Network(quint16 port = 0, QObject* parent = nullptr);
    quint16 port() const { return serverPort(); }
    PlayerAction parsePlayerAction(const QByteArray& data) const;
    void sendAll(const QString &message) const;
    void sendAll(const QByteArray& data) const;
    void sendAll(const GameState& gameState) const;
    void send(const int playerID) const;
    int addClientToMap(ClientSocket* clientSocket);
    int getDisconnectedSocketID();
signals:
    void newClientConnected(int id);
    void playerMadeAction(const PlayerAction& playerAction) const;
    void gameDisconnect(int playerID);

public slots:
    void onNewConnection();
    void onDisconnected();
    void onMessage(const QString& message) const;
    void onMessage(const QByteArray& data) const;

public:
    QMap<int, ClientSocket*> clientsMap;
};

#endif // NETWORK_H
