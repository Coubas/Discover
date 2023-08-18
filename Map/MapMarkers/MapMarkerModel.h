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
