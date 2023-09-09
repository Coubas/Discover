#ifndef MAPMARKERTREEITEM_H
#define MAPMARKERTREEITEM_H

#include <QGeoCoordinate>
#include <QVariant>

#include <VisitorReturnEnum.h>

struct MapMarkerTreeItemData
{
    int markerId{-1};
    QString markerType{"invalidType"};
    QGeoCoordinate markerCoordinate{0.0, 0.0};
    bool selected{false};
    bool active{true};

    bool operator==(const MapMarkerTreeItemData& _other) const
    {
        return markerId == _other.markerId && markerCoordinate == _other.markerCoordinate;
    }
};

class MapMarkerTreeItem
{
public:
    explicit MapMarkerTreeItem(MapMarkerTreeItem* parentItem = nullptr);
    ~MapMarkerTreeItem();

    enum MarkerField
    {
        MarkerId = Qt::UserRole,
        MarkerType,
        MarkerCoordinate,
        MarkerIsSelected,
        MarkerIsActive,
        MarkerCoordinateLatitude,
        MarkerCoordinateLongitude,
        MarkerRoleCount
    };
    int rolesCount() const { return MarkerRoleCount - MarkerId; }
    int getColumnIdFromRole(int _role) const;
    int getRoleIdFromColumn(int _column) const;

    MapMarkerTreeItem* parent();
    MapMarkerTreeItem* child(int _row);
    int childCount() const;
    int childNumber() const;
    int columnCount() const;
    QVariant data(int _role = Qt::DisplayRole) const;
    bool setData(const QVariant& _value, int _role = Qt::EditRole);
    bool appendChild(const MapMarkerTreeItemData& _data);
    bool insertChildren(int _position, int _count, int _columnsCount);
    bool removeChildren(int _position, int _count);
//    bool insertColumns(int _position, int _count);
//    bool removeColumns(int _position, int _count);

    MapMarkerTreeItemData markerData() const;
    void setMarkerData(const MapMarkerTreeItemData &newMarkerData);

    VisitorReturn visit(std::function<VisitorReturn(MapMarkerTreeItem*)> _function);
    VisitorReturn visitChilds(std::function<VisitorReturn(MapMarkerTreeItem*)> _function);
    int count() const;

    bool operator==(const MapMarkerTreeItem& _other) const
    {
        return m_markerData == _other.m_markerData;
    }

public slots:
    void appendMarker();
    void removeItem(int _index, bool _updateIds = true);
    void moveItem(int _index, int _destIndex);

private:
    MapMarkerTreeItem* m_parentItem;
    QList<MapMarkerTreeItem*> m_childItems;

    MapMarkerTreeItemData m_markerData{};

    static const QList<int> ms_columns;
};

#endif // MAPMARKERTREEITEM_H
