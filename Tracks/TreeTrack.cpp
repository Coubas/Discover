#include "Tracks/TreeTrack.h"

#include <MapMarkerItem.h>
#include <MapMarkerTreeItem.h>

TreeTrack::TreeTrack(QObject *parent)
    : QObject{parent}
    , m_name{""}
    , m_tree()
{
    m_author = qgetenv("USER");
    if (m_author.isEmpty())
    {
        m_author = qgetenv("USERNAME");
    }
}

bool TreeTrack::addPoint(const QGeoCoordinate& _coord, const QString& _type /*= "pin"*/, int _parentMarkerId /*= -1*/)
{
    return m_tree.addNewMarker(_coord, _type, _parentMarkerId);
}

bool TreeTrack::addPointAfterFirstSelected(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return m_tree.addNewMarkerAfterFirstSelected(_coord, _type);
}

bool TreeTrack::addPointAsChildOfFirstSelected(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return m_tree.addNewMarkerAsChildOfFirstSelected(_coord, _type);
}

bool TreeTrack::removePoint(int _markerId)
{
    return m_tree.removeMaker(_markerId);
}

bool TreeTrack::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    return m_tree.setMarkerSelected(_markerId, _selected);
}

bool TreeTrack::setPointCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    return m_tree.setMarkerCoordinate(_markerId, _coord);
}

void TreeTrack::removeSelectedPoints()
{
    m_tree.removeSelectedMarkers();
}

const QString& TreeTrack::name() const
{
    return m_name;
}

void TreeTrack::setName(const QString& _newName)
{
    m_name = _newName;
}

QString TreeTrack::author() const
{
    return m_author;
}

void TreeTrack::setAuthor(const QString& _newAuthor)
{
    m_author = _newAuthor;
}

//void TreeTrack::computeBounds(QPair<double, double> &_latBounds, QPair<double, double> &_lonBounds) const
//{
//    _latBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
//    _lonBounds = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};

//    for(const MapMarkerItem& marker : m_points.items())
//    {
//        const QGeoCoordinate& coord = marker.markerCoordinate();

//        _latBounds.first = qMin(_latBounds.first, coord.latitude());
//        _latBounds.second = qMax(_latBounds.second, coord.latitude());

//        _lonBounds.first = qMin(_lonBounds.first, coord.longitude());
//        _lonBounds.second = qMax(_lonBounds.second, coord.longitude());
//    }
//}

QDataStream& operator<<(QDataStream& _ds, const TreeTrack& _trk)
{
    _ds << _trk.name()
        << _trk.author()
        << *(_trk.getTreeModel());

    return _ds;
}

QDataStream& operator>>(QDataStream& _ds, TreeTrack& _trk)
{
    QString input;
    _ds >> input;
    _trk.setName(input);

    _ds >> input;
    _trk.setAuthor(input);

    _ds >> *(_trk.getTreeModel());

    return _ds;
}

