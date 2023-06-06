#ifndef CONTROLLED_H
#define CONTROLLED_H

#include "protocol.h"
#include <QObject>
#include <QTcpServer>

class Socket;  //自定义的套接字类，继承自QTcpSocket
class RemoteEvent; //定义的远程事件

class Controlled : public QTcpServer  //被控制端
{
    Q_OBJECT

public:
    Q_PROPERTY(bool flag READ flag WRITE setFlag NOTIFY flagChanged)  //该套接字是否连接的标志
    bool flag();
    void setFlag(const bool& flag);


    explicit Controlled(QObject *parent = nullptr);
    ~Controlled();

    Q_INVOKABLE void finish();  //显示终止

signals:
    //描述套接字状态
    void connected();
    void disconnected();
    void flagChanged();

public slots:
    void processEvent(const RemoteEvent &ev);   //对传来的事件进行处理的过程


protected:
    void timerEvent(QTimerEvent *event);  //计时器事件，定时发送被控制端的屏幕截图
    void incomingConnection(qintptr socketDescriptor); //当有控制端请求连接时，自动调用该函数处理连接

private:

    Socket *m_controlled = nullptr; //已连接套接字

//    OutputServer *outputServer = nullptr;
//    InputServer *inputServer = nullptr;
    int m_timerId = 0;
    bool connectstate=false;  //对应的是flag
};

#endif // CONTROLLED_H
