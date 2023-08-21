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

    void addPoint(const QGeoCoordinate& _coord, int _insertIndex = -1, const QString& _type = "pin");
    void removePoint(int _markerId);
    void setPointSelected(int _markerId, bool _selected = true);
    void setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPoints();
    void changePointIndex(int _oldIndex, int _newIndex);

    const QString& name() const;
    void setName(const QString& _newName);

signals:

private:
    QString m_name;
    MapMarkerList m_points;
};

#endif // TRACK_H
