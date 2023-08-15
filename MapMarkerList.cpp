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

void MapMarkerList::removeItem(int _index)
{
    if(_index >= 0 & _index < m_markers.size())
    {
        emit preItemRemoved(_index);

        int removedId = m_markers[_index].markerId();
        m_markers.removeAt(_index);

        emit postItemRemoved();

        updateMarkerIdsOnRemove(removedId);
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

void MapMarkerList::updateMarkerIdsOnRemove(int _removedId)
{
    int modifBounds[2]{-1, -1};
    for (int i = 0; i < m_markers.size(); ++i)
    {
        int markerId = m_markers[i].markerId();
        if(markerId > _removedId)
        {
            m_markers[i].setMarkerId(markerId - 1);

            if(modifBounds[0] < 0)
            {
                modifBounds[0] = i;
            }
            modifBounds[1] = i;
        }
    }

    if(modifBounds[0] >= 0)
    {
        QList<int> modifiedRole{};
        modifiedRole.append(MapMarkerModel::MarkerField::MarkerId);
        emit dataChanged(modifBounds[0], modifBounds[1], modifiedRole);
    }
}
