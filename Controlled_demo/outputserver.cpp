#include "outputserver.h"
#include <QTcpSocket>
#include <QThread>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>

OutputServer::OutputServer(QObject *parent):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,8877);
    QAudioFormat format;

    format.setSampleRate(44100);//采样率
    format.setChannelCount(2);//声道
    format.setSampleFormat(QAudioFormat::Int16);//采样精度

    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    qDebug() << info.description();

    for(auto device:QMediaDevices::audioOutputs()){
        qDebug() << device.description();
    }

    QList<QAudioDevice> ds = QMediaDevices::audioOutputs();

    output = new QAudioSink(ds[0],format,this);//采用格 2W式
    //inputDevice=dynamic_cast<IoDevice *>(input->start());//采集声音
    //outputDevice=input->start();

    //output = new QAudioSink(format,this);
    outputDevice=output->start();
}

void OutputServer::incomingConnection(qintptr socketDescriptor)
{

        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        m_socket_output = new SocketAudio;
        m_socket_output->setSocketDescriptor(socketDescriptor);
        m_socket_output->moveToThread(thread);
        QObject::connect(m_socket_output,&QTcpSocket::readyRead,this,&OutputServer::readyRead,Qt::DirectConnection);
        thread->start();
        qDebug() << "called";


}
void OutputServer::readyRead()
{
    QByteArray data;
    QMetaObject::invokeMethod(m_socket_output,"readAllSocket",Q_RETURN_ARG(QByteArray,data));
    outputDevice->write(data);
    qDebug()<<"akscnsakc";
}
