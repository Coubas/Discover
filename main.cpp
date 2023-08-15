#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <InputHandler.h>
#include <MainWindow.h>
#include <MapBackend.h>
#include <MapHelper.h>
#include <MapMarkerList.h>
#include <MapMarkerModel.h>
#include <TracksManager.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterSingletonType<MapHelper>("MapHelper", 1, 0, "MapHelper", &MapHelper::qmlInstance);
    qmlRegisterUncreatableType<MapBackend>("MapBackend", 1, 0,"MapBackend", QStringLiteral("MapBackend should not be created in QML."));
    qmlRegisterType<MapMarkerModel>("MapMarker", 1, 0, "MapMarkerModel");
    qmlRegisterUncreatableType<MapMarkerList>("MapMarker", 1, 0, "MapMarkerList", QStringLiteral("MapMarkerList should not be created in QML."));
    qmlRegisterUncreatableType<MapMarkerList>("Tracks", 1, 0, "TracksManager", QStringLiteral("TracksManager should not be created in QML."));
    qmlRegisterUncreatableType<MapMarkerList>("Tracks", 1, 0, "Track", QStringLiteral("Track should not be created in QML."));
    qmlRegisterUncreatableType<MapMarkerList>("Inputs", 1, 0, "InputManager", QStringLiteral("TracksManager should not be created in QML."));

    InputHandler inputHdl;
    MapBackend mapBackEnd;
    mapBackEnd.connectInputs(&inputHdl);
    mapBackEnd.setLocusPos(QGeoCoordinate(43.778958, 3.812109)); // Le Pic Saint-Loup
    TracksManager tracksManager;
    tracksManager.connectInputs(&inputHdl);

//    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty(QStringLiteral("inputHandler"), &inputHdl);
//    engine.rootContext()->setContextProperty(QStringLiteral("tracksManager"), &tracksManager);

    MainWindow window;
    window.setMapViewContextProperty(QStringLiteral("tracksManager"), &tracksManager);
    window.setMapViewContextProperty(QStringLiteral("mapBackend"), &mapBackEnd);
    window.connectWindowElements(&inputHdl);
    window.connectInputs(&inputHdl);
    window.show();

    return app.exec();
}
