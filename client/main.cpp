#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "inputclient.h"
#include "outputclient.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Client *client = new Client;
    InputClient *ic = new InputClient;
    QThread* th1 = new QThread;
    QObject::connect(th1, &QThread::finished, th1, &QThread::deleteLater);
    ic->moveToThread(th1);
    th1->start();

    OutputClient *oc = new OutputClient;
    QThread* th2 = new QThread;
    QObject::connect(th2, &QThread::finished, th2, &QThread::deleteLater);
    oc->moveToThread(th2);
    th2->start();


    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled2/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
