#include "controller.h"
#include "imageprovider.h"
#include "socket.h"
#include<QThread>
#include <QGuiApplication>
#include <QHostAddress>
#include <QInputDialog>
Controller::Controller(QObject *parent)
    : QObject(parent)
{
    m_provider = new ImageProvider();
    m_socket = new Socket;

    connect(m_socket, &Socket::hasScreenData, this, &Controller::readScreenData);
    connect(m_socket,&Socket::connected,this,&Controller::changeflag);
    connect(m_socket,&Socket::disconnected,this,&Controller::changeflag);
    QThread *thread = new QThread;
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    m_socket->moveToThread(thread);//刚创建就交给子进程？？那主进程干什么
    thread->start();
}
//连接服务器
void Controller::requestNewConnection(QString ip)
{
    QHostAddress hostAddress(QString{ip});
    QMetaObject::invokeMethod(m_socket, "connectHost", Q_ARG(QHostAddress, hostAddress), Q_ARG(quint16, 43800));
    //指定服务器的ip和端口
}
//断开连接
void Controller::finish()
{
    QMetaObject::invokeMethod(m_socket, "abort");
}
void Controller::communication(QString ip)
{
     setCflag(true);
     setSflag(true);

     input=new InputClient();//cflag
     input->connectInput(ip);
     connect(input->m_socketRead,&SocketAudio::connected,this,&Controller::changecflag);
     connect(input->m_socketRead,&SocketAudio::disconnected,this,&Controller::changecflag);
     QThread *thread1 = new QThread;
     connect(thread1, &QThread::finished, thread1, &QThread::deleteLater);
     input->moveToThread(thread1);
     thread1->start();

     output=new OutputClient();
     output->connectOutput(ip);
     connect(output->m_socketWrite,&SocketAudio::connected,this,&Controller::changesflag);
     connect(output->m_socketWrite,&SocketAudio::disconnected,this,&Controller::changesflag);
     QThread *thread2 = new QThread;
     connect(thread2, &QThread::finished, thread2, &QThread::deleteLater);
     output->moveToThread(thread2);
     thread2->start();
}

void Controller::discommunication()
{
     input->m_socketRead->abort();
     output->m_socketWrite->abort();
     setCflag(true);
     setSflag(true);
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
//读图片数据
void Controller::readScreenData(const QByteArray &screenData)
{
     QPixmap pixmap;
     pixmap.loadFromData(screenData);
     m_provider->setPixmap(pixmap);
     emit needUpdate();
}
bool Controller::flag()
{
     return m_flag;
}

void Controller::setFlag(const bool &flag)
{
     if(m_flag==flag)
        return;
     m_flag=flag;
     emit flagChanged();
}

bool Controller::cflag()
{
     return c_flag;
}

void Controller::setCflag(const bool &flag)
{
     if(c_flag==flag)
        return;
     c_flag=flag;
     emit cflagChanged();
}

bool Controller::sflag()
{
     return s_flag;
}

void Controller::setSflag(const bool &flag)
{
     if(s_flag==flag)
        return;
     s_flag=flag;
     emit cflagChanged();
}
void Controller::changeflag()
{
     setFlag(!flag());
     if(flag()&&!cflag()){//为true主连接断开语音通信也应该断开
        discommunication();
     }
}

void Controller::changecflag()
{
     setCflag(!cflag());
}

void Controller::changesflag()
{
     setSflag(!sflag());
}

