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
    bool loop{false};
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
    explicit MapMarkerTreeItem(MapMarkerTreeItem* _parent = nullptr, const MapMarkerTreeItem *_source = nullptr);
    ~MapMarkerTreeItem();

    enum MarkerField
    {
        MarkerId = Qt::UserRole,
        MarkerType,
        MarkerCoordinate,
        MarkerIsLoop,
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
    const MapMarkerTreeItem* parent() const;
    MapMarkerTreeItem* child(int _row);
    const MapMarkerTreeItem* child(int _row) const;
    int childCount() const;
    int childNumber() const;
    int columnCount() const;
    QVariant data(int _role = Qt::DisplayRole) const;
    bool setData(const QVariant& _value, int _role = Qt::EditRole);
    bool appendChild(const MapMarkerTreeItemData& _data);
    bool appendChild(const MapMarkerTreeItem* _source);
    bool insertChild(int _position, const MapMarkerTreeItemData& _data);
    bool insertChild(int _position, const MapMarkerTreeItem* _source);
    bool insertChildren(int _position, int _count);
    bool removeChildren(int _position, int _count);
//    bool insertColumns(int _position, int _count);
//    bool removeColumns(int _position, int _count);

    const MapMarkerTreeItemData& markerData() const;
    MapMarkerTreeItemData& markerData();
    void setMarkerData(const MapMarkerTreeItemData &newMarkerData);
    bool inActiveHierarchy() const;
    void setInActiveHierarchy(bool newInActiveHierarchy);
    int linearIndex() const;
    void setLinearIndex(int newLinearIndex);
    int linearIndexActiveHierarchy() const;
    void setLinearIndexActiveHierarchy(int newLinearIndexActiveHierarchy);

    VisitorReturn visit(std::function<VisitorReturn(MapMarkerTreeItem*)> _function, std::function<VisitorReturn (MapMarkerTreeItem *)> _postChildFunction = {});
    VisitorReturn visitChilds(std::function<VisitorReturn(MapMarkerTreeItem*)> _function);
    int count() const;

    bool hasVisibleChild();

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
    bool m_inActiveHierarchy{ false };
    int m_linearIndex{ -1 };
    int m_linearIndexActiveHierarchy{ -1 };


    static const QList<int> ms_columns;
};

QDataStream &operator<<(QDataStream& _ds, const MapMarkerTreeItemData& _data);
QDataStream &operator>>(QDataStream& _ds, MapMarkerTreeItemData& _data);

QDataStream &operator<<(QDataStream& _ds, const MapMarkerTreeItem& _item);
QDataStream &operator>>(QDataStream& _ds, MapMarkerTreeItem& _item);

#endif // MAPMARKERTREEITEM_H
