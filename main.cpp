#include <QApplication>
//#include <QGeoServiceProvider>
//#include <QGeoRoutingManager>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QQuickView>

#include <DiscoverMainWindow.h>
#include <InputHandler.h>
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
    qmlRegisterUncreatableType<TracksManager>("Tracks", 1, 0, "TracksManager", QStringLiteral("TracksManager should not be created in QML."));
    qmlRegisterUncreatableType<Track>("Tracks", 1, 0, "Track", QStringLiteral("Track should not be created in QML."));
    qmlRegisterUncreatableType<InputHandler>("Inputs", 1, 0, "InputHandler", QStringLiteral("InputHandler should not be created in QML."));

//    QGeoServiceProvider geoServiceProvider("osm");
//    QGeoRoutingManager* routingManager = geoServiceProvider.routingManager();


    InputHandler inputHdl;
    MapBackend mapBackEnd;
    mapBackEnd.connectInputs(&inputHdl);
    mapBackEnd.setLocusPos(QGeoCoordinate(43.778958, 3.812109)); // Le Pic Saint-Loup
    TracksManager tracksManager;
    tracksManager.connectInputs(&inputHdl);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("inputHandler", &inputHdl);
    engine.rootContext()->setContextProperty("tracksManager", &tracksManager);
    engine.rootContext()->setContextProperty("mapBackend", &mapBackEnd);
    engine.load(QUrl(QStringLiteral("qrc:/qml/Qml/MainWindow.qml")));

    DiscoverMainWindow mainWindow{qobject_cast<QQuickWindow*>(engine.rootObjects().at(0))};
    mainWindow.connectInputs(&inputHdl);
    mainWindow.show();

    return app.exec();
}
