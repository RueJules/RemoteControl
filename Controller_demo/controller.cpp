#include "controller.h"
#include "imageprovider.h"
#include "socket.h"


#include <QGuiApplication>
#include <QHostAddress>
#include <QThread>

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    m_provider = new ImageProvider();
    m_socket = new Socket;
    connect(m_socket, &Socket::hasScreenData, this, &Controller::readScreenData);
    QThread *thread = new QThread;
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    m_socket->moveToThread(thread);//刚创建就交给子进程？？那主进程干什么
    thread->start();
}
//连接服务器
void Controller::requestNewConnection()
{
    QHostAddress hostAddress(QString{"10.252.11.56"});
    QMetaObject::invokeMethod(m_socket, "connectHost", Q_ARG(QHostAddress, hostAddress), Q_ARG(quint16, 43800));//指定服务器的ip和端口
}
//断开连接
void Controller::finish()
{
     QMetaObject::invokeMethod(m_socket, "abort");
}

//读图片数据
void Controller::readScreenData(const QByteArray &screenData)
{
     QPixmap pixmap;
     pixmap.loadFromData(screenData);
     m_provider->setPixmap(pixmap);
     emit needUpdate();
}

//鼠标事件
void Controller::mousePressed(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::Pressed, position);
     qDebug()<<"按下";
}

void Controller::mouseReleased(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::Released, position);
}

void Controller::mouseMoved(const QPointF &position)
{

     sendRemoteEvent(RemoteEvent::EventType::Moved, position);

}

void Controller::mouseEntered(const QPointF &position)
{

     sendRemoteEvent(RemoteEvent::EventType::Entered, position);

}

void Controller::keyPressed(const int &key)
{
    sendRemoteEvent(RemoteEvent::EventType::KeyInput, key);

}

void Controller::keyReleased(const int &key)
{
    sendRemoteEvent(RemoteEvent::EventType::KeyReleased, key);
}
//发送鼠标事件
void Controller::sendRemoteEvent(RemoteEvent::EventType type, const QPointF &position)
{
     RemoteEvent event(type, position);
     QMetaObject::invokeMethod(m_socket, "writeToSocket", Q_ARG(RemoteEvent, event));
}
//发送键盘事件
void Controller::sendRemoteEvent(RemoteEvent::EventType type, const int &key)
{
     RemoteEvent event(type, key);
     QMetaObject::invokeMethod(m_socket, "writeToSocket", Q_ARG(RemoteEvent, event));
     qDebug()<<"套接字键盘事件";
}




