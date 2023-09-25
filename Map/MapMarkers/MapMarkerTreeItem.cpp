#include "MapMarkerTreeItem.h"

const QList<int> MapMarkerTreeItem::ms_columns{MapMarkerTreeItem::MarkerIsActive, MapMarkerTreeItem::MarkerLinearIndexInActiveHierarchy, MapMarkerTreeItem::MarkerName, MapMarkerTreeItem::MarkerIsLoop};

MapMarkerTreeItem::MapMarkerTreeItem(MapMarkerTreeItem* _parent /*= nullptr*/, const MapMarkerTreeItem *_source /*= nullptr*/)
    : m_parentItem(_parent)
{
    if(_source != nullptr)
    {
        this->setMarkerData(_source->m_markerData);

        if(!_source->m_childItems.empty())
        {
            for(const MapMarkerTreeItem* child : _source->m_childItems)
            {
                this->appendChild(child);
            }
        }
    }
}

MapMarkerTreeItem::~MapMarkerTreeItem()
{
    qDeleteAll(m_childItems);
}

int MapMarkerTreeItem::getColumnIdFromRole(int _role) const
{
    if(_role < MarkerId || _role >= MarkerRoleCount)
    {
        return -1;
    }


    for (int i = 0; i < ms_columns.size(); ++i)
    {
        if(ms_columns[i] == _role)
        {
            return i;
        }
    }

    return -1;
}

int MapMarkerTreeItem::getRoleIdFromColumn(int _column) const
{
    return ms_columns[_column];
}

MapMarkerTreeItem* MapMarkerTreeItem::parent()
{
    return m_parentItem;
}

const MapMarkerTreeItem* MapMarkerTreeItem::parent() const
{
    return m_parentItem;
}

MapMarkerTreeItem* MapMarkerTreeItem::child(int _row)
{
    if (_row < 0 || _row >= m_childItems.size())
    {
        return nullptr;
    }
    return m_childItems.at(_row);
}

const MapMarkerTreeItem* MapMarkerTreeItem::child(int _row) const
{
    if (_row < 0 || _row >= m_childItems.size())
    {
        return nullptr;
    }
    return m_childItems.at(_row);
}

int MapMarkerTreeItem::childCount() const
{
    return m_childItems.count();
}

int MapMarkerTreeItem::childNumber() const
{
    if (m_parentItem)
    {
        return m_parentItem->m_childItems.indexOf(const_cast<MapMarkerTreeItem*>(this));
    }
    return 0;
}

int MapMarkerTreeItem::columnCount() const
{
    return ms_columns.size();
    //return m_itemData.count();
}

QVariant MapMarkerTreeItem::data(int _role /*= Qt::DisplayRole*/) const
{
    switch (_role)
    {
    case MarkerId:
        return QVariant(m_markerData.markerId);
    case MarkerType:
        return QVariant(m_markerData.markerType);
    case MarkerCoordinate:
        return QVariant::fromValue<QGeoCoordinate>(m_markerData.markerCoordinate);
    case MarkerName:
        return QVariant(m_markerData.markerName);
    case MarkerIsLoop:
        return QVariant(m_markerData.loop);
    case MarkerIsSelected:
        return QVariant(m_markerData.selected);
    case MarkerIsActive:
        return QVariant(m_markerData.active);
    case MarkerCoordinateLatitude:
        return QVariant(m_markerData.markerCoordinate.latitude());
    case MarkerCoordinateLongitude:
        return QVariant(m_markerData.markerCoordinate.longitude());
    case MarkerLinearIndex:
        return QVariant(m_linearIndex);
    case MarkerLinearIndexInActiveHierarchy:
        return QVariant(m_linearIndexActiveHierarchy);
    }

    return QVariant();
}

bool MapMarkerTreeItem::setData(const QVariant& _value, int _role /*= Qt::EditRole*/)
{
    switch (_role)
    {
    case MarkerId:
        m_markerData.markerId =_value.toInt();
        break;
    case MarkerType:
        m_markerData.markerType = _value.toString();
        break;
    case MarkerCoordinate:
        m_markerData.markerCoordinate = _value.value<QGeoCoordinate>();
        break;
    case MarkerName:
        m_markerData.markerName = _value.toString();
    case MarkerIsLoop:
        m_markerData.loop = _value.toBool();
        break;
    case MarkerIsSelected:
        m_markerData.selected = _value.toBool();
        break;
    case MarkerIsActive:
        m_markerData.active = _value.toBool();
        break;
    case MarkerCoordinateLatitude:
        m_markerData.markerCoordinate.setLatitude(_value.toDouble());
        break;
    case MarkerCoordinateLongitude:
        m_markerData.markerCoordinate.setLongitude(_value.toDouble());
        break;
    case MarkerLinearIndex:
        m_linearIndex = _value.toInt();
        break;
    case MarkerLinearIndexInActiveHierarchy:
        m_linearIndexActiveHierarchy = _value.toInt();
        break;
    }

    return true;
}

bool MapMarkerTreeItem::appendChild(const MapMarkerTreeItemData& _data)
{
    MapMarkerTreeItem* item = new MapMarkerTreeItem(this);
    item->setMarkerData(_data);
    m_childItems.append(item);
    return true;
}

bool MapMarkerTreeItem::appendChild(const MapMarkerTreeItem* _source)
{
    MapMarkerTreeItem* item = new MapMarkerTreeItem(this, _source);
    m_childItems.append(item);
    return true;
}

bool MapMarkerTreeItem::insertChild(int _position, const MapMarkerTreeItemData &_data)
{
    MapMarkerTreeItem* item = new MapMarkerTreeItem(this);
    item->setMarkerData(_data);
    m_childItems.insert(_position, item);
    return true;
}

bool MapMarkerTreeItem::insertChild(int _position, const MapMarkerTreeItem* _source)
{
    MapMarkerTreeItem* item = new MapMarkerTreeItem(this, _source);
    m_childItems.insert(_position, item);
    return true;
}

bool MapMarkerTreeItem::insertChildren(int _position, int _count)
{
    if (_position < 0 || _position > m_childItems.size())
    {
        return false;
    }

    for (int row = 0; row < _count; ++row)
    {
        MapMarkerTreeItem* item = new MapMarkerTreeItem(this);
        m_childItems.insert(_position, item);
    }

    return true;
}

bool MapMarkerTreeItem::removeChildren(int _position, int _count)
{
    if (_position < 0 || _position + _count > m_childItems.size())
    {
        return false;
    }

    for (int row = 0; row < _count; ++row)
    {
        delete m_childItems.takeAt(_position);
    }

    return true;
}

const MapMarkerTreeItemData& MapMarkerTreeItem::markerData() const
{
    return m_markerData;
}

MapMarkerTreeItemData& MapMarkerTreeItem::markerData()
{
    return m_markerData;
}

void MapMarkerTreeItem::setMarkerData(const MapMarkerTreeItemData &newMarkerData)
{
    m_markerData = newMarkerData;
}

bool MapMarkerTreeItem::inActiveHierarchy() const
{
    return m_inActiveHierarchy;
}

void MapMarkerTreeItem::setInActiveHierarchy(bool newInActiveHierarchy)
{
    m_inActiveHierarchy = newInActiveHierarchy;
}

int MapMarkerTreeItem::linearIndex() const
{
    return m_linearIndex;
}

void MapMarkerTreeItem::setLinearIndex(int newLinearIndex)
{
    m_linearIndex = newLinearIndex;
}

int MapMarkerTreeItem::linearIndexActiveHierarchy() const
{
    return m_linearIndexActiveHierarchy;
}

void MapMarkerTreeItem::setLinearIndexActiveHierarchy(int newLinearIndexActiveHierarchy)
{
    m_linearIndexActiveHierarchy = newLinearIndexActiveHierarchy;
}

VisitorReturn MapMarkerTreeItem::visit(std::function<VisitorReturn (MapMarkerTreeItem *)> _function, std::function<VisitorReturn (MapMarkerTreeItem *)> _postChildFunction /*= {}*/)
{
    VisitorReturn result = m_parentItem == nullptr ? VisitorReturn::VisitorContinue : _function(this); // Root item is an empty item
    switch (result)
    {
    case VisitorBreak:
        return VisitorBreak;
    case VisitorIgnoreChilds: // Ignore Child won't propagate up the tree so return Continue.
        result =  VisitorContinue;
        break;
    case VisitorContinue:
        for(MapMarkerTreeItem* child : m_childItems)
        {
            result = child->visit(_function, _postChildFunction);
            if(result == VisitorBreak)
            {
                return result;
            }
        }
        break;
    default: // Something whent wrong
        return VisitorBreak;
    }

    if(_postChildFunction)
    {
        return _postChildFunction(this);
    }

    return result;
}

VisitorReturn MapMarkerTreeItem::visitChilds(std::function<VisitorReturn (MapMarkerTreeItem *)> _function)
{
    VisitorReturn result = VisitorReturn::VisitorContinue;
    for(MapMarkerTreeItem* child : m_childItems)
    {
        result = child->visit(_function);
        if(result == VisitorBreak)
        {
            return result;
        }
    }

    return result;
}

int MapMarkerTreeItem::count() const
{
    int count = m_parentItem == nullptr ? 0 : 1; // Root item is an empty item that doesn't count
    for(MapMarkerTreeItem* child : m_childItems)
    {
        count += child->count();
    }
    return count;
}

bool MapMarkerTreeItem::hasVisibleChild()
{
    bool found = false;

    auto visibleChild= [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            found = true;
            return VisitorReturn::VisitorBreak;
        }
        else
        {
            return VisitorReturn::VisitorIgnoreChilds;
        }
    };
    visitChilds(visibleChild);

    return found;
}

//bool MapMarkerTreeItem::insertColumns(int _position, int _count)
//{
//    if (_position < 0 || _position > m_itemData.size())
//    {
//        return false;
//    }

//    for (int column = 0; column < _count; ++column)
//    {
//        m_itemData.insert(_position, QVariant());
//    }

//    for (MapMarkerTreeItem* child : std::as_const(m_childItems))
//    {
//        child->insertColumns(_position, _count);
//    }

//    return true;
//}

//bool MapMarkerTreeItem::removeColumns(int _position, int _count)
//{
//    if (_position < 0 || _position + _count > m_itemData.size())
//    {
//        return false;
//    }

//    for (int column = 0; column < _count; ++column)
//    {
//        m_itemData.remove(_position);
//    }

//    for (MapMarkerTreeItem* child : std::as_const(m_childItems))
//    {
//        child->removeColumns(_position, _count);
//    }

//    return true;
//}

QDataStream &operator<<(QDataStream& _ds, const MapMarkerTreeItemData& _data)
{
    _ds << _data.markerId
        << _data.markerType
        << _data.markerCoordinate
        << _data.loop
        << _data.selected
        << _data.active;

    return _ds;
}

QDataStream &operator>>(QDataStream& _ds, MapMarkerTreeItemData& _data)
{
    _ds >> _data.markerId
        >> _data.markerType
        >> _data.markerCoordinate
        >> _data.loop
        >> _data.selected
        >> _data.active;

    return _ds;
}

QDataStream& operator<<(QDataStream& _ds, const MapMarkerTreeItem& _item)
{
    _ds << _item.markerData();

    _ds << _item.linearIndex()
        << _item.inActiveHierarchy()
        << _item.linearIndexActiveHierarchy();

    int childCount = _item.childCount();
    _ds << childCount;

    for(int i = 0; i < childCount; ++i)
    {
        _ds << *(_item.child(i));
    }

    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, MapMarkerTreeItem& _item)
{
    MapMarkerTreeItemData data;
    _ds >> data;
    _item.setMarkerData(data);

    int val;
    _ds >> val;
    _item.setLinearIndex(val);

    bool inActiveHierarchy;
    _ds >> inActiveHierarchy;
    _item.setInActiveHierarchy(inActiveHierarchy);

    _ds >> val;
    _item.setLinearIndexActiveHierarchy(val);

    _ds >> val;
    _item.insertChildren(0, val);
    for(int i = 0; i < val; ++i)
    {
        _ds >> *(_item.child(i));
    }

    return _ds;
}
