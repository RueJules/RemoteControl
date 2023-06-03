#include "controller.h"
#include "imageprovider.h"
#include "socket.h"
#include "keythread.h"
#include <QGuiApplication>
#include <QHostAddress>
#include <QInputDialog>
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
//    KeyThread *keythread = new KeyThread(this);
//    connect(keythread,&KeyThread::keyPressed,this ,&Controller::keyPressed);
//    connect(keythread,&KeyThread::keyReleased,this ,&Controller::keyReleased);
//    keythread->start();
}
//连接服务器

void Controller::requestNewConnection()
{

    QHostAddress hostAddress(QString{"10.252.47.61"});
        QMetaObject::invokeMethod(m_socket, "connectHost", Q_ARG(QHostAddress, hostAddress), Q_ARG(quint16, 43800));



    //指定服务器的ip和端口
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

void Controller::Communication()
{
     input=new InputClient();
     QThread *thread1 = new QThread;
     connect(thread1, &QThread::finished, thread1, &QThread::deleteLater);
     input->moveToThread(thread1);//刚创建就交给子进程？？那主进程干什么
     thread1->start();

     output=new OutputClient();
     QThread *thread2 = new QThread;
     connect(thread2, &QThread::finished, thread2, &QThread::deleteLater);
     output->moveToThread(thread2);//刚创建就交给子进程？？那主进程干什么
     thread2->start();

}

void Controller::CancelCom()
{
     delete input;
     delete output;
}

//鼠标事件
void Controller::leftMousePressed(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::MouseLeftPressed, position);
}

void Controller::leftMouseReleased(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::MouseLeftReleased, position);
}
void Controller::rightMousePressed(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::MouseRightPressed, position);
     qDebug("鼠标右键");
}

void Controller::rightMouseReleased(const QPointF &position)
{
     sendRemoteEvent(RemoteEvent::EventType::MouseRightReleased, position);
}


void Controller::mouseMoved(const QPointF &position)
{

     sendRemoteEvent(RemoteEvent::EventType::MouseMoved, position);

}

void Controller::mouseEntered(const QPointF &position)
{

     sendRemoteEvent(RemoteEvent::EventType::MouseEntered, position);

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




