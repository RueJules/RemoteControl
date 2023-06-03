#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include"inputserver.h"
#include"outputserver.h"
#include <QThread>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    InputServer *inputServer=new InputServer();
    OutputServer*outputServer=new OutputServer();
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
