
#include "controller.h"
#include "imageprovider.h"
#include "protocol.h"
#include <QHostAddress>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//
    QGuiApplication app(argc, argv);
    qRegisterMetaType<DataBlock>("DataBlock");
    qRegisterMetaType<RemoteEvent>("RemoteEvent");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    Controller *controller = new Controller;
    controller->requestNewConnection();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controller", controller);
    engine.addImageProvider(QLatin1String("screen"), controller->getImageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/Control_demo/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
