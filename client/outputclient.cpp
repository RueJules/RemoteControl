#include "outputclient.h"
#include <QMediaDevices>

OutputClient::OutputClient(QObject *parent):QObject{parent}
{
    m_socketWrite = new Socket;//读麦克风写入套接字
    m_socketWrite->connectHost(QHostAddress(QString("10.252.211.167")), 8877);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    //qDebug() << info.description();
//    for(auto device:QMediaDevices::audioInputs()){
//        qDebug() << device.description();
//    }

    QList<QAudioDevice> ds = QMediaDevices::audioInputs();

    input = new QAudioSource(ds[1],format,this);//采用格 2W式
    //inputDevice=dynamic_cast<IoDevice *>(input->start());//采集声音
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
    // qDebug() << data;
    //m_socket->write(data);
    QMetaObject::invokeMethod(m_socketWrite, "writeToSocket", Q_ARG(QByteArray, data));

    qDebug() << "已发送";
}
