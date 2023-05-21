#ifndef KEYTHREAD_H
#define KEYTHREAD_H

#include <QObject>
#include<QThread>

class KeyThread : public QThread
{
    Q_OBJECT
public:
    KeyThread(QObject *parent=nullptr);
protected:
    void run();
signals:
    void keyPressed(int key);
    void keyReleased(int key);
};

#endif // KEYTHREAD_H
