//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef MAPMARKERMODEL_H
#define MAPMARKERMODEL_H

#include <QAbstractItemModel>

class MapMarkerList;

class MapMarkerModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerList *list READ list WRITE setList)

public:
    explicit MapMarkerModel(QObject *parent = nullptr);

    enum MarkerField
    {
        MarkerId = Qt::UserRole,
        MarkerIsSelected,
        MarkerType,
        MarkerCoordinate
    };
    static const QList<int> ms_allRoles;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool insertRows(int _row, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool removeRows(int _row, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool moveRows(const QModelIndex& _sourceParent, int _sourceRow, int _count, const QModelIndex& _destinationParent, int _destinationChild) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    MapMarkerList* list() const;
    void setList(MapMarkerList* _list);

private:
    MapMarkerList* m_list;
};

#endif // MAPMARKERMODEL_H
