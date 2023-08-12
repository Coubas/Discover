#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickItem>
#include <QGeoAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Discover");
    //showMaximized();

    connectWindowElements();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::connectWindowElements()
{
    const QQuickItem* item = ui->mapWidget->rootObject();
    if(QObject* mouseArea = item->findChild<QObject*>("mouseArea"))
    {
        connect(mouseArea, SIGNAL(displayCurrentPos(QGeoCoordinate)), this, SLOT(displayCurrentPos(QGeoCoordinate)));
    }

    if(QObject* geoModel = item->findChild<QObject*>("geoModel"))
    {
        connect(geoModel, SIGNAL(displayAdress(QGeoLocation)), this, SLOT(displayAdress(QGeoLocation)));
    }
}
