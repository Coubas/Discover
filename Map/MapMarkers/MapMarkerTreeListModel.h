#ifndef MAPMARKERTREELISTMODEL_H
#define MAPMARKERTREELISTMODEL_H

#include <QAbstractItemModel>

class MapMarkerTreeItem;
class MapMarkerTreeModel;

class MapMarkerTreeListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MapMarkerTreeListModel(MapMarkerTreeItem* _root, QObject *parent = nullptr);
    ~MapMarkerTreeListModel();

    void setRoot(MapMarkerTreeItem* _root) { m_root = _root; }

    QModelIndex index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool insertRows(int _row, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool removeRows(int _row, int _count, const QModelIndex& _parent = QModelIndex()) override;
    bool moveRows(const QModelIndex& _sourceParent, int _sourceRow, int _count, const QModelIndex& _destinationParent, int _destinationChild) override;

    Qt::ItemFlags flags(const QModelIndex& _index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& _index, int _role) const override;
    bool setData(const QModelIndex& _index, const QVariant& _value, int _role = Qt::EditRole) override;

    void triggerDataChanged(int _first, int _last, int _role, const QVariant& _value = QVariant());
    void triggerBeginRemoveRows(int _first, int _last);
    void triggerEndRemoveRows();
    void triggerBeginInsertRows(int _first, int _last);
    void triggerEndInsertRows();
    void triggerBeginResetModel();
    void triggerEndResetModel();

private:
    MapMarkerTreeItem* getItem(const QModelIndex& _index) const;

    MapMarkerTreeItem* m_root{nullptr};
};

#endif // MAPMARKERTREELISTMODEL_H
