#include "inputclient.h"
#include <QMediaDevices>

InputClient::InputClient(QObject *parent) : QObject{parent}
{
    m_socketRead = new SocketAudio; //读网络写入扬声器
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    output = new QAudioSink(format,this);
}

InputClient::~InputClient()
{
    delete output;
    delete outputDevice;
    delete m_socketRead;
}
//套接字连接，从套接字中读到扬声器
void InputClient::connectInput(QString ip)
{
    m_socketRead->connectToHost(QHostAddress(QString(ip)), 8888);
    outputDevice = output->start();
    connect(m_socketRead,&SocketAudio::readyRead,this,&InputClient::readyReadSlot,Qt::DirectConnection);
}

void InputClient::readyReadSlot()
{
    QByteArray data;
    data = m_socketRead->readAll();
    outputDevice->write(data);
}
