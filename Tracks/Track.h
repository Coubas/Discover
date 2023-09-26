//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef TRACK_H
#define TRACK_H

#include <QObject>

#include <MapMarkerList.h>
#include <MapMarkerTreeItem.h>

class Track : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerList* points READ getPointList CONSTANT)

public:
    explicit Track(QObject *parent = nullptr);

    MapMarkerList* getPointList() {return &m_points;}
    const MapMarkerList* getPointList() const {return &m_points;}
    void setPointList(const MapMarkerList& _points);
    qsizetype size() const {return m_points.size();}

    void addPoint(const QGeoCoordinate& _coord, const QString& _type = "pin", int _insertIndex = -1);
    void removePoint(int _markerId);
    void setPointSelected(int _markerId, bool _selected = true);
    void setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPoints();
    void changePointIndex(int _oldIndex, int _newIndex);
    const QVariantList& getWaypoints() const { return m_points.getWaypoints(); }

    const QString& name() const;
    void setName(const QString& _newName);
    QString author() const;
    void setAuthor(const QString& _newAuthor);

    void clear()
    {
        m_name = "";
        m_author = "";
        m_points.clear();
    }

    void computeBounds(QPair<double, double>& _latBounds, QPair<double, double>& _lonBounds) const;

signals:

private:
    QString m_name;
    QString m_author;
    MapMarkerList m_points;
};

QDataStream &operator<<(QDataStream& _ds, const Track& _trk);
QDataStream &operator>>(QDataStream& _ds, Track& _trk);

#endif // TRACK_H
