//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef TREETRACK_H
#define TREETRACK_H

#include <QObject>

#include <MapMarkerTreeModel.h>

class TreeTrack: public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerTreeModel* treeModel READ getTreeModel CONSTANT)

public:
    explicit TreeTrack(QObject *parent = nullptr);

    MapMarkerTreeModel* getTreeModel() {return &m_tree;}
    const MapMarkerTreeModel* getTreeModel() const {return &m_tree;}

//    qsizetype size() const {return m_points.size();}

    bool addPoint(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin", int _parentMarkerId = -1);
    bool addPointAfterFirstSelected(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool addPointAsChildOfFirstSelected(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool removePoint(int _markerId);
    bool setPointSelected(int _markerId, bool _selected = true);
    bool setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPoints();
    void removeAllPoints();
//    const QVariantList& getWaypoints() const { return m_points.getWaypoints(); }

    const QString& name() const;
    void setName(const QString& _newName);
    QString author() const;
    void setAuthor(const QString& _newAuthor);

    void clear()
    {
        m_name = "";
        m_author = "";

        m_tree.clear();
    }

    void computeBounds(QPair<double, double>& _latBounds, QPair<double, double>& _lonBounds) const;

private:
    QString m_name;
    QString m_author;

    MapMarkerTreeModel m_tree;
};

QDataStream &operator<<(QDataStream& _ds, const TreeTrack& _trk);
QDataStream &operator>>(QDataStream& _ds, TreeTrack& _trk);

#endif // TREETRACK_H
