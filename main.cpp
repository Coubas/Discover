#include <QApplication>
//#include <QGeoServiceProvider>
//#include <QGeoRoutingManager>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QQuickView>

//#include <QAbstractItemModelTester>

//#define TEST_SIMPLETREEVIEW
#ifdef TEST_SIMPLETREEVIEW
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>
#endif // TEST_SIMPLETREEVIEW

#include <DiscoverMainWindow.h>
#include <InputHandler.h>
#include <MapBackend.h>
#include <MapHelper.h>
#include <MapMarkerList.h>
#include <MapMarkerModel.h>
#include <MapMarkerTreeModel.h>
#include <MapMarkerTreeItem.h>
#include <TracksManager.h>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterSingletonType<MapHelper>("MapHelper", 1, 0, "MapHelper", &MapHelper::qmlInstance);
    qmlRegisterUncreatableType<MapBackend>("MapBackend", 1, 0,"MapBackend", QStringLiteral("MapBackend should not be created in QML."));
    qmlRegisterType<MapMarkerModel>("MapMarker", 1, 0, "MapMarkerModel");
    qmlRegisterType<MapMarkerTreeModel>("MapMarker", 1, 0, "MapMarkerTreeModel");
    qmlRegisterUncreatableType<MapMarkerList>("MapMarker", 1, 0, "MapMarkerList", QStringLiteral("MapMarkerList should not be created in QML."));
    qmlRegisterUncreatableType<MapMarkerTreeItem>("MapMarker", 1, 0, "MapMarkerTreeItem", QStringLiteral("MapMarkerTreeItem should not be created in QML."));
    qmlRegisterUncreatableType<TracksManager>("Tracks", 1, 0, "TracksManager", QStringLiteral("TracksManager should not be created in QML."));
    qmlRegisterUncreatableType<Track>("Tracks", 1, 0, "Track", QStringLiteral("Track should not be created in QML."));
    qmlRegisterUncreatableType<TreeTrack>("Tracks", 1, 0, "TreeTrack", QStringLiteral("TreeTrack should not be created in QML."));
    qmlRegisterUncreatableType<InputHandler>("Inputs", 1, 0, "InputHandler", QStringLiteral("InputHandler should not be created in QML."));

//    QGeoServiceProvider geoServiceProvider("osm");
//    QGeoRoutingManager* routingManager = geoServiceProvider.routingManager();


    InputHandler inputHdl;
    MapBackend mapBackEnd;
    mapBackEnd.connectInputs(&inputHdl);
    mapBackEnd.setLocusPos(QGeoCoordinate(43.778958, 3.812109)); // Le Pic Saint-Loup
    TracksManager tracksManager;
    tracksManager.connectInputs(&inputHdl);

//    MapMarkerTreeModel *modelToBeTested = tracksManager.getTreeTrack()->getTreeModel();
//    auto tester = new QAbstractItemModelTester(modelToBeTested, QAbstractItemModelTester::FailureReportingMode::Fatal);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("inputHandler", &inputHdl);
    engine.rootContext()->setContextProperty("tracksManager", &tracksManager);
    engine.rootContext()->setContextProperty("mapBackend", &mapBackEnd);
    engine.load(QUrl(QStringLiteral("qrc:/qml/Qml/MainWindow.qml")));

#ifdef TEST_SIMPLETREEVIEW
    QWidget *wdg = new QWidget;
    wdg->show();

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView *tree = new QTreeView(wdg);
    tree->setModel(tracksManager.getTreeTrack()->getTreeModel());
    //tree->setModel(simpleModel);
    tree->show();

    QPushButton *button = new QPushButton(
        QApplication::translate("childwidget", "Press me"), wdg);
    button->move(100, 300);
    button->show();

    int prevID = 0;
    wdg->connect(button, &QPushButton::released, wdg, [&]()
    {
        qDebug() << Q_FUNC_INFO << "btn click";
        QGeoCoordinate randCoord = QGeoCoordinate((double)rand() / RAND_MAX, (double)rand() / RAND_MAX);
        tracksManager.setPointCoordinate(prevID, randCoord);
        //tracksManager.getTreeTrack()->getTreeModel()->setData(tracksManager.getTreeTrack()->getTreeModel()->index(0, 0), QVariant::fromValue<QGeoCoordinate>(randCoord), MapMarkerTreeItem::MarkerCoordinate);
//        tracksManager.getTreeTrack()->getTreeModel()->setData(tracksManager.getTreeTrack()->getTreeModel()->index(0, 1), (double)rand() / RAND_MAX, MapMarkerTreeItem::MarkerCoordinateLatitude);
//        tracksManager.getTreeTrack()->getTreeModel()->setData(tracksManager.getTreeTrack()->getTreeModel()->index(0, 2), (double)rand() / RAND_MAX, MapMarkerTreeItem::MarkerCoordinateLongitude);
        prevID = rand();
        tracksManager.getTreeTrack()->getTreeModel()->setData(tracksManager.getTreeTrack()->getTreeModel()->index(0, 0), prevID, MapMarkerTreeItem::MarkerId);
        //simpleModel->setData(simpleModel->index(1,1), rand());
    });
#endif // TEST_SIMPLETREEVIEW

    DiscoverMainWindow mainWindow{qobject_cast<QQuickWindow*>(engine.rootObjects().at(0))};
    mainWindow.connectInputs(&inputHdl);
    mainWindow.show();

    return app.exec();
}
