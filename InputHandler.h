//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QObject>

class InputHandler : public QObject
{
    Q_OBJECT

public:
    explicit InputHandler(QObject *parent = nullptr);

public slots:
    void onMapZoomed(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor);
    void onMapDraged(const QGeoCoordinate& _newMapCenter);
    void onMapClicked(const QGeoCoordinate& _mouseCoord);

    void onCursorGeolocComputed(const QGeoLocation& _loc);
    void onCursorPosChanged(const QGeoCoordinate& _coord);

signals:
    void mapZoomed(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor);
    void mapDraged(const QGeoCoordinate& _newMapCenter);
    void mapClicked(const QGeoCoordinate& _mouseCoord);

    void cursorPosChanged(const QGeoCoordinate& _coord);
    void cursorGeolocComputed(const QGeoLocation& _loc);
};

#endif // INPUTHANDLER_H
