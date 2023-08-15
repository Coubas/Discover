#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQmlContext>
#include <QQuickItem>
#include <QGeoAddress>

#include <InputHandler.h>
#include <MapBackend.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Discover");
    //showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectInputs(const InputHandler* _inputHdl)
{
    if(_inputHdl == nullptr)
    {
        return;
    }

    connect(_inputHdl, SIGNAL(mapClicked(QGeoCoordinate)), this, SLOT(displayCurrentPos(QGeoCoordinate)));
    connect(_inputHdl, SIGNAL(cursorGeolocComputed(QGeoLocation)), this, SLOT(displayAdress(QGeoLocation)));
}

void MainWindow::connectWindowElements(const InputHandler* _inputHdl)
{
    const QQuickItem* item = ui->mapWidget->rootObject();

    // Elements listened by the InputHandler
    if(QObject* wheelHandler = item->findChild<QObject*>("wheelHandler"))
    {
        connect(wheelHandler, SIGNAL(mapZoomed(QGeoCoordinate,QGeoCoordinate,int)), _inputHdl, SLOT(onMapZoomed(QGeoCoordinate,QGeoCoordinate,int)));
    }

    if(QObject* dragHandler = item->findChild<QObject*>("dragHandler"))
    {
        connect(dragHandler, SIGNAL(mapDraged(QGeoCoordinate)), _inputHdl, SLOT(onMapDraged(QGeoCoordinate)));
    }

    if(QObject* mouseArea = item->findChild<QObject*>("mouseArea"))
    {
        connect(mouseArea, SIGNAL(mapClicked(QGeoCoordinate)), _inputHdl, SLOT(onMapClicked(QGeoCoordinate)));
    }

    if(QObject* geoModel = item->findChild<QObject*>("geoModel"))
    {
        connect(geoModel, SIGNAL(cursorGeolocComputed(QGeoLocation)), _inputHdl, SLOT(onCursorGeolocComputed(QGeoLocation)));
    }
}

void MainWindow::setMapViewContextProperty(const QString &_name, QObject *_value)
{
    QQmlContext* context = ui->mapWidget->rootContext();
    context->setContextProperty(_name, _value);
}

// Slots
void MainWindow::displayCurrentPos(QGeoCoordinate _coord)
{
    qDebug() << Q_FUNC_INFO << _coord;
    ui->currentLat->setText(QString::fromUtf8("%1").arg(_coord.latitude(), 0, 'f', 5));
    ui->currentLon->setText(QString::fromUtf8("%1").arg(_coord.longitude(), 0, 'f', 5));
}

void MainWindow::displayAdress(QGeoLocation _loc)
{
    qDebug() << Q_FUNC_INFO << _loc.address().text() << _loc.coordinate();
    ui->selectedAdress->setText(_loc.address().text());
}
