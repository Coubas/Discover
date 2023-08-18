#ifndef TRACK_H
#define TRACK_H

#include <QObject>

#include <MapMarkerList.h>

class Track : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerList *points READ getPointList CONSTANT)

public:
    explicit Track(QObject *parent = nullptr);

    MapMarkerList* getPointList() {return &m_points;}
    qsizetype size() const {return m_points.size();}

    void addPoint(const QGeoCoordinate& _coord, const QString& _type = "pin");
    void removePoint(int _markerId);
    void setPointSelected(int _markerId, bool _selected = true);
    void removeSelectedPoints();
    void changePointIndex(int _oldIndex, int _newIndex);

signals:

private:
    MapMarkerList m_points;
};

#endif // TRACK_H
