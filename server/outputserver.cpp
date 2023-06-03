#include "outputserver.h"
#include <QTcpSocket>
#include <QThread>
OutputServer::OutputServer(QObject *parent):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,8877);
    QAudioFormat format;

    format.setSampleRate(44100);//采样率
    format.setChannelCount(2);//声道
    format.setSampleFormat(QAudioFormat::Int16);//采样精度

    output =new QAudioSink(format,this);
    outputDevice=output->start();
}

void OutputServer::incomingConnection(qintptr socketDescriptor)
{

        QThread *thread = new QThread;
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        m_socket_output = new Socket;
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
