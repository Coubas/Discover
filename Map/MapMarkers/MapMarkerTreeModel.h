#ifndef MAPMARKERTREEMODEL_H
#define MAPMARKERTREEMODEL_H

#include <QAbstractItemModel>

#include <VisitorReturnEnum.h>
#include <MapMarkerList.h>

class MapMarkerTreeItem;
class MapMarkerTreeListModel;

class MapMarkerTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerTreeListModel* listModel READ getListModel CONSTANT)

public:
    explicit MapMarkerTreeModel(QObject *parent = nullptr);
    ~MapMarkerTreeModel();

    int size() const;
    void clear();
    MapMarkerTreeItem* getRoot() { return m_root; }
    const MapMarkerTreeItem* getRoot() const { return m_root; }
    int getHighestLinearIndexInActiveHierarchy() const{ return m_highestLinearIndexInActiveHierarchy; }
    void setHighestLinearIndexInActiveHierarchy(int _value) { m_highestLinearIndexInActiveHierarchy = _value; }
    int getIdCounter() const { return m_idCounter; }
    void setIdCounter(int _count) { m_idCounter = _count; }

    QModelIndex index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const override;
    QModelIndex index(const MapMarkerTreeItem* _item) const;
    QModelIndex parent(const QModelIndex& _index) const override;

    int rowCount(const QModelIndex& _parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& _parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex& _index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& _index, int _role) const override;
    bool setData(const QModelIndex& _index, const QVariant& _value, int _role = Qt::EditRole) override;
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role = Qt::DisplayRole) const override;
    bool setHeaderData(int _section, Qt::Orientation _orientation, const QVariant& _value, int _role = Qt::EditRole) override;

//    bool insertColumns(int _position, int _count, const QModelIndex& _parent = QModelIndex()) override;
//    bool removeColumns(int _position, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool insertRows(int _position, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool removeRows(int _position, int _count, const QModelIndex& _parent = QModelIndex()) override;

    void visit(std::function<VisitorReturn(MapMarkerTreeItem*)> _function, std::function<VisitorReturn (MapMarkerTreeItem *)> _postChildFunction = {}) const;

    MapMarkerTreeListModel* getListModel() {return m_listModel;}
    const MapMarkerTreeListModel* getListModel() const {return m_listModel;}
    const QVariantList getWaypoints();

    bool removeMaker(int _markerId);
    bool setMarkerSelected(int _markerId, bool _selected = true);
    bool setMarkerCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedMarkers();
    bool addNewMarker(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin", int _parentMarkerId = -1, int _index = -1);
    bool addNewMarkerAfterFirstSelected(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool addNewMarkerAsChildOfFirstSelected(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");

    void updateTreeItemIndexInfo();
    void computeBounds(QPair<double, double>& _latBounds, QPair<double, double>& _lonBounds) const;

    void triggerBeginResetModel();
    void triggerEndResetModel();

public slots:
    bool isValidMove(int _fromMarkerId, int _toMarkerId, bool addAfter = false);
    bool isValidNewChild(int _fromMarkerId, int _toMarkerId);
    void moveItem(int _fromMarkerId, int _toMarkerId, bool addAfter = false);
    void addItemAsChild(int _fromMarkerId, int _toMarkerId);

private:
    MapMarkerTreeItem* getItem(const QModelIndex& _index) const;
    bool isInActiveHierarchy(MapMarkerTreeItem& _item, bool _includeFirstRankDisabled = false);
    int getLinearIndexFromRoot(MapMarkerTreeItem& _item, bool _includeFirstRankDisabled = false);
    int getNbVisibleChild(MapMarkerTreeItem& _item);
    QModelIndex getIndexFromMarkerId(int _markerId);
    bool removeItem(MapMarkerTreeItem* _treeItem);
    MapMarkerTreeItem* getFirstSelectedMarkerId();

    MapMarkerTreeItem* m_root{nullptr};
    MapMarkerTreeListModel* m_listModel{nullptr};

    int m_idCounter{0};
    int m_highestLinearIndexInActiveHierarchy{-1};
    bool m_waypointsDirty{true};
    QVariantList m_waypoints{};
};

QDataStream &operator<<(QDataStream& _ds, const MapMarkerTreeModel& _treeModel);
QDataStream &operator>>(QDataStream& _ds, MapMarkerTreeModel& _treeModel);

#endif // MAPMARKERTREEMODEL_H
