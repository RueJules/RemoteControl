#include "outputclient.h"
#include <QMediaDevices>

OutputClient::OutputClient(QObject *parent):QObject{parent}
{
    m_socketWrite = new SocketAudio;//读麦克风写入套接字
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    input=new QAudioSource(format,this);
}

OutputClient::~OutputClient()
{
    delete input;
    delete inputDevice;
    delete m_socketWrite;
}

void OutputClient::connectOutput(QString ip)
{
    m_socketWrite->connectToHost(QHostAddress(QString(ip)), 8877);
    inputDevice=input->start();
    connect(inputDevice,&QIODevice::readyRead,this,&OutputClient::readySend);
}
void OutputClient::readySend()
{
    QByteArray data;
    data = inputDevice->readAll();
    //m_socketWrite->write(data);
    QMetaObject::invokeMethod(m_socketWrite, "writeToSocket", Q_ARG(QByteArray, data));
}
