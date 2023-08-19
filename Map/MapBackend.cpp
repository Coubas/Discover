#include "MapBackend.h"

#include <InputHandler.h>
#include <VecGeoCoord2D.h>

MapBackend::MapBackend(QObject *parent)
    : QObject{parent}
{}

void MapBackend::connectInputs(const InputHandler* _inputHdl)
{
    if(_inputHdl == nullptr)
    {
        return;
    }

    connect(_inputHdl, SIGNAL(mapClicked(QGeoCoordinate)), this, SLOT(onMapClick(QGeoCoordinate)));
    connect(_inputHdl, SIGNAL(mapZoomed(QGeoCoordinate,QGeoCoordinate,int)), this, SLOT(onMapZoom(QGeoCoordinate,QGeoCoordinate,int)));
    connect(_inputHdl, SIGNAL(mapDraged(QGeoCoordinate)), this, SLOT(onMapDrag(QGeoCoordinate)));
}

QGeoCoordinate MapBackend::locusPos() const
{
    return m_locusPos;
}

void MapBackend::setLocusPos(const QGeoCoordinate& _coord)
{
    if(m_locusPos == _coord)
    {
        return;
    }

    m_locusPos = _coord;
    emit locusPosUptated();
}

bool MapBackend::cursorVisible() const
{
    return m_cursorVisible;
}

void MapBackend::setCursorVisible(bool _newCursorVisible)
{
    if (m_cursorVisible == _newCursorVisible)
        return;
    m_cursorVisible = _newCursorVisible;
    emit cursorVisibleChanged();
}

QGeoCoordinate MapBackend::cursorPos() const
{
    return m_cursorPos;
}

void MapBackend::setCursorPos(const QGeoCoordinate& _newCursorPos)
{
    if (m_cursorPos == _newCursorPos)
        return;
    m_cursorPos = _newCursorPos;
    emit cursorPosChanged();
}

// Slots
void MapBackend::onMapClick(const QGeoCoordinate &_clickCoord)
{
    setCursorPos(_clickCoord);
    setCursorVisible(true);
}

void MapBackend::onMapZoom(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor)
{
    m_center = _centerCoord;
    m_mouse = _mouseCoord;

    updateZoomTarget(_zoomFactor);
}

void MapBackend::onMapDrag(const QGeoCoordinate& _newMapCenter)
{
    m_center = _newMapCenter;
    setLocusPos(_newMapCenter);
}

void MapBackend::updateZoomTarget(int _zoomFactor)
{
    VecGeoCoord2D delta{VecGeoCoord2D(m_mouse) - VecGeoCoord2D(m_center)};
    delta *= m_mouseMvtSmoothRatioOnZoom;

    if(_zoomFactor < 0.0f)
    {
        delta *= -1.0;
    }

    setLocusPos({m_locusPos.latitude() + delta.x(), m_locusPos.longitude() + delta.y()});
}
