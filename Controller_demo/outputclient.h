#ifndef OUTPUTCLIENT_H
#define OUTPUTCLIENT_H

#include "socket.h"
//#include <QAudioSink>
#include <QAudioSource>
#include <QIODevice>
#include <QObject>

class OutputClient : public QObject
{
    Q_OBJECT
public:
    OutputClient(QObject *parent = nullptr);
    ~OutputClient();
    void connectOutput(QString ip);
    SocketAudio *m_socketWrite;
public slots:
    void readySend();
private:
    QAudioSource *input;
    QIODevice *inputDevice;
//SocketAudio *m_socketWrite;

};

#endif // OUTPUTCLIENT_H
