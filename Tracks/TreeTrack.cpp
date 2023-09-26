//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "Tracks/TreeTrack.h"

#include <MapMarkerTreeItem.h>

TreeTrack::TreeTrack(QObject *parent)
    : QObject{parent}
    , m_name{""}
    , m_tree()
{
    m_author = qgetenv("USER");
    if (m_author.isEmpty())
    {
        m_author = qgetenv("USERNAME");
    }
}

bool TreeTrack::addPoint(const QString& _name, const QGeoCoordinate& _coord, const QString& _type /*= "pin"*/, int _parentMarkerId /*= -1*/)
{
    return m_tree.addNewMarker(_name, _coord, _type, _parentMarkerId);
}

bool TreeTrack::addPointAfterFirstSelected(const QString& _name, const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return m_tree.addNewMarkerAfterFirstSelected(_name, _coord, _type);
}

bool TreeTrack::addPointAsChildOfFirstSelected(const QString& _name, const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return m_tree.addNewMarkerAsChildOfFirstSelected(_name, _coord, _type);
}

bool TreeTrack::removePoint(int _markerId)
{
    return m_tree.removeMaker(_markerId);
}

bool TreeTrack::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    return m_tree.setMarkerSelected(_markerId, _selected);
}

bool TreeTrack::setPointCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    return m_tree.setMarkerCoordinate(_markerId, _coord);
}

void TreeTrack::removeSelectedPoints()
{
    m_tree.removeSelectedMarkers();
}

void TreeTrack::removeAllPoints()
{
    m_tree.removeAllMarkers();
}

const QString& TreeTrack::name() const
{
    return m_name;
}

void TreeTrack::setName(const QString& _newName)
{
    m_name = _newName;
}

QString TreeTrack::author() const
{
    return m_author;
}

void TreeTrack::setAuthor(const QString& _newAuthor)
{
    m_author = _newAuthor;
}

void TreeTrack::computeBounds(QPair<double, double> &_latBounds, QPair<double, double> &_lonBounds) const
{
    m_tree.computeBounds(_latBounds, _lonBounds);
}

QDataStream& operator<<(QDataStream& _ds, const TreeTrack& _trk)
{
    _ds << _trk.name()
        << _trk.author()
        << *(_trk.getTreeModel());

    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, TreeTrack& _trk)
{
    QString input;
    _ds >> input;
    _trk.setName(input);

    _ds >> input;
    _trk.setAuthor(input);

    _ds >> *(_trk.getTreeModel());

    return _ds;
}

