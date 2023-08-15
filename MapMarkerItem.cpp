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
