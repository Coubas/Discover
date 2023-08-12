#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MapHelper.h>
#include <MapBackend.h>


int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<MapHelper>("MapHelper", 1, 0, "MapHelper", &MapHelper::qmlInstance);
    qmlRegisterType<MapBackend>("MapBackend", 1, 0,"MapBackend");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Discover", "Main");

    return app.exec();
}
