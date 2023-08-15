#include "Track.h"

Track::Track(QObject *parent)
    : QObject{parent}
{

}

void Track::addPoint(const QGeoCoordinate &_coord, const QString &_type /*= "circle"*/)
{
    m_points.appendMarker(MapMarkerItem(m_points.size(), _type, _coord));
}

void Track::removePoint(int _markerId)
{
    m_points.removeMaker(_markerId);
}

void Track::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    m_points.setMarkerSelected(_markerId, _selected);
}
