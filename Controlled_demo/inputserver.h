#ifndef OUTPUTSERVER_H
#define OUTPUTSERVER_H
#include <QTcpServer>
#include <QAudioSource>
#include "socket.h"

class InputServer:public QTcpServer//检测是否有数据需要输出给客户端（麦克风）
{
    Q_OBJECT
public:
    InputServer(QObject *parent = nullptr);
     ~InputServer(){
         delete input;
         delete inputDevice;
     }
     void incomingConnection(qintptr socketDescriptor);
 private:
     SocketAudio *m_socket_input=nullptr;
     QAudioSource *input;
     QIODevice *inputDevice;
 public slots:
     void readySend();
};

#endif // OUTPUTSERVER_H
