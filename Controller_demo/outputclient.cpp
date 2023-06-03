#include "outputclient.h"
#include <QMediaDevices>

OutputClient::OutputClient(QObject *parent):QObject{parent}
{
    m_socketWrite = new SocketAudio;//读麦克风写入套接字
    m_socketWrite->connectToHost(QHostAddress(QString("10.252.47.61")), 8877);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    input=new QAudioSource(format,this);
    inputDevice=input->start();

    connect(inputDevice,&QIODevice::readyRead,this,&OutputClient::readySend);
}

OutputClient::~OutputClient()
{
    delete input;
    delete inputDevice;
    delete m_socketWrite;
}

void OutputClient::readySend()
{
    QByteArray data;
    //qDebug() << QMetaObject::invokeMethod(inputDevice, "readToAll", Q_RETURN_ARG(QByteArray, data));
    data = inputDevice->readAll();
    //qDebug() << data;
    //m_socket->write(data);
    QMetaObject::invokeMethod(m_socketWrite, "writeToSocket", Q_ARG(QByteArray, data));

    qDebug() << "已发送";
}
