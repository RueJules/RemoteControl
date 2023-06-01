#ifndef SOCKET_H
#define SOCKET_H

#include "protocol.h"
#include <QTcpSocket>

class RemoteEvent;
class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);
    ~Socket();

    Q_INVOKABLE void abort( bool &flag);
    Q_INVOKABLE void connectHost(const QHostAddress &host, quint16 port,bool &flag);
    Q_INVOKABLE void writeToSocket(const RemoteEvent &event);

signals:
    void hasScreenData(const QByteArray &screenData);
    void hasEventData(const RemoteEvent &event);
private:
    void processRecvBlock();

    QByteArray m_recvData;
    BlockHeader m_recvHeader;
};

#endif // SOCKET_H
