#include "inputclient.h"
#include <QMediaDevices>

InputClient::InputClient(QObject *parent) : QObject{parent}
{

    m_socketRead = new Socket; //读网络写入扬声器
    m_socketRead->connectHost(QHostAddress(QString("10.252.211.167")), 8888);
    connect(m_socketRead,&Socket::readyRead,this,&InputClient::readyReadSlot,Qt::DirectConnection);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

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
    //qDebug() << data;
    qDebug() << data;
    outputDevice->write(data);
    //QMetaObject::invokeMethod(outputDevice, "writeTo", Q_ARG(QByteArray, data));
}
