#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    Socket(QObject *parent = nullptr):QTcpSocket(parent){}
    ~Socket(){}
    Q_INVOKABLE void writeToSocket(QByteArray data){QTcpSocket::write(data);}
    Q_INVOKABLE QByteArray readAllSocket(){return QTcpSocket::readAll();}

};

#endif // SOCKET_H
