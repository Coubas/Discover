#include "TracksManager.h"

#include <InputHandler.h>

TracksManager::TracksManager(QObject *parent)
    : QObject{parent}
{
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

void TracksManager::addPointToActiveTrack(const QGeoCoordinate &_coord, int _insertIndex /*= -1*/, const QString& _type /*= "pin"*/)
{
    getActiveTrack()->addPoint(_coord, _insertIndex, _type);
    emit getActiveTrackSizeChanged();
}

void TracksManager::removePointFromActiveTrack(int _markerId)
{
    getActiveTrack()->removePoint(_markerId);
    emit getActiveTrackSizeChanged();
}

void TracksManager::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    getActiveTrack()->setPointSelected(_markerId, _selected);
}

void TracksManager::removeSelectedPointsFromActiveTrack()
{
    getActiveTrack()->removeSelectedPoints();
    emit getActiveTrackSizeChanged();
}

void TracksManager::changePointIndexFromActiveTrack(int _oldIndex, int _newIndex)
{
    getActiveTrack()->changePointIndex(_oldIndex, _newIndex);
}
