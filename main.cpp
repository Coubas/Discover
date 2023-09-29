//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

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
#include <MapMarkerTreeModel.h>
#include <MapMarkerTreeItem.h>
#include <TracksManager.h>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterSingletonType<MapHelper>("MapHelper", 1, 0, "MapHelper", &MapHelper::qmlInstance);
    qmlRegisterUncreatableType<MapBackend>("MapBackend", 1, 0,"MapBackend", QStringLiteral("MapBackend should not be created in QML."));
    qmlRegisterType<MapMarkerTreeModel>("MapMarker", 1, 0, "MapMarkerTreeModel");
    qmlRegisterUncreatableType<MapMarkerTreeItem>("MapMarker", 1, 0, "MapMarkerTreeItem", QStringLiteral("MapMarkerTreeItem should not be created in QML."));
    qmlRegisterUncreatableType<TracksManager>("Tracks", 1, 0, "TracksManager", QStringLiteral("TracksManager should not be created in QML."));
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

//    MapMarkerTreeModel *modelToBeTested = tracksManager.getActiveTrack()->getTreeModel();
//    auto tester = new QAbstractItemModelTester(modelToBeTested, QAbstractItemModelTester::FailureReportingMode::Fatal);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("inputHandler", &inputHdl);
    engine.rootContext()->setContextProperty("tracksManager", &tracksManager);
    engine.rootContext()->setContextProperty("mapBackend", &mapBackEnd);
    engine.load(QUrl(QStringLiteral("qrc:/qml/Qml/MainWindow.qml")));
    //engine.load(QUrl(QStringLiteral("qrc:/qml/Qml/HelpWindow.qml")));

#ifdef TEST_SIMPLETREEVIEW
    QWidget *wdg = new QWidget;
    wdg->show();

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView *tree = new QTreeView(wdg);
    tree->setModel(tracksManager.getActiveTrack()->getTreeModel());
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
        //tracksManager.getActiveTrack()->getTreeModel()->setData(tracksManager.getActiveTrack()->getTreeModel()->index(0, 0), QVariant::fromValue<QGeoCoordinate>(randCoord), MapMarkerTreeItem::MarkerCoordinate);
//        tracksManager.getActiveTrack()->getTreeModel()->setData(tracksManager.getActiveTrack()->getTreeModel()->index(0, 1), (double)rand() / RAND_MAX, MapMarkerTreeItem::MarkerCoordinateLatitude);
//        tracksManager.getActiveTrack()->getTreeModel()->setData(tracksManager.getActiveTrack()->getTreeModel()->index(0, 2), (double)rand() / RAND_MAX, MapMarkerTreeItem::MarkerCoordinateLongitude);
        prevID = rand();
        tracksManager.getActiveTrack()->getTreeModel()->setData(tracksManager.getActiveTrack()->getTreeModel()->index(0, 0), prevID, MapMarkerTreeItem::MarkerId);
        //simpleModel->setData(simpleModel->index(1,1), rand());
    });
#endif // TEST_SIMPLETREEVIEW

    DiscoverMainWindow mainWindow{qobject_cast<QQuickWindow*>(engine.rootObjects().at(0))};
    mainWindow.connectInputs(&inputHdl);
    mainWindow.show();

    return app.exec();
}
