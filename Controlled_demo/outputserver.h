#ifndef INPUTSERVER_H
#define INPUTSERVER_H

#include <QTcpServer>
#include <QAudioSink>
#include <QObject>
#include "socket.h"

class OutputServer:public QTcpServer//监听是否有数据输入（客户端有没有传过来）有就用扬声器播放
{
    Q_OBJECT
public:
    OutputServer(QObject *parent=nullptr);
    ~OutputServer(){
        delete output;
        delete outputDevice;
    }
    void incomingConnection(qintptr socketDescriptor);
private:
    SocketAudio *m_socket_output=nullptr;
    QAudioSink *output;
    QIODevice *outputDevice;
public slots:
    void readyRead();
};

#endif // INPUTSERVER_H
