//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include<QApplication>
#include "controlled.h"
#include "virtualmouse.h"
#include"remoteevent.h"
#include "systemapi.h"
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qRegisterMetaType<DataBlock>("DataBlock");
    qRegisterMetaType<RemoteEvent>("RemoteEvent");

    Controlled *controlled = new Controlled;
    VirtualMouse *vmouse = new VirtualMouse;
    SystemApi *sysapi = new SystemApi;

    vmouse->install_uinput_mouse_device();
    //sleep(3);
    //qDebug() << vmouse->oldPoint.x() << vmouse->oldPoint.y();
    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("virtualmouse", vmouse);
    const QUrl url(u"qrc:/Controlled/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
