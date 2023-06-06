#include "controlled.h"
#include "remoteevent.h"
#include "systemapi.h"
#include "socket.h"

#include <QBuffer>
#include <QGuiApplication>
#include <QScreen>
#include <QTime>
#include <QThread>
#include <QCursor>
#include <QMessageBox>
bool Controlled::flag() //连接状态返回函数
{
    return connectstate;
}

void Controlled::setFlag(const bool &flag)  //当套接字状态发生改变时，设置当前的套接字状态
{
    if(connectstate==flag)
        return;
    connectstate=flag;
    emit flagChanged();
}

Controlled::Controlled(QObject *parent)
    : QTcpServer (parent)
{
    listen(QHostAddress::Any, 43800); //监听

}

Controlled::~Controlled()
{

}

void Controlled::finish()
{
    if (m_controlled)
        QMetaObject::invokeMethod(m_controlled, "abort"); //Aborts the current connection and resets the socket.this function immediately closes the socket, discarding any pending data in the write buffer.
}

void Controlled::processEvent(const RemoteEvent &ev)
{
    QRectF screenRect = qApp->primaryScreen()->geometry();
    QPointF localPos(ev.position().x() * screenRect.width(),
                     ev.position().y() * screenRect.height());//通过事件点在控制端上应用窗口内的占比重新计算应该显示在被控制端的坐标
    switch (ev.type())  //根据不听的事件类型使用不同的处理函数
    {
    case RemoteEvent::EventType::MouseLeftPressed:
        SystemApi::mousePress(localPos);
       // qDebug()<<"收到鼠标按下事件";
        break;
    case RemoteEvent::EventType::MouseLeftReleased:
        SystemApi::mouseRelease(localPos);
       // qDebug()<<"收到鼠标释放事件";
        break;
    case RemoteEvent::EventType::MouseMoved:
        SystemApi::mouseMove(localPos);
        //qDebug()<<"收到鼠标移动事件";
        //qDebug() << p3.x() << p3.y();
        break;
    case RemoteEvent::EventType::MouseEntered:
        SystemApi::mouseEntered(localPos);
        //qDebug()<<"收到鼠标进入事件";
        break;
    case RemoteEvent::EventType::KeyInput:
        SystemApi::keyPressed(ev.key());
        break;
    case RemoteEvent::EventType::KeyReleased:
        SystemApi::keyReleased(ev.key());
        break;
    case RemoteEvent::EventType::MouseRightPressed:
        SystemApi::MouseRightPress(localPos);
        break;
    case RemoteEvent::EventType::MouseRightReleased:
        SystemApi::MouseRightReleased(localPos);
        break;
    default:
        break;
    }
}

void Controlled::incomingConnection(qintptr socketDescriptor)
{
    QMessageBox msgBox;  //消息盒子，由被控制端决定时会接受这次控制
    msgBox.setText("This shares control of your computer's screen, mouse, and keyboard with the connector");
    msgBox.setInformativeText("Do you want to connect?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Ok:

        break;
    case QMessageBox::Cancel:
    default:
        setFlag(false);
        finish();
        return;
        break;
    }

    qDebug() << "called";
    if (!m_controlled) {  //没有生成连接套接字

        QThread *thread = new QThread; //套接字线程
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        m_controlled = new Socket;  //生成连接套接字

        //完成套接字一些可能的信号与槽的连接
        connect(m_controlled, &Socket::stateChanged, this, [this](QAbstractSocket::SocketState socketState) {
            switch (socketState)
            {
            case QAbstractSocket::ConnectedState:
                 setFlag(true);
                emit connected();
                break;
            default:
                break;
            }
        });
        connect(m_controlled, &Socket::disconnected, this, [this]() {
            Socket *socket = m_controlled;
            m_controlled = nullptr;
            socket->deleteLater();
            killTimer(m_timerId);
            m_timerId = 0;
            setFlag(false);
            emit disconnected();
        });
        connect(m_controlled, &Socket::hasEventData, this, [this](const RemoteEvent &event) { //对于被控制端在这个套接字中只会接收到事件数据
            processEvent(event);
        });

        //为连接套接字设置套接字描述符
        m_controlled->setSocketDescriptor(socketDescriptor);
        m_controlled->moveToThread(thread);
        thread->start();

        //启动计时器，1秒做一次
        if (!m_timerId)
            m_timerId = startTimer(std::chrono::milliseconds(1000));
    }
}

void Controlled::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (m_controlled) {
        QBuffer buffer;  //屏幕事件缓冲区
        buffer.open(QIODevice::WriteOnly);
        QTime time = QTime::currentTime();
        QPixmap pixmap = SystemApi::grabScreen();
        //qDebug() << time.msecsTo(QTime::currentTime());
        pixmap.save(&buffer, "jpg", 35); //This function writes a QPixmap to the given device using the specified image file format and quality factor.

        BlockHeader header = { SCREEN_TYPE, qint32(buffer.size()) };
        DataBlock data = { header, buffer.data() };

        //进入套接字的线程中
        QMetaObject::invokeMethod(m_controlled, "writeToSocket", Q_ARG(DataBlock, data));
    }
}
