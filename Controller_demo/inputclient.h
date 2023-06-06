#ifndef INPUTCLIENT_H
#define INPUTCLIENT_H

#include <socket.h>
#include <QAudioSink>
#include <QIODevice>
#include <QObject>

class InputClient : public QObject
{
    Q_OBJECT
public:
    InputClient(QObject *parent = nullptr);
    ~InputClient();
    void connectInput(QString ip);
    SocketAudio *m_socketRead;
public slots:
    void readyReadSlot();
private:
    QAudioSink *output;
    QIODevice *outputDevice;
};

#endif // INPUTCLIENT_H
