#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpSocket>
#include <QDataStream>


class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr, QTcpSocket* socket = nullptr);
    virtual ~Socket() { }
    virtual void sendString(const QString& string);
    virtual void sendData(const QByteArray& data) const;



signals:
    void message(const QString& message) const;
    void message(const QByteArray& data) const;
    void error(const QString& error) const;
    void disconnected() const;

protected slots:
    void onReadyRead();
    void onDisconnected() const;


public:
    QTcpSocket *tcpSocket;
};

#endif // SOCKET_H
