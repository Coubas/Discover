#ifndef MAPMARKERLIST_H
#define MAPMARKERLIST_H

#include <QObject>

#include <MapMarkerItem.h>
#include <QVariant>

class MapMarkerList : public QObject
{
    Q_OBJECT
public:
    explicit MapMarkerList(QObject *parent = nullptr);

    const QList<MapMarkerItem>& items() const { return m_markers; }

    bool setItemAt(int _index, const MapMarkerItem& _item);
    qsizetype size() const {return m_markers.size();}

    void removeMaker(int _markerId);
    void setMarkerSelected(int _markerId, bool _selected = true);
    void setMarkerCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedMarkers();
    void changeMarkerIndex(int _oldMarkerId, int _newMarkerId);
    const QVariantList& getWaypoints() const { return m_waypoints; }

    void clear();

signals:
    void preItemAppended(int _index);
    void postItemAppended();

    void preItemRemoved(int _first, int _last);
    void postItemRemoved();

    void preItemMoved();
    void postItemMoved(int _index, int _indexDest);

    void dataChanged(int _first, int _last, const QList<int>& _roles = QList<int>());

public slots:
    void appendMarker();
    void appendMarker(MapMarkerItem _item, int _insertIndex = -1);
    void removeItem(int _index, bool _updateIds = true);
    void moveItem(int _index, int _destIndex);

private:
    const MapMarkerItem* getMarker(int _markerId) const;
    MapMarkerItem* getMarker(int _markerId);
    int getMarkerIndex(int _markerId) const;
    void updateMarkerIds(int _firstModifiedId = 0);
    void onMarkerListModified(int (&_modifBounds)[2], std::initializer_list<int> _modifiedRoles = {});

    QList<MapMarkerItem> m_markers;
    QVariantList m_waypoints; // simple reflexion of the marker list containing only the coordinates.
};

QDataStream &operator<<(QDataStream& _ds, const MapMarkerList& _mrkList);
QDataStream &operator>>(QDataStream& _ds, MapMarkerList& _mrkList);

#endif // MAPMARKERLIST_H
