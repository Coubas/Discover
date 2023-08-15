#ifndef MAPMARKERLIST_H
#define MAPMARKERLIST_H

#include <QObject>
#include <QVector>

#include <MapMarkerItem.h>

class MapMarkerList : public QObject
{
    Q_OBJECT
public:
    explicit MapMarkerList(QObject *parent = nullptr);

    const QVector<MapMarkerItem>& items() const;

    bool setItemAt(int _index, const MapMarkerItem& _item);
    qsizetype size() const {return m_markers.size();}

    void removeMaker(int _markerId);
    void setMarkerSelected(int _markerId, bool _selected = true);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int _index);
    void postItemRemoved();

    void dataChanged(int _first, int _last, const QList<int>& _roles = QList<int>());

public slots:
    void appendMarker();
    void appendMarker(MapMarkerItem _item);
    void removeItem(int _index);

private:
    const MapMarkerItem* getMarker(int _markerId) const;
    MapMarkerItem* getMarker(int _markerId);
    int getMarkerIndex(int _markerId) const;
    void updateMarkerIdsOnRemove(int _removedId);

    QVector<MapMarkerItem> m_markers;

};

#endif // MAPMARKERLIST_H
