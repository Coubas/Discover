#include <QApplication>
#include <QQmlApplicationEngine>

#include <MainWindow.h>
#include <MapHelper.h>
#include <MapBackend.h>


int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<MapHelper>("MapHelper", 1, 0, "MapHelper", &MapHelper::qmlInstance);
    qmlRegisterType<MapBackend>("MapBackend", 1, 0,"MapBackend");

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
