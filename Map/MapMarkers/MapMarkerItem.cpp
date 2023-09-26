//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "MapMarkerItem.h"

MapMarkerItem::MapMarkerItem() {}

MapMarkerItem::MapMarkerItem(int _id, const QString &_type, const QGeoCoordinate &_coord, bool _selected /*= false*/)
    : m_markerId(_id)
    , m_markerType(_type)
    , m_markerCoordinate(_coord)
    , m_selected(_selected)
{}

int MapMarkerItem::markerId() const
{
    return m_markerId;
}

void MapMarkerItem::setMarkerId(int newMarkerId)
{
    m_markerId = newMarkerId;
}

QString MapMarkerItem::markerType() const
{
    return m_markerType;
}

void MapMarkerItem::setMarkerType(const QString &newMarkerType)
{
    m_markerType = newMarkerType;
}

QGeoCoordinate MapMarkerItem::markerCoordinate() const
{
    return m_markerCoordinate;
}

void MapMarkerItem::setMarkerCoordinate(const QGeoCoordinate &newMarkerCoordinate)
{
    m_markerCoordinate = newMarkerCoordinate;
}

bool MapMarkerItem::selected() const
{
    return m_selected;
}

void MapMarkerItem::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

QDataStream &operator<<(QDataStream& _ds, const MapMarkerItem& _mrk)
{
    _ds << _mrk.markerId() << _mrk.selected() << _mrk.markerType() << _mrk.markerCoordinate();
    return _ds;
}

QDataStream &operator>>(QDataStream& _ds, MapMarkerItem& _mrk)
{
    int markerId{-1};
    bool selected{false};
    QString markerType{"invalidType"};
    QGeoCoordinate markerCoordinate{0.0, 0.0};
    _ds >> markerId >> selected >> markerType >> markerCoordinate;

    _mrk.setMarkerId(markerId);
    _mrk.setSelected(selected);
    _mrk.setMarkerType(markerType);
    _mrk.setMarkerCoordinate(markerCoordinate);

    return _ds;
}
