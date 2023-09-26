//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "InputHandler.h"

InputHandler::InputHandler(QObject *parent)
    : QObject{parent}
{}

void InputHandler::onMapZoomed(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor)
{
    emit mapZoomed(_centerCoord, _mouseCoord, _zoomFactor);
}

void InputHandler::onMapDraged(const QGeoCoordinate& _newMapCenter)
{
    emit mapDraged(_newMapCenter);
}

void InputHandler::onMapClicked(const QGeoCoordinate& _mouseCoord)
{
    emit mapClicked(_mouseCoord);
}

void InputHandler::onCursorPosChanged(const QGeoCoordinate &_coord)
{
    emit cursorPosChanged(_coord);
}

void InputHandler::onCursorGeolocComputed(const QGeoLocation& _loc)
{
    emit cursorGeolocComputed(_loc);
}
