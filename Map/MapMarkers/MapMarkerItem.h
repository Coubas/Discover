//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef MAPMARKERITEM_H
#define MAPMARKERITEM_H

#include <QGeoCoordinate>

class MapMarkerItem
{
public:
    MapMarkerItem();
    MapMarkerItem(int _id, const QString& _type, const QGeoCoordinate& _coord, bool _selected = false);

    bool operator==(const MapMarkerItem& _other) const { return m_markerId == _other.m_markerId && m_markerCoordinate == _other.m_markerCoordinate; }
    bool operator!=(const MapMarkerItem& _other) const { return !operator==(_other); }

    int markerId() const;
    void setMarkerId(int newMarkerId);

    QString markerType() const;
    void setMarkerType(const QString &newMarkerType);

    QGeoCoordinate markerCoordinate() const;
    void setMarkerCoordinate(const QGeoCoordinate &newMarkerCoordinate);
    bool selected() const;
    void setSelected(bool newSelected);


private:
    int m_markerId{-1};
    QString m_markerType{"invalidType"};
    QGeoCoordinate m_markerCoordinate{0.0, 0.0};
    bool m_selected{false};
};

QDataStream &operator<<(QDataStream& _ds, const MapMarkerItem& _mrk);
QDataStream &operator>>(QDataStream& _ds, MapMarkerItem& _mrk);

#endif // MAPMARKERITEM_H
