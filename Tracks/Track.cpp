#include "Track.h"

Track::Track(QObject *parent)
    : QObject{parent}
{

}

void Track::addPoint(const QGeoCoordinate &_coord, int _insertIndex /*= -1*/, const QString &_type /*= "pin"*/)
{
    m_points.appendMarker(MapMarkerItem(m_points.size(), _type, _coord), _insertIndex);
}

void Track::removePoint(int _markerId)
{
    m_points.removeMaker(_markerId);
}

void Track::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    m_points.setMarkerSelected(_markerId, _selected);
}

void Track::removeSelectedPoints()
{
    m_points.removeSelectedMarkers();
}

void Track::changePointIndex(int _oldIndex, int _newIndex)
{
    m_points.changeMarkerIndex(_oldIndex, _newIndex);
}
