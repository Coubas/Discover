//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "Track.h"

Track::Track(QObject *parent)
    : QObject{parent}
    , m_name{""}
{
    m_author = qgetenv("USER");
    if (m_author.isEmpty())
    {
        m_author = qgetenv("USERNAME");
    }
}

void Track::setPointList(const MapMarkerList &_points)
{
    for(const MapMarkerItem& point : _points.items())
    {
        m_points.appendMarker(point);
    }
}

void Track::addPoint(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/, int _insertIndex /*= -1*/)
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

void Track::setPointCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    m_points.setMarkerCoordinate(_markerId, _coord);
}

void Track::removeSelectedPoints()
{
    m_points.removeSelectedMarkers();
}

void Track::changePointIndex(int _oldIndex, int _newIndex)
{
    m_points.changeMarkerIndex(_oldIndex, _newIndex);
}

const QString& Track::name() const
{
    return m_name;
}

void Track::setName(const QString& _newName)
{
    m_name = _newName;
}

QString Track::author() const
{
    return m_author;
}

void Track::setAuthor(const QString& _newAuthor)
{
    m_author = _newAuthor;
}

void Track::computeBounds(QPair<double, double> &_latBounds, QPair<double, double> &_lonBounds) const
{
    _latBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
    _lonBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};

    for(const MapMarkerItem& marker : m_points.items())
    {
        const QGeoCoordinate& coord = marker.markerCoordinate();

        _latBounds.first = qMin(_latBounds.first, coord.latitude());
        _latBounds.second = qMax(_latBounds.second, coord.latitude());

        _lonBounds.first = qMin(_lonBounds.first, coord.longitude());
        _lonBounds.second = qMax(_lonBounds.second, coord.longitude());
    }
}

QDataStream& operator<<(QDataStream& _ds, const Track& _trk)
{
    _ds << _trk.name()
        << _trk.author()
        << *(_trk.getPointList());
    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, Track& _trk)
{
    QString input;
    _ds >> input;
    _trk.setName(input);

    _ds >> input;
    _trk.setAuthor(input);

    MapMarkerList markers;
    _ds >> markers;
    _trk.setPointList(markers);

    return _ds;
}
