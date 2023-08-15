#include "MapMarkerModel.h"

#include <QGeoCoordinate>

#include <MapMarkerList.h>

MapMarkerModel::MapMarkerModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_list(nullptr)
{
}

QModelIndex MapMarkerModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return createIndex(row, column, nullptr);
}

QModelIndex MapMarkerModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    return {};
}

int MapMarkerModel::rowCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 1; // Root item

    if(parent.isValid() || m_list == nullptr)
    {
        return 0;
    }

    return m_list->items().size();
}

int MapMarkerModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant MapMarkerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_list == nullptr)
        return QVariant();

    const MapMarkerItem item = m_list->items().at(index.row());
    switch (role) {
    case MarkerId:
        return QVariant(item.markerId());
    case MarkerIsSelected:
        return QVariant(item.selected());
    case MarkerType:
        return QVariant(item.markerType());
    case MarkerCoordinate:
        return QVariant::fromValue<QGeoCoordinate>(item.markerCoordinate());
    }

    return QVariant();
}

bool MapMarkerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_list == nullptr)
    {
        return false;
    }

    MapMarkerItem item = m_list->items().at(index.row());
    switch (role) {
    case MarkerId:
        item.setMarkerId(value.toInt());
        break;
    case MarkerIsSelected:
        item.setSelected(value.toBool());
        break;
    case MarkerType:
        item.setMarkerType(value.toString());
        break;
    case MarkerCoordinate:
        item.setMarkerCoordinate(value.value<QGeoCoordinate>());
        break;
    }

    if (m_list->setItemAt(index.row(), item))
    {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags MapMarkerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> MapMarkerModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[MarkerId] = "markerId";
    names[MarkerIsSelected] = "markerIsSelected";
    names[MarkerType] = "markerType";
    names[MarkerCoordinate] = "markerCoordinate";
    return names;
}

MapMarkerList *MapMarkerModel::list() const
{
    return m_list;
}

void MapMarkerModel::setList(MapMarkerList *_list)
{
    beginResetModel();

    if(m_list)
    {
        m_list->disconnect(this);
    }

    m_list = _list;

    if(m_list)
    {
        connect(m_list, &MapMarkerList::preItemAppended, this, [=](){
            const int i = m_list->items().size();
            beginInsertRows(QModelIndex(), i, i);
        });

        connect(m_list, &MapMarkerList::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(m_list, &MapMarkerList::preItemRemoved, this, [=](int _i){
            beginRemoveRows(QModelIndex(), _i, _i);
        });

        connect(m_list, &MapMarkerList::postItemRemoved, this, [=](){
            endRemoveRows();
        });

        connect(m_list, &MapMarkerList::dataChanged, this, [=](int _first, int _last, const QList<int>& _roles = QList<int>()){
            QModelIndex topLeft{index(_first, 0)};
            QModelIndex bottomRight{index(_last, 0)};
            emit dataChanged(topLeft, bottomRight, _roles);
        });
    }

    endResetModel();
}
