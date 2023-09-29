//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef MAPBACKEND_H
#define MAPBACKEND_H

#include "qqmlintegration.h"
#include <QObject>
#include <QGeoCoordinate>
#include <QVector2D>

class InputHandler;

class MapBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float zoomLevel READ currentZoomLevel WRITE setCurrentZoomLevel NOTIFY zoomLevelUpdated FINAL)
    Q_PROPERTY(QGeoCoordinate locusPos READ locusPos WRITE setLocusPos NOTIFY locusPosUptated FINAL)
    Q_PROPERTY(QGeoCoordinate cursorPos READ cursorPos WRITE setCursorPos NOTIFY cursorPosChanged FINAL)
    Q_PROPERTY(bool cursorVisible READ cursorVisible WRITE setCursorVisible NOTIFY cursorVisibleChanged FINAL)
    QML_ELEMENT

public:
    explicit MapBackend(QObject *parent = nullptr);

    void connectInputs(const InputHandler* _inputHdl);

    float currentZoomLevel() const {return m_currentZoomLevel;}
    void setCurrentZoomLevel(float _zoomLevel) {m_currentZoomLevel = _zoomLevel;}
    QGeoCoordinate locusPos() const;
    void setLocusPos(const QGeoCoordinate& _coord);

    QGeoCoordinate cursorPos() const;
    void setCursorPos(const QGeoCoordinate& _newCursorPos);

    bool cursorVisible() const;
    void setCursorVisible(bool _newCursorVisible);

signals:
    void locusPosUptated();
    void zoomLevelUpdated();
    void cursorPosChanged();
    void cursorVisibleChanged();

public slots:
    void onMapClick(const QGeoCoordinate& _clickCoord);
    void onMapZoom(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor);
    void onMapDrag(const QGeoCoordinate& _newMapCenter);

private:
    void updateZoomTarget(int _zoomFactor);

    double m_mouseMvtSmoothRatioOnZoom{0.1};

    float m_currentZoomLevel{};
    QGeoCoordinate m_locusPos{};
    QGeoCoordinate m_center{};
    QGeoCoordinate m_mouse{};
    QGeoCoordinate m_cursorPos{43.778958, 3.812109};
    bool m_cursorVisible{false};
};

#endif // MAPBACKEND_H
