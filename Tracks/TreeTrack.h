#ifndef TREETRACK_H
#define TREETRACK_H

#include <QObject>

#include <MapMarkerTreeModel.h>

class TreeTrack: public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapMarkerTreeModel* treeModel READ getTreeModel CONSTANT)

public:
    explicit TreeTrack(QObject *parent = nullptr);

    MapMarkerTreeModel* getTreeModel() {return &m_tree;}
    const MapMarkerTreeModel* getTreeModel() const {return &m_tree;}

//    qsizetype size() const {return m_points.size();}

    bool addPoint(const QGeoCoordinate& _coord, const QString& _type = "pin", int _parentMarkerId = -1);
    bool addPointAfterFirstSelected(const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool addPointAsChildOfFirstSelected(const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool removePoint(int _markerId);
    bool setPointSelected(int _markerId, bool _selected = true);
    bool setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPoints();
//    const QVariantList& getWaypoints() const { return m_points.getWaypoints(); }

    const QString& name() const;
    void setName(const QString& _newName);
    QString author() const;
    void setAuthor(const QString& _newAuthor);

    void clear()
    {
        m_name = "";
        m_author = "";
    }

    void computeBounds(QPair<double, double>& _latBounds, QPair<double, double>& _lonBounds) const;

private:
    QString m_name;
    QString m_author;

    MapMarkerTreeModel m_tree;
};

QDataStream &operator<<(QDataStream& _ds, const TreeTrack& _trk);
QDataStream &operator>>(QDataStream& _ds, TreeTrack& _trk);

#endif // TREETRACK_H
