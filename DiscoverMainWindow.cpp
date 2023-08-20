#include "DiscoverMainWindow.h"

#include <QGeoAddress>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QQuickItem>
#include <QQuickWindow>

#include <InputHandler.h>

DiscoverMainWindow::DiscoverMainWindow(QQuickWindow* _parent)
    : QObject{_parent}
    , m_window{_parent}
{
    m_window->setTitle("Discover");

    bindWindowObjects();
}

void DiscoverMainWindow::connectInputs(const InputHandler* _inputHdl)
{
    if(_inputHdl == nullptr)
    {
        return;
    }

    connect(_inputHdl, SIGNAL(mapClicked(QGeoCoordinate)), this, SLOT(displayCurrentPos(QGeoCoordinate)));
    connect(_inputHdl, SIGNAL(cursorPosChanged(QGeoCoordinate)), this, SLOT(displayCurrentPos(QGeoCoordinate)));
    connect(_inputHdl, SIGNAL(cursorGeolocComputed(QGeoLocation)), this, SLOT(displayAdress(QGeoLocation)));
}

void DiscoverMainWindow::show(bool _fullscreen /*= false*/)
{
    _fullscreen ? m_window->showFullScreen() : m_window->show();
}

// Slots
void DiscoverMainWindow::displayCurrentPos(const QGeoCoordinate& _coord)
{
    //qDebug() << Q_FUNC_INFO << _coord;

    if(m_clickLatText != nullptr)
    {
        m_clickLatText->setProperty("text", QString::fromUtf8("%1").arg(_coord.latitude(), 0, 'f', 5));
    }

    if(m_clickLonText != nullptr)
    {
        m_clickLonText->setProperty("text", QString::fromUtf8("%1").arg(_coord.longitude(), 0, 'f', 5));
    }
}

void DiscoverMainWindow::displayAdress(const QGeoLocation& _loc)
{
    //qDebug() << Q_FUNC_INFO << _loc.address().text() << _loc.coordinate();

    if(m_clickAdressText != nullptr)
    {
        m_clickAdressText->setProperty("text", _loc.address().text());
    }
}

void DiscoverMainWindow::bindWindowObjects()
{
    m_clickLatText = m_window->findChild<QObject*>("clickLat");
    m_clickLonText = m_window->findChild<QObject*>("clickLon");
    m_clickAdressText = m_window->findChild<QObject*>("clickAdress");
}
