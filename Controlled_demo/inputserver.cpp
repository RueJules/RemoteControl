#include "inputserver.h"
#include<QThread>
#include <QTcpSocket>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>

InputServer::InputServer(QObject *parent):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,8888);


    QAudioFormat format;//音频格式

    format.setSampleRate(44100);//采样率
    format.setChannelCount(2);//双声道
    format.setSampleFormat(QAudioFormat::Int16);//采样精度

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {  //判断默认的设备是否支持设置的格式
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    //qDebug() << info.description();
    //    for(auto device:QMediaDevices::audioInputs()){
    //        qDebug() << device.description();
    //    }

    QList<QAudioDevice> ds = QMediaDevices::audioInputs(); //返回所有可用的设备

    input = new QAudioSource(ds[1],format,this);//采用格 2W式
    inputDevice=input->start(); //返回输入设备
    QObject::connect(inputDevice,&QIODevice::readyRead,this,&InputServer::readySend);//检测到声音，接收语音并发出给对方
}

void InputServer::incomingConnection(qintptr socketDescriptor)
{
        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        m_socket_input = new SocketAudio;
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
    qDebug() << "fasong!";
}
