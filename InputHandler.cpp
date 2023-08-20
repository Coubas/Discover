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
