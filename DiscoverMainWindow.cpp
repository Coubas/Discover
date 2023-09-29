//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

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
//    m_window->setIcon(QIcon("Discover/Images/Icons/explore.svg"));
    m_window->setIcon(QIcon("Discover/moto.ico"));

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
