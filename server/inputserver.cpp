#include "inputserver.h"
#include<QThread>
#include <QTcpSocket>
InputServer::InputServer(QObject *parent):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,8888);
    QAudioFormat format;

    format.setSampleRate(44100);//采样率
    format.setChannelCount(2);//声道
    format.setSampleFormat(QAudioFormat::Int16);//采样精度

    input =new QAudioSource(format,this);
    inputDevice=input->start();
    QObject::connect(inputDevice,&QIODevice::readyRead,this,&InputServer::readySend);//检测到声音，接收语音并发出
}

void InputServer::incomingConnection(qintptr socketDescriptor)
{
        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        m_socket_input = new Socket;
        m_socket_input->setSocketDescriptor(socketDescriptor);
        m_socket_input->moveToThread(thread);
        thread->start();
        qDebug() << "called";

}
void InputServer::readySend()
{
    QByteArray data=inputDevice->readAll();
    QMetaObject::invokeMethod(m_socket_input,"writeToSocket",Q_ARG(QByteArray,data));
    //qDebug()<<data;
}
