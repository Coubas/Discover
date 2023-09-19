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
//    MapMarkerTreeModel(const QStringList& _headers, QObject* _parent = nullptr);
    ~MapMarkerTreeModel();

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


    void visit(std::function<VisitorReturn(MapMarkerTreeItem*)> _function) const;

    MapMarkerTreeListModel* getListModel() {return m_listModel;}
    const MapMarkerTreeListModel* getListModel() const {return m_listModel;}
    const QVariantList getWaypoints() const;

    bool removeMaker(int _markerId);
    bool setMarkerSelected(int _markerId, bool _selected = true);
    bool setMarkerCoordinate(int _markerId, const QGeoCoordinate& _coord);
//    void removeSelectedMarkers();

private:
    MapMarkerTreeItem* getItem(const QModelIndex& _index) const;
    bool isInActiveHierarchy(MapMarkerTreeItem& _item, bool _includeFirstRankDisabled = false);
    int getLinearIndexFromRoot(MapMarkerTreeItem& _item, bool _includeFirstRankDisabled = false);
    int getNbVisibleChild(MapMarkerTreeItem& _item);

    void updateTreeItemIndexInfo();

    MapMarkerTreeItem* m_root{nullptr};
    MapMarkerTreeListModel* m_listModel{nullptr};

};

#endif // MAPMARKERTREEMODEL_H
