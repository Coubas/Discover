#include "TracksManager.h"

#include <InputHandler.h>

TracksManager::TracksManager(QObject *parent)
    : QObject{parent}
{
    m_track.setName("My first track");
    m_track.addPoint(QGeoCoordinate(43.78958, 3.812109), -1, "circle");
    m_track.addPoint(QGeoCoordinate(43.79958, 3.812109));
    m_track.addPoint(QGeoCoordinate(43.80958, 3.812109));
    m_track.addPoint(QGeoCoordinate(43.81958, 3.812109));
}

void TracksManager::connectInputs(const InputHandler* _inputHdl)
{
    if(_inputHdl == nullptr)
    {
        return;
    }

    //connect(_inputHdl, SIGNAL(mapClicked(QGeoCoordinate)), this, SLOT(addPointToActiveTrack(QGeoCoordinate)));
}

const QString &TracksManager::getActiveTrackName() const
{
    return getActiveTrack()->name();
}

void TracksManager::setActiveTrackName(const QString &_name)
{
    getActiveTrack()->setName(_name);
    emit activeTrackNameChanged();
}

void TracksManager::addPointToActiveTrack(const QGeoCoordinate &_coord, int _insertIndex /*= -1*/, const QString& _type /*= "pin"*/)
{
    getActiveTrack()->addPoint(_coord, _insertIndex, _type);
    emit activeTrackSizeChanged();
}

void TracksManager::removePointFromActiveTrack(int _markerId)
{
    getActiveTrack()->removePoint(_markerId);
    emit activeTrackSizeChanged();
}

void TracksManager::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    getActiveTrack()->setPointSelected(_markerId, _selected);
}

void TracksManager::setPointCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    getActiveTrack()->setPointCoordinate(_markerId, _coord);
}

void TracksManager::removeSelectedPointsFromActiveTrack()
{
    getActiveTrack()->removeSelectedPoints();
    emit activeTrackSizeChanged();
}

void TracksManager::changePointIndexFromActiveTrack(int _oldIndex, int _newIndex)
{
    getActiveTrack()->changePointIndex(_oldIndex, _newIndex);
}
