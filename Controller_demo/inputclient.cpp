#include "inputclient.h"
#include <QMediaDevices>

InputClient::InputClient(QObject *parent) : QObject{parent}
{

    m_socketRead = new SocketAudio; //读网络写入扬声器
    m_socketRead->connectToHost(QHostAddress(QString("10.252.47.61")), 8888);
    connect(m_socketRead,&SocketAudio::readyRead,this,&InputClient::readyReadSlot,Qt::DirectConnection);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    output = new QAudioSink(format,this);
    outputDevice = output->start();
}

InputClient::~InputClient()
{
    delete output;
    delete outputDevice;

}

void InputClient::readyReadSlot()
{

    QByteArray data;
    data = m_socketRead->readAll();
    //QMetaObject::invokeMethod(m_socketRead, "readAllData", Q_RETURN_ARG(QByteArray, data));
    //data=m_socket->readAll();
    qDebug() << data;
    outputDevice->write(data);
    //QMetaObject::invokeMethod(outputDevice, "writeTo", Q_ARG(QByteArray, data));
}
