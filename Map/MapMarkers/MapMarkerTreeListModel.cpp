//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#include "MapMarkerTreeListModel.h"

#include <MapMarkerTreeItem.h>
#include <MapMarkerTreeModel.h>

MapMarkerTreeListModel::MapMarkerTreeListModel(MapMarkerTreeItem* _root, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root(_root)
{}

MapMarkerTreeListModel::~MapMarkerTreeListModel()
{}

QModelIndex MapMarkerTreeListModel::index(int _row, int _column, const QModelIndex& _parent) const
{
    if(m_root == nullptr)
    {
        QModelIndex();
    }

    MapMarkerTreeItem* item;
    int curRow = 0;
    auto getItem = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            if(curRow == _row)
            {
                item = _treeItem;
                return VisitorReturn::VisitorBreak;
            }
        }
        else
        {
            return VisitorReturn::VisitorIgnoreChilds;
        }

        ++curRow;
        return VisitorReturn::VisitorContinue;
    };

    m_root->visit(getItem);

    if(item != nullptr)
    {
        return createIndex(_row, _column, item);
    }

    return QModelIndex();
}

QModelIndex MapMarkerTreeListModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    return {};
}

int MapMarkerTreeListModel::rowCount(const QModelIndex &parent) const
{

    if(m_root == nullptr)
    {
        return 0;
    }

    int count = 0;
    auto countActive = [&](MapMarkerTreeItem* _treeItem) -> VisitorReturn
    {
        if(_treeItem->markerData().active)
        {
            ++count;
        }
        else
        {
            return VisitorReturn::VisitorIgnoreChilds;
        }

        return VisitorReturn::VisitorContinue;
    };
    m_root->visit(countActive);

    return count;
}

int MapMarkerTreeListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

bool MapMarkerTreeListModel::insertRows(int _row, int _count, const QModelIndex &_parent)
{
    return false;
}

bool MapMarkerTreeListModel::removeRows(int _row, int _count, const QModelIndex &_parent)
{
    return false;
}

bool MapMarkerTreeListModel::moveRows(const QModelIndex &_sourceParent, int _sourceRow, int _count, const QModelIndex &_destinationParent, int _destinationChild)
{
    return false;
}

Qt::ItemFlags MapMarkerTreeListModel::flags(const QModelIndex& _index) const
{
    if (!_index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(_index);
}

QHash<int, QByteArray> MapMarkerTreeListModel::roleNames() const
{
    QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
    names[MapMarkerTreeItem::MarkerId] = "markerId";
    names[MapMarkerTreeItem::MarkerType] = "markerType";
    names[MapMarkerTreeItem::MarkerCoordinate] = "markerCoordinate";
    names[MapMarkerTreeItem::MarkerName] = "markerName";
    names[MapMarkerTreeItem::MarkerIsLoop] = "markerIsLoop";
    names[MapMarkerTreeItem::MarkerIsSelected] = "markerIsSelected";
    names[MapMarkerTreeItem::MarkerIsActive] = "markerIsActive";
    names[MapMarkerTreeItem::MarkerCoordinateLatitude] = "markerCoordinateLatitude";
    names[MapMarkerTreeItem::MarkerCoordinateLongitude] = "markerCoordinateLongitude";
    names[MapMarkerTreeItem::MarkerLinearIndex] = "markerLinearIndex";
    names[MapMarkerTreeItem::MarkerLinearIndexInActiveHierarchy] = "markerLinearIndexInActiveHierarchy";
    return names;
}

QVariant MapMarkerTreeListModel::data(const QModelIndex& _index, int _role) const
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

bool MapMarkerTreeListModel::setData(const QModelIndex& _index, const QVariant& _value, int _role/* = Qt::EditRole*/)
{
    //    if (_role != Qt::EditRole)
    //    {
    //        return false;
    //    }

    if (!_index.isValid())
    {
        return false;
    }

    if(MapMarkerTreeItem* item = getItem(_index))
    {
        //        if(item->setData(_index.column(), _value))
        if(item->setData(_value, _role))
        {
            emit dataChanged(_index, _index, {Qt::DisplayRole, Qt::EditRole});
            return true;
        }
    }

    return false;
}

void MapMarkerTreeListModel::triggerDataChanged(int _first, int _last, int _role, const QVariant& _value /*= QVariant()*/)
{
//    qDebug() << Q_FUNC_INFO << "first: "<< _first<< " last: "<< _last << " role: "<<roleNames()[_role];

    if(_role == MapMarkerTreeItem::MarkerIsActive)
    {
        if(_value.toBool())
        {
            beginInsertRows(QModelIndex(), _first, _last);
            endInsertRows();
        }
        else
        {
            beginRemoveRows(QModelIndex(), _first, _last);
            endRemoveRows();
        }
    }
    else
    {
        QModelIndex topLeft{index(_first, 0)};
        QModelIndex bottomRight{index(_last, 0)};
        emit dataChanged(topLeft, bottomRight, {_role});
    }
}

void MapMarkerTreeListModel::triggerBeginRemoveRows(int _first, int _last)
{
    beginRemoveRows(QModelIndex(), _first, _last);
}

void MapMarkerTreeListModel::triggerEndRemoveRows()
{
    endRemoveRows();
}

void MapMarkerTreeListModel::triggerBeginInsertRows(int _first, int _last)
{
    beginInsertRows(QModelIndex(), _first, _last);
}

void MapMarkerTreeListModel::triggerEndInsertRows()
{
    endInsertRows();
}

void MapMarkerTreeListModel::triggerBeginResetModel()
{
    beginResetModel();
}

void MapMarkerTreeListModel::triggerEndResetModel()
{
    endResetModel();
}

MapMarkerTreeItem* MapMarkerTreeListModel::getItem(const QModelIndex& _index) const
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
