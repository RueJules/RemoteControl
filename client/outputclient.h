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
public slots:
    void readySend();
private:
    QAudioSource *input;
    QIODevice *inputDevice;

    Socket *m_socketWrite;
};

#endif // OUTPUTCLIENT_H
