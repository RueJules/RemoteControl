#ifndef INPUTCLIENT_H
#define INPUTCLIENT_H

#include <socket.h>
#include <QAudioSink>
#include <QIODevice>
#include <QObject>

class InputClient : public QObject
{
public:
    InputClient(QObject *parent = nullptr);
    ~InputClient();

public slots:
    void readyReadSlot();
private:
    QAudioSink *output;
    QIODevice *outputDevice;
    SocketAudio *m_socketRead;
};

#endif // INPUTCLIENT_H
