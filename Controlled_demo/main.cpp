#include <QGuiApplication>
#include<QApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QQmlContext>
#include "controlled.h"
#include "virtualmouse.h"
#include"remoteevent.h"
#include "systemapi.h"
#include "inputserver.h"
#include "outputserver.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<DataBlock>("DataBlock");
    qRegisterMetaType<RemoteEvent>("RemoteEvent");

    Controlled *controlled = new Controlled;
    VirtualMouse *vmouse = new VirtualMouse;
    SystemApi *sysapi = new SystemApi;

    OutputServer *outputServer = new OutputServer;
    InputServer *inputServer = new InputServer;

    vmouse->install_uinput_mouse_device();
    //vmouse->install_uinput_keyboard_device();
    //sleep(3);
    //qDebug() << vmouse->oldPoint.x() << vmouse->oldPoint.y();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controlled", controlled);
    //engine.rootContext()->setContextProperty("virtualmouse", vmouse);
    const QUrl url(u"qrc:/Controlled/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
