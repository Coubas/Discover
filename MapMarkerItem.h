#ifndef MAPMARKERITEM_H
#define MAPMARKERITEM_H

#include <QGeoCoordinate>

class MapMarkerItem
{
public:
    MapMarkerItem();
    MapMarkerItem(int _id, const QString& _type, const QGeoCoordinate& _coord, bool _selected = false);

    bool operator==(const MapMarkerItem& _other) const { return m_markerId == _other.m_markerId; }
    bool operator!=(const MapMarkerItem& _other) const { return !operator==(_other); }

    int markerId() const;
    void setMarkerId(int newMarkerId);

    QString markerType() const;
    void setMarkerType(const QString &newMarkerType);

    QGeoCoordinate markerCoordinate() const;
    void setMarkerCoordinate(const QGeoCoordinate &newMarkerCoordinate);

    bool selected() const;
    void setSelected(bool newSelected);

private:
    int m_markerId{-1};
    bool m_selected{false};
    QString m_markerType{"invalidType"};
    QGeoCoordinate m_markerCoordinate{0.0, 0.0};
};

#endif // MAPMARKERITEM_H
