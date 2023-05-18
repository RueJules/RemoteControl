#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include"remoteevent.h"

class Socket;
class ImageProvider;
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);//explicit禁止隐式类型

    ImageProvider* getImageProvider() { return m_provider; }

    Q_INVOKABLE void finish();
    Q_INVOKABLE void requestNewConnection();

    Q_INVOKABLE void mousePressed(const QPointF &position);
    Q_INVOKABLE void mouseReleased(const QPointF &position);
    Q_INVOKABLE void mouseMoved(const QPointF &position);
    Q_INVOKABLE void mouseEntered(const QPointF &position);
    inline void sendRemoteEvent(RemoteEvent::EventType type, const QPointF &position);


public slots:
    void readScreenData(const QByteArray &screenData);
signals:
    void connected();
    void disconnected();
    void needUpdate();

private:

    Socket *m_socket;//这是跟服务器连接的套接字
    ImageProvider *m_provider;

};

#endif // CONTROLLER_H