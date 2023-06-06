#ifndef OUTPUTSERVER_H
#define OUTPUTSERVER_H
#include <QTcpServer>
#include <QAudioSource>
#include "socket.h"

class InputServer:public QTcpServer//检测是否有数据需要输出给客户端（麦克风），也就是将本地麦克风中的数据传输给对方
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

     SocketAudio *m_socket_input=nullptr;  //用于将本地的语音传输给对方的套接字
     QAudioSource *input; //The QAudioSource class provides an interface for receiving audio data from an audio input device
     QIODevice *inputDevice; //输入设备，也就是麦克风
 public slots:
     void readySend();
};

#endif // OUTPUTSERVER_H
