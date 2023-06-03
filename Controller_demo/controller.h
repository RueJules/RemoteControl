#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include"remoteevent.h"
#include"inputclient.h"
#include"outputclient.h"

class Socket;
class ImageProvider;
class Controller : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool flag=true;
    Q_INVOKABLE void communication(QString ip);
    Q_INVOKABLE void discommunication();
    explicit Controller(QObject *parent = nullptr);//explicit禁止隐式类型

    ImageProvider* getImageProvider() { return m_provider; }

    Q_INVOKABLE void finish();
//    Q_INVOKABLE void requestNewConnection();
    Q_INVOKABLE void requestNewConnection(QString ip);
    Q_INVOKABLE void leftMousePressed(const QPointF &position);
    Q_INVOKABLE void leftMouseReleased(const QPointF &position);
    Q_INVOKABLE void rightMousePressed(const QPointF &position);
    Q_INVOKABLE void rightMouseReleased(const QPointF &position);
    Q_INVOKABLE void mouseMoved(const QPointF &position);
    Q_INVOKABLE void mouseEntered(const QPointF &position);
    Q_INVOKABLE void keyPressed(const int &key);
    Q_INVOKABLE void keyReleased(const int &key);

    inline void sendRemoteEvent(RemoteEvent::EventType type, const QPointF &position);
    inline void sendRemoteEvent(RemoteEvent::EventType type, const int &key);

public slots:
    void readScreenData(const QByteArray &screenData);
//    void Communication();

    void CancelCom();
    void changeflag();
signals:
    void connected();
    void sin_discommunication();
    void disconnected();
    void needUpdate();

private:

    Socket *m_socket;//这是跟服务器连接的套接字
    ImageProvider *m_provider;
    InputClient *input;
    OutputClient *output;

};

#endif // CONTROLLER_H
