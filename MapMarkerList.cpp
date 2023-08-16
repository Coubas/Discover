#include "MapMarkerList.h"

#include <QGeoCoordinate>
#include <QList>

#include <MapMarkerModel.h>

MapMarkerList::MapMarkerList(QObject *parent)
    : QObject{parent}
{}

const QVector<MapMarkerItem>& MapMarkerList::items() const
{
    return m_markers;
}

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
    }
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
        updateMarkerIdsOnRemove(firstRemovedId);
    }
}

void MapMarkerList::appendMarker()
{
    MapMarkerItem item;
    appendMarker(item);
}

void MapMarkerList::appendMarker(MapMarkerItem _item)
{
    emit preItemAppended();

    m_markers.append(_item);

    emit postItemAppended();
}

void MapMarkerList::removeItem(int _index, bool _updateIds /*= true*/)
{
    if(_index >= 0 & _index < m_markers.size())
    {
        emit preItemRemoved(_index);

        int removedId = m_markers[_index].markerId();
        m_markers.removeAt(_index);

        emit postItemRemoved();

        if(_updateIds)
        {
            updateMarkerIdsOnRemove(removedId);
        }
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

void MapMarkerList::updateMarkerIdsOnRemove(int _firstRemovedId /*= 0*/)
{
    int modifBounds[2]{-1, -1};
    for (int i = _firstRemovedId; i < m_markers.size(); ++i)
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

    OnMarkerListModified(modifBounds, {MapMarkerModel::MarkerField::MarkerId});
}

void MapMarkerList::OnMarkerListModified(int (&_modifBounds)[2], std::initializer_list<int> _modifiedRoles /*= {}*/)
{
    QList<int> modifiedRole{};
    for (int role : _modifiedRoles)
    {
        modifiedRole.append(role);
    }

    if(_modifBounds[0] >= 0)
    {
        emit dataChanged(_modifBounds[0], _modifBounds[1], modifiedRole);
    }
}
