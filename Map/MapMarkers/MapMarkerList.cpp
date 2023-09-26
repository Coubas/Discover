//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "MapMarkerList.h"

#include <QGeoCoordinate>
#include <QList>

#include <MapMarkerModel.h>

MapMarkerList::MapMarkerList(QObject *parent)
    : QObject{parent}
    , m_markers{}
    , m_waypoints{}
{}

bool MapMarkerList::setItemAt(int _index, const MapMarkerItem &_item)
{
    if(_index < 0 || _index >= m_markers.size())
    {
        return false;
    }

    const MapMarkerItem& oldItem = m_markers.at(_index);
    if(_item == oldItem)
    {
        return false;
    }

    m_markers[_index] = _item;
    m_waypoints[_index] = QVariant::fromValue(_item.markerCoordinate());
    return true;
}

void MapMarkerList::removeMaker(int _markerId)
{
    int index = getMarkerIndex(_markerId);
    if(index >= 0)
    {
        removeItem(index);
    }
}

void MapMarkerList::setMarkerSelected(int _markerId, bool _selected /*= true*/)
{
    if(MapMarkerItem* marker = getMarker(_markerId))
    {
        marker->setSelected(_selected);
        emit dataChanged(_markerId, _markerId, {MapMarkerModel::MarkerField::MarkerIsSelected});
    }
}

void MapMarkerList::setMarkerCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    if(MapMarkerItem* marker = getMarker(_markerId))
    {
        marker->setMarkerCoordinate(_coord);
        emit dataChanged(_markerId, _markerId, {MapMarkerModel::MarkerField::MarkerCoordinate});
    }
    m_waypoints[_markerId] = QVariant::fromValue(_coord);
}

void MapMarkerList::removeSelectedMarkers()
{
    int firstRemovedId = -1;
    for (int i = 0; i < m_markers.size();)
    {
        if(m_markers[i].selected())
        {
            removeItem(i, false);

            if(firstRemovedId < 0)
            {
                firstRemovedId = i;
            }
        }
        else
        {
            i++;
        }
    }

    if(firstRemovedId >= 0)
    {
        updateMarkerIds(firstRemovedId);
    }
}

void MapMarkerList::changeMarkerIndex(int _oldMarkerId, int _newMarkerId)
{
    moveItem(_oldMarkerId, _newMarkerId);

}

void MapMarkerList::clear()
{
    emit preItemRemoved(0, m_markers.size() - 1);

    m_markers.clear();
    m_waypoints.clear();

    emit postItemRemoved();
}

void MapMarkerList::appendMarker()
{
    MapMarkerItem item;
    appendMarker(item);
}

void MapMarkerList::appendMarker(MapMarkerItem _item, int _insertIndex /*= -1*/)
{
    int index = _insertIndex >= 0 ? _insertIndex : m_markers.size();

    emit preItemAppended(index);

    m_markers.insert(index, _item);
    m_waypoints.insert(index, QVariant::fromValue(_item.markerCoordinate()));

    emit postItemAppended();

    updateMarkerIds(index);
}

void MapMarkerList::removeItem(int _index, bool _updateIds /*= true*/)
{
    if(_index >= 0 & _index < m_markers.size())
    {
        emit preItemRemoved(_index, _index);

        int removedId = m_markers[_index].markerId();
        m_markers.removeAt(_index);
        m_waypoints.removeAt(_index);

        emit postItemRemoved();

        if(_updateIds)
        {
            updateMarkerIds(removedId);
        }
    }
}

void MapMarkerList::moveItem(int _index, int _destIndex)
{
    if(_index >= 0 & _index < m_markers.size() && _destIndex != _index)
    {
        emit preItemMoved();

        m_markers.move(_index, _destIndex);
        m_waypoints.move(_index, _destIndex);

        emit postItemMoved(_index, _destIndex);

        updateMarkerIds(qMin(_index, _destIndex));
    }
}

const MapMarkerItem* MapMarkerList::getMarker(int _markerId) const
{
    auto it = std::find_if(m_markers.begin(), m_markers.end(), [=](const MapMarkerItem& _item){return _item.markerId() == _markerId;});
    if(it != m_markers.end())
    {
        return &(*it);
    }

    return nullptr;
}

MapMarkerItem *MapMarkerList::getMarker(int _markerId)
{
    return const_cast<MapMarkerItem*>(const_cast<const MapMarkerList*>(this)->getMarker(_markerId));
}

int MapMarkerList::getMarkerIndex(int _markerId) const
{
    for (int i = 0; i < m_markers.size(); ++i)
    {
        if(m_markers[i].markerId() == _markerId)
        {
            return i;
        }
    }

    return -1;
}

void MapMarkerList::updateMarkerIds(int _firstModifiedId /*= 0*/)
{
    int modifBounds[2]{-1, -1};
    for (int i = _firstModifiedId; i < m_markers.size(); ++i)
    {
        int markerId = m_markers[i].markerId();
        if(markerId != i)
        {
            m_markers[i].setMarkerId(i);

            if(modifBounds[0] < 0)
            {
                modifBounds[0] = i;
            }
            modifBounds[1] = i;
        }
    }

    //onMarkerListModified(modifBounds, {MapMarkerModel::MarkerField::MarkerId});
    onMarkerListModified(modifBounds);
}

void MapMarkerList::onMarkerListModified(int (&_modifBounds)[2], std::initializer_list<int> _modifiedRoles /*= {}*/)
{
    QList<int> modifiedRole{};
    if(_modifiedRoles.size() > 0)
    {
        for (int role : _modifiedRoles)
        {
            modifiedRole.append(role);
        }
    }
    else
    {
        modifiedRole = MapMarkerModel::ms_allRoles;
    }

    if(_modifBounds[0] >= 0)
    {
        emit dataChanged(_modifBounds[0], _modifBounds[1], modifiedRole);
    }
}

QDataStream& operator<<(QDataStream& _ds, const MapMarkerList& _mrkList)
{
    _ds << _mrkList.size();
    for(const MapMarkerItem& item : _mrkList.items())
    {
        _ds << item;
    }
    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, MapMarkerList& _mrkList)
{
    qsizetype nbMarkers;
    _ds >> nbMarkers;

    MapMarkerItem item;
    for (int i = 0; i < nbMarkers; ++i)
    {
        _ds >> item;
        _mrkList.appendMarker(item);
    }

    return _ds;
}
