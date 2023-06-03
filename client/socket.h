#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);
    void abort();
    void connectHost(const QHostAddress &host, quint16 port){
        QTcpSocket::connectToHost(host,port);
    }
    Q_INVOKABLE void writeToSocket(QByteArray data){
        QTcpSocket::write(data);
        qDebug() << "write!";
    }
    Q_INVOKABLE QByteArray readAllData(){
        return QTcpSocket::readAll();
        qDebug() << "read!";
    }
signals:
    //void hasAudioData();

};

#endif // SOCKET_H
