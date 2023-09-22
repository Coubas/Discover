#include "MapMarkerTreeModel.h"

#include <MapMarkerTreeItem.h>
#include <MapMarkerTreeListModel.h>

MapMarkerTreeModel::MapMarkerTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_root = new MapMarkerTreeItem();
    m_root->markerData().markerId = -1;
    m_root->setInActiveHierarchy(true);

    m_listModel = new MapMarkerTreeListModel{m_root};
}

MapMarkerTreeModel::~MapMarkerTreeModel()
{
    delete m_listModel;
    delete m_root;
}

int MapMarkerTreeModel::size() const
{
    if(m_root != nullptr)
    {
        return m_root->count();
    }

    return 0;
}

void MapMarkerTreeModel::clear()
{
    delete m_listModel;
    delete m_root;

    m_root = new MapMarkerTreeItem();
    m_root->markerData().markerId = -1;
    m_root->setInActiveHierarchy(true);

    m_listModel = new MapMarkerTreeListModel{m_root};

    m_highestLinearIndexInActiveHierarchy = -1;
}

QModelIndex MapMarkerTreeModel::index(int _row, int _column, const QModelIndex& _parent/* = QModelIndex()*/) const
{
//    qDebug() << Q_FUNC_INFO << "index("<<_row<<", "<<_column<<", "<<_parent<<")";
    if (_parent.isValid() && _parent.column() != 0)
        return QModelIndex();

    MapMarkerTreeItem* parentItem = getItem(_parent);
    if (!parentItem)
    {
        return QModelIndex();
    }

    if(MapMarkerTreeItem* childItem = parentItem->child(_row))
    {
//        qDebug() << Q_FUNC_INFO <<"createIndex("<<_row<<", "<<_column<<", "<<childItem->markerData().markerId<<")";
        return createIndex(_row, _column, childItem);
    }

    return QModelIndex();
}

QModelIndex MapMarkerTreeModel::index(const MapMarkerTreeItem* _item) const
{
    if(_item == m_root)
    {
        return QModelIndex();
    }

    QModelIndex index{};
    if(_item != nullptr)
    {
        index = createIndex(_item->childNumber(), 0, _item);
    }

    return index;
}

QModelIndex MapMarkerTreeModel::parent(const QModelIndex& _index) const
{
//    qDebug() << Q_FUNC_INFO << "parent("<<_index<<")";
    if (!_index.isValid() || m_root == nullptr)
    {
//        qDebug() << Q_FUNC_INFO <<"wrong index: "<<_index;
        return QModelIndex();
    }

    MapMarkerTreeItem* childItem = getItem(_index);
    MapMarkerTreeItem* parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == m_root || !parentItem)
    {
//        qDebug() << Q_FUNC_INFO <<"childId: "<<childItem->markerData().markerId<<" parent null";
        return QModelIndex();
    }
//    qDebug() << Q_FUNC_INFO <<"childId: "<<childItem->markerData().markerId<<" parentId: "<<parentItem->markerData().markerId << " createIndex row: "<<parentItem->childNumber();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int MapMarkerTreeModel::rowCount(const QModelIndex& _parent/* = QModelIndex()*/) const
{
    if (_parent.isValid() && _parent.column() > 0)
    {
        return 0;
    }

    if(const MapMarkerTreeItem* parentItem = getItem(_parent))
    {
//        qDebug() << Q_FUNC_INFO <<"row count: "<<parentItem->childCount();
        return parentItem->childCount();
    }

    return 0;
}

// Does not need to look for a particular item because all items are defined to have the same number of columns associated with them.
int MapMarkerTreeModel::columnCount(const QModelIndex& _parent/* = QModelIndex()*/) const
{
    Q_UNUSED(_parent);
    if(m_root != nullptr)
    {
//        qDebug() << Q_FUNC_INFO <<"column count: "<<m_root->columnCount();
        return m_root->columnCount();
    }

    return 0;
}

Qt::ItemFlags MapMarkerTreeModel::flags(const QModelIndex& _index) const
{
    if (!_index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(_index);
}

QHash<int, QByteArray> MapMarkerTreeModel::roleNames() const
{
    QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
    names[MapMarkerTreeItem::MarkerId] = "markerId";
    names[MapMarkerTreeItem::MarkerType] = "markerType";
    names[MapMarkerTreeItem::MarkerCoordinate] = "markerCoordinate";
    names[MapMarkerTreeItem::MarkerIsSelected] = "markerIsSelected";
    names[MapMarkerTreeItem::MarkerIsActive] = "markerIsActive";
    names[MapMarkerTreeItem::MarkerCoordinateLatitude] = "markerCoordinateLatitude";
    names[MapMarkerTreeItem::MarkerCoordinateLongitude] = "markerCoordinateLongitude";
    return names;
}

QVariant MapMarkerTreeModel::data(const QModelIndex& _index, int _role) const
{
    if (!_index.isValid())
    {
        return QVariant();
    }

    MapMarkerTreeItem* item = getItem(_index);
    if (_role == Qt::DisplayRole || _role == Qt::EditRole)
    {
        int role = item->getRoleIdFromColumn(_index.column());
        return item->data(role);
    }
    else
    {
        return item->data(_role);
    }
}

bool MapMarkerTreeModel::setData(const QModelIndex& _index, const QVariant& _value, int _role/* = Qt::EditRole*/)
{
    if (!_index.isValid())
    {
        return false;
    }

    if(MapMarkerTreeItem* item = getItem(_index))
    {
        if(item->setData(_value, _role))
        {
            int first = item->linearIndexActiveHierarchy();
            if(_role == MapMarkerTreeItem::MarkerIsActive && _value.toBool() &&
                !item->inActiveHierarchy() && item->parent()->inActiveHierarchy()) // Item wasn't in active hierarchy but will be now
            {
                first = getLinearIndexFromRoot(*item, true);
            }
            int last = first;
            if(_role == MapMarkerTreeItem::MarkerIsActive)
            {
                int nb = getNbVisibleChild(*item);
                last = first + nb;
            }
            if(first >= 0)
            {
                //qDebug() << Q_FUNC_INFO << "m_listModel->triggerDataChanged(" << first <<", " << last <<", " << roleNames()[_role] <<", " << _value <<")";
                m_listModel->triggerDataChanged(first, last, _role, _value);
            }

            if(_role == MapMarkerTreeItem::MarkerIsActive)
            {
                updateTreeItemIndexInfo();
            }

            QList<int> roles{Qt::DisplayRole, Qt::EditRole, _role};

            if(_role == MapMarkerTreeItem::MarkerCoordinate)
            {
                QModelIndex idLat = createIndex(_index.row(), item->getColumnIdFromRole(MapMarkerTreeItem::MarkerCoordinateLatitude), item);
                QModelIndex idLon = createIndex(_index.row(), item->getColumnIdFromRole(MapMarkerTreeItem::MarkerCoordinateLongitude), item);
                emit dataChanged(idLat, idLon, roles);
            }
            else if(_role == MapMarkerTreeItem::MarkerIsSelected)
            {
                QModelIndex idFirst = createIndex(_index.row(), 0, item);
                QModelIndex idLast = createIndex(_index.row(), columnCount() -1, item);
                emit dataChanged(idFirst, idLast);
            }
            else
            {
                QModelIndex id = createIndex(_index.row(), item->getColumnIdFromRole(_role), item);
                emit dataChanged(id, id, roles);
            }
            //qDebug() << Q_FUNC_INFO << "Emit dataChanged("<<_index<<", "<<_index<< ", "<<roles<<")";

            return true;
        }
    }

    return false;
}

QVariant MapMarkerTreeModel::headerData(int _section, Qt::Orientation _orientation, int _role /* = Qt::DisplayRole*/) const
{
    if(m_root == nullptr)
    {
        return QVariant();
    }

//    if (_orientation == Qt::Horizontal && _role == Qt::DisplayRole)
//    {
//        return m_rootItem->data(_section);
//    }

    if (_orientation == Qt::Horizontal && _role == Qt::DisplayRole)
    {
        return roleNames()[m_root->getRoleIdFromColumn(_section)];
    }

    return QVariant();
}

bool MapMarkerTreeModel::setHeaderData(int _section, Qt::Orientation _orientation, const QVariant& _value, int _role/* = Qt::EditRole*/)
{
    if(m_root == nullptr)
    {
        return false;
    }

    if (_role != Qt::EditRole || _orientation != Qt::Horizontal)
    {
        return false;
    }

//    if(m_rootItem->setData(_section, _value))
//    if(m_root->setData(_value, _section))
//    {
//        emit headerDataChanged(_orientation, _section, _section);
//        return true;
//    }

    return false;
}

//bool MapMarkerTreeModel::insertColumns(int _position, int _count, const QModelIndex& _parent/* = QModelIndex()*/)
//{
//    if(m_rootItem == nullptr)
//    {
//        return false;
//    }

//    beginInsertColumns(_parent, _position, _position + _count- 1);
//    const bool success = m_rootItem->insertColumns(_position, _count);
//    endInsertColumns();

//    return success;
//}

//bool MapMarkerTreeModel::removeColumns(int _position, int _count, const QModelIndex& _parent/* = QModelIndex()*/)
//{
//    if(m_rootItem == nullptr)
//    {
//        return false;
//    }

//    beginRemoveColumns(_parent, _position, _position + _count - 1);
//    const bool success = m_rootItem->removeColumns(_position, _count);
//    endRemoveColumns();

//    if (m_rootItem->columnCount() == 0)
//    {
//        removeRows(0, rowCount());
//    }

//    return success;
//}

bool MapMarkerTreeModel::insertRows(int _position, int _count, const QModelIndex& _parent/* = QModelIndex()*/)
{
    if (!_parent.isValid())
    {
        return false;
    }

    if(MapMarkerTreeItem* item = getItem(_parent))
    {
        beginInsertRows(_parent, _position, _position + _count - 1);
        const bool success = item->insertChildren(_position, _count);
        endInsertRows();

        return success;
    }

    return false;
}

bool MapMarkerTreeModel::removeRows(int _position, int _count, const QModelIndex& _parent/* = QModelIndex()*/)
{
    if (!_parent.isValid())
    {
        return false;
    }

    if(MapMarkerTreeItem* item = getItem(_parent))
    {
        beginRemoveRows(_parent, _position, _position + _count - 1);
        const bool success = item->removeChildren(_position, _count);
        endRemoveRows();

        return success;
    }

    return false;
}

void MapMarkerTreeModel::visit(std::function<VisitorReturn (MapMarkerTreeItem *)> _function) const
{
    m_root->visit(_function);
}

const QVariantList MapMarkerTreeModel::getWaypoints() const
{
    QVariantList waypoints;

    auto gatherWaypoints = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            waypoints.append(QVariant::fromValue(_treeItem->markerData().markerCoordinate));
        }
        else
        {
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(gatherWaypoints);

    return waypoints;
}

bool MapMarkerTreeModel::removeMaker(int _markerId)
{
    bool done = false;

    auto remove = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().markerId == _markerId)
        {
            done = removeItem(_treeItem);
            return VisitorReturn::VisitorBreak;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(remove);

    return done;
}

bool MapMarkerTreeModel::setMarkerSelected(int _markerId, bool _selected)
{
    bool done = false;

    auto setSelected = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().markerId == _markerId)
        {
            done = true;

            QModelIndex id = index(_treeItem);
            setData(id, _selected, MapMarkerTreeItem::MarkerIsSelected);

            return VisitorReturn::VisitorBreak;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(setSelected);

    return done;
}

bool MapMarkerTreeModel::setMarkerCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
//    qDebug() << Q_FUNC_INFO << "setMarkerCoordinate("<<_markerId<<", "<<_coord<<")";

    bool done = false;
    auto setCoordinate = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().markerId == _markerId)
        {
            done = true;

            QModelIndex id = index(_treeItem);
            setData(id, QVariant::fromValue<QGeoCoordinate>(_coord), MapMarkerTreeItem::MarkerCoordinate);

            return VisitorReturn::VisitorBreak;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(setCoordinate);

    return done;
}

void MapMarkerTreeModel::removeSelectedMarkers()
{
    auto removeSelected = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().selected)
        {
            removeItem(_treeItem);
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(removeSelected);
}

bool MapMarkerTreeModel::addNewMarker(const QGeoCoordinate& _coord, const QString& _type /*= "pin"*/, int _parentMarkerId /*= -1*/)
{
    bool done = false;

    if(_parentMarkerId == -1)
    {
        int insertIndex = m_root->childCount();
        int listInsterIndex = m_highestLinearIndexInActiveHierarchy + 1;

        beginInsertRows(index(m_root), insertIndex, insertIndex);
        m_listModel->triggerBeginInsertRows(listInsterIndex, listInsterIndex);

        MapMarkerTreeItemData markerData{ size(), _type, _coord, false, true};
        done = m_root->appendChild(markerData);

        m_listModel->triggerEndInsertRows();
        endInsertRows();
    }
    else
    {
        auto addMarker = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
        {
            if(_treeItem->markerData().markerId == _parentMarkerId)
            {
                QModelIndex id = index(_treeItem);
                beginInsertRows(id, _treeItem->childCount(), _treeItem->childCount());
//                qDebug() << Q_FUNC_INFO << "beginInsertRows(" << id  << ", " << _treeItem->childCount()  << ", " << _treeItem->childCount() << ")";
                if(_treeItem->inActiveHierarchy())
                {
                    int insertIndex = _treeItem->linearIndexActiveHierarchy() + getNbVisibleChild(*_treeItem) + 1;
                    m_listModel->triggerBeginInsertRows(insertIndex, insertIndex);
//                    qDebug() << Q_FUNC_INFO << "triggerBeginInsertRows(" << insertIndex << ", " << insertIndex << ")";
                }

                MapMarkerTreeItemData markerData{ size(), _type, _coord, false, true};
                done = _treeItem->appendChild(markerData);

                if(_treeItem->inActiveHierarchy())
                {
                    m_listModel->triggerEndInsertRows();
                }

                endInsertRows();

                return VisitorReturn::VisitorBreak;
            }

            return VisitorReturn::VisitorContinue;
        };
        visit(addMarker);
    }

    updateTreeItemIndexInfo();

    return done;
}

bool MapMarkerTreeModel::addNewMarkerAfterFirstSelected(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    bool done = false;
    MapMarkerTreeItem* firstSelectedMarkerId = getFirstSelectedMarkerId();

    if(firstSelectedMarkerId == m_root)
    {
        // No selected marker
        return false;
    }

    if(MapMarkerTreeItem* parent = firstSelectedMarkerId->parent())
    {
        done = addNewMarker(_coord, _type, parent->markerData().markerId);
    }

    return done;
}

bool MapMarkerTreeModel::addNewMarkerAsChildOfFirstSelected(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    bool done = false;
    MapMarkerTreeItem* firstSelectedMarkerId = getFirstSelectedMarkerId();

    if(firstSelectedMarkerId == m_root)
    {
        // No selected marker
        return false;
    }

    done = addNewMarker(_coord, _type, firstSelectedMarkerId->markerData().markerId);

    return done;
}

bool MapMarkerTreeModel::isValidMove(int _fromMarkerId, int _toMarkerId, bool addAfter)
{
    if(_fromMarkerId == _toMarkerId)
    {
        return false;
    }

    QModelIndex from = getIndexFromMarkerId(_fromMarkerId);
    QModelIndex to = getIndexFromMarkerId(_toMarkerId);

    int fromRow = from.row();
    int destRow = to.row();

    if(from.parent() == to.parent())
    {
        if((fromRow == destRow - 1 && !addAfter) ||
            (fromRow == destRow + 1 && addAfter))
        {
            //qDebug() << Q_FUNC_INFO << "aborted";
            return false;
        }
    }

    return true;
}

bool MapMarkerTreeModel::isValidNewChild(int _fromMarkerId, int _toMarkerId)
{
    if(_fromMarkerId == _toMarkerId)
    {
        return false;
    }

    QModelIndex from = getIndexFromMarkerId(_fromMarkerId);
    QModelIndex to = getIndexFromMarkerId(_toMarkerId);

    if(from.parent() == to)
    {
        return false;
    }

    return true;
}

void MapMarkerTreeModel::moveItem(int _fromMarkerId, int _toMarkerId, bool addAfter /*= false*/)
{
    if(_fromMarkerId == _toMarkerId)
    {
        return;
    }

    QModelIndex from = getIndexFromMarkerId(_fromMarkerId);
    QModelIndex to = getIndexFromMarkerId(_toMarkerId);

    int fromRow = from.row();
    int destRow = to.row();

    //qDebug() << Q_FUNC_INFO << "Move("<<fromRow<<", "<<destRow<<", "<<addAfter<<")";

    if(from.parent() == to.parent())
    {
        if((fromRow == destRow - 1 && !addAfter) ||
            (fromRow == destRow + 1 && addAfter))
        {
            //qDebug() << Q_FUNC_INFO << "aborted";
            return;
        }
    }

    if(addAfter)
    {
        ++destRow;
    }

    if(from.parent() == to.parent())
    {
        if(destRow < fromRow)
        {
            ++fromRow;
        }
    }

    beginMoveRows(from.parent(), from.row(), from.row(), to.parent(), destRow);

    MapMarkerTreeItem* source = getItem(from);
    MapMarkerTreeItem* sourceParent = getItem(from.parent());
    MapMarkerTreeItem* destParent = getItem(to.parent());

    bool shouldUpdateListModel = source->inActiveHierarchy() || (source->markerData().active && destParent->inActiveHierarchy());
    if(shouldUpdateListModel)
    {
        // Could be improved by using begin/endmoverows or begin/endremoverows (demending if the dest node is in active hierarchy or not)
        // But this seems fine for now
        m_listModel->triggerBeginResetModel();
    }

    if(source != nullptr && sourceParent != nullptr && destParent != nullptr)
    {
        destParent->insertChild(destRow, source);
        sourceParent->removeChildren(fromRow, 1);

        updateTreeItemIndexInfo();
    }

    if(shouldUpdateListModel)
    {
        m_listModel->triggerEndResetModel();
    }

    endMoveRows();
}

void MapMarkerTreeModel::addItemAsChild(int _fromMarkerId, int _toMarkerId)
{
    if(_fromMarkerId == _toMarkerId)
    {
        return;
    }

    QModelIndex from = getIndexFromMarkerId(_fromMarkerId);
    QModelIndex to = getIndexFromMarkerId(_toMarkerId);

    if(from.parent() == to)
    {
        return;
    }

    MapMarkerTreeItem* source = getItem(from);
    MapMarkerTreeItem* sourceParent = getItem(from.parent());
    MapMarkerTreeItem* dest = getItem(to);

    beginMoveRows(from.parent(), from.row(), from.row(), to, dest->childCount());

    bool shouldUpdateListModel = source->inActiveHierarchy() || (source->markerData().active && dest->inActiveHierarchy());
    if(shouldUpdateListModel)
    {
        // Could be improved by using begin/endmoverows or begin/endremoverows (demending if the dest node is in active hierarchy or not)
        // But this seems fine for now
        m_listModel->triggerBeginResetModel();
    }

    if(source != nullptr && sourceParent != nullptr && dest != nullptr)
    {
        dest->appendChild(source);
        sourceParent->removeChildren(from.row(), 1);

        updateTreeItemIndexInfo();
    }

    if(shouldUpdateListModel)
    {
        m_listModel->triggerEndResetModel();
    }

    endMoveRows();
}

MapMarkerTreeItem* MapMarkerTreeModel::getItem(const QModelIndex& _index) const
{
    if (_index.isValid())
    {
        if(MapMarkerTreeItem* item = static_cast<MapMarkerTreeItem*>(_index.internalPointer()))
        {
            return item;
        }
    }

    return m_root;
}

// Active marker, if(_includeFirstRankDisabled) match if parent is active.
bool MapMarkerTreeModel::isInActiveHierarchy(MapMarkerTreeItem &_item, bool _includeFirstRankDisabled /*= false*/)
{
    bool found = false;
    auto searchInActive = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            if(*_treeItem == _item)
            {
                found = true;
                return VisitorReturn::VisitorBreak;
            }
        }
        else
        {
            if(_includeFirstRankDisabled && *_treeItem == _item)
            {
                found = true;
                return VisitorReturn::VisitorBreak;
            }
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(searchInActive);

    //qDebug() << Q_FUNC_INFO << "Id: "<< _item.markerData().markerId <<"is in active hierarchy = "<< found;
    return found;
}

// if(_includeFirstRankDisabled) Include first rank disabled leaf.
// It means that a disabled item can match only if his parent is active.
int MapMarkerTreeModel::getLinearIndexFromRoot(MapMarkerTreeItem& _item, bool _includeFirstRankDisabled /*= false*/)
{
    int ind = 0;
    bool found = false;
    auto getIndex = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            if(*_treeItem == _item)
            {
                found = true;
                return VisitorReturn::VisitorBreak;
            }
            ++ind;
        }
        else
        {
            if(_includeFirstRankDisabled && *_treeItem == _item)
            {
                found = true;
                return VisitorReturn::VisitorBreak;
            }
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(getIndex);

    if(!found)
    {
        ind = -1;
    }

//    qDebug() << Q_FUNC_INFO << "Id: "<< _item.markerData().markerId <<"LinearIndex = "<< ind;
    return ind;
}

int MapMarkerTreeModel::getNbVisibleChild(MapMarkerTreeItem &_item)
{
    int nb = 0;
    auto getLastVisibleChildIndex = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            ++nb;
        }
        else
        {
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    _item.visitChilds(getLastVisibleChildIndex);

//    qDebug() << Q_FUNC_INFO << "Id: "<< _item.markerData().markerId << "Nb visible Childs: "<< nb;
    return nb;
}

QModelIndex MapMarkerTreeModel::getIndexFromMarkerId(int _markerId)
{
    QModelIndex id;

    auto getModelIndex = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().markerId == _markerId)
        {
            id = index(_treeItem);
            return VisitorReturn::VisitorBreak;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(getModelIndex);

    return id;
}

bool MapMarkerTreeModel::removeItem(MapMarkerTreeItem *_treeItem)
{
    bool done = false;

    QModelIndex id = index(_treeItem);
    beginRemoveRows(id.parent(), id.row(), id.row());
    if(_treeItem->inActiveHierarchy())
    {
        int first = _treeItem->linearIndexActiveHierarchy();
        int last = first;
        if(_treeItem->childCount() > 0)
        {
            int nb = getNbVisibleChild(*_treeItem);
            last = first + nb;
        }
        m_listModel->triggerBeginRemoveRows(first, last);
        qDebug() << Q_FUNC_INFO << "triggerBeginRemoveRows(" << first << ", " << last << ")";
    }

    done = _treeItem->parent()->removeChildren(id.row(), 1);

    if(_treeItem->inActiveHierarchy())
    {
        m_listModel->triggerEndRemoveRows();
    }

    endRemoveRows();

    updateTreeItemIndexInfo();

    return done;
}

MapMarkerTreeItem* MapMarkerTreeModel::getFirstSelectedMarkerId()
{
    MapMarkerTreeItem* firstSelectedMarkerId = m_root;

    auto getFirstSelected = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().selected)
        {
            firstSelectedMarkerId = _treeItem;
            return VisitorReturn::VisitorBreak;
        }

        return VisitorReturn::VisitorContinue;
    };
    visit(getFirstSelected);

    return firstSelectedMarkerId;
}

void MapMarkerTreeModel::updateTreeItemIndexInfo()
{
    int id = 0;
    int idActiveHierarchy = 0;

    auto updateInfo = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        _treeItem->setLinearIndex(id);
        ++id;

        bool inActiveHerarchy{ false };
        if(const MapMarkerTreeItem* parent = _treeItem->parent())
        {
            inActiveHerarchy = parent->inActiveHierarchy() && _treeItem->markerData().active;
        }

        _treeItem->setInActiveHierarchy(inActiveHerarchy);
        if(inActiveHerarchy)
        {
            _treeItem->setLinearIndexActiveHierarchy(idActiveHierarchy);
            ++idActiveHierarchy;
        }
        else
        {
            _treeItem->setLinearIndexActiveHierarchy(-1);
        }

        //qDebug() << Q_FUNC_INFO << "Id: "<< _treeItem->markerData().markerId << "linearIndex: "<< _treeItem->linearIndex() << ", inActiveHierarchy: " << _treeItem->inActiveHierarchy() << ", linearIndexInActiveHierarchy: " << _treeItem->linearIndexActiveHierarchy();
        return VisitorReturn::VisitorContinue;
    };
    visit(updateInfo);

    m_highestLinearIndexInActiveHierarchy = idActiveHierarchy - 1;
}

void MapMarkerTreeModel::computeBounds(QPair<double, double>& _latBounds, QPair<double, double>& _lonBounds) const
{
    _latBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
    _lonBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};

    auto gatherTreeBounds = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {

            const QGeoCoordinate& coord = _treeItem->markerData().markerCoordinate;

            _latBounds.first = qMin(_latBounds.first, coord.latitude());
            _latBounds.second = qMax(_latBounds.second, coord.latitude());

            _lonBounds.first = qMin(_lonBounds.first, coord.longitude());
            _lonBounds.second = qMax(_lonBounds.second, coord.longitude());

            return VisitorReturn::VisitorContinue;
        }

        return VisitorReturn::VisitorIgnoreChilds;
    };
    visit(gatherTreeBounds);
}

QDataStream& operator<<(QDataStream& _ds, const MapMarkerTreeModel& _treeModel)
{
    _ds << *(_treeModel.getRoot())
        << _treeModel.getHighestLinearIndexInActiveHierarchy();

    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, MapMarkerTreeModel& _treeModel)
{
    _treeModel.triggerBeginResetModel();

    _ds >> *(_treeModel.getRoot());

    int highestLinearIndexInActiveHierarchy;
    _ds >> highestLinearIndexInActiveHierarchy;
    _treeModel.setHighestLinearIndexInActiveHierarchy(highestLinearIndexInActiveHierarchy);

    _treeModel.triggerEndResetModel();

    return _ds;
}
