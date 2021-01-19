#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>


class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr, QTcpSocket* socket = nullptr);
    virtual ~Socket() { }
    virtual void sendString(const QString& string);


signals:
    void message(const QString& message) const;
    void error(const QString& error) const;
    void disconnected() const;

protected slots:
    void onReadyRead();
    void onDisconnected() const;


protected:
    QTcpSocket *tcpSocket;
};

#endif // SOCKET_H
