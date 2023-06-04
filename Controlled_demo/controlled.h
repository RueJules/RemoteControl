#ifndef CONTROLLED_H
#define CONTROLLED_H

#include "protocol.h"
#include <QObject>
#include <QTcpServer>

class Socket;
class RemoteEvent;

class Controlled : public QTcpServer
{
    Q_OBJECT

public:
    Q_PROPERTY(bool flag READ flag WRITE setFlag NOTIFY flagChanged)
    bool flag();
    void setFlag(const bool& flag);


    explicit Controlled(QObject *parent = nullptr);
    ~Controlled();

    Q_INVOKABLE void finish();

signals:
    void connected();
    void disconnected();
    void flagChanged();

public slots:
    void processEvent(const RemoteEvent &ev);


protected:
    void timerEvent(QTimerEvent *event);
    void incomingConnection(qintptr socketDescriptor);

private:
    Socket *m_controlled = nullptr;

//    OutputServer *outputServer = nullptr;
//    InputServer *inputServer = nullptr;
    int m_timerId = 0;
    bool connectstate=false;
};

#endif // CONTROLLED_H
