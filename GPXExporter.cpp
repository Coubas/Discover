#include "GPXExporter.h"

#include <QDateTime>

#include <TreeTrack.h>
#include <MapMarkerTreeItem.h>

GPXExporter::GPXExporter(TreeTrack& _track)
    : m_track(_track)
{
    m_xml.setAutoFormatting(true);
}

bool GPXExporter::writeFile(QIODevice* _output)
{
    m_xml.setDevice(_output);

    m_xml.writeStartDocument();

    m_xml.writeStartElement(QStringLiteral("gpx"));
    {
        m_xml.writeAttribute("version", "1.0");
        m_xml.writeAttribute("creator", "Discover 1.0");

        m_xml.writeStartElement("metadata");
        {
            m_xml.writeTextElement("name", m_track.name());
            m_xml.writeTextElement("author", m_track.author());
            QDateTime time = QDateTime::currentDateTimeUtc();
            m_xml.writeTextElement("time", time.toString("yyyy-MM-ddThh:mm::ssZ"));
            m_xml.writeEmptyElement("bounds");
            {
                QPair<double, double> latBounds;
                QPair<double, double> lonBounds;
                m_track.computeBounds(latBounds, lonBounds);

                m_xml.writeAttribute("minlat", QString::number(latBounds.first, 'f'));
                m_xml.writeAttribute("maxlat", QString::number(latBounds.second, 'f'));
                m_xml.writeAttribute("minlon", QString::number(lonBounds.first, 'f'));
                m_xml.writeAttribute("maxlon", QString::number(lonBounds.second, 'f'));
            }
        }
        m_xml.writeEndElement();

        writeTrack();
    }
    m_xml.writeEndElement();

    m_xml.writeEndDocument();
    return true;
}

void GPXExporter::writeTrack()
{
    m_xml.writeStartElement("trk");
    {
        QGeoCoordinate markerCoordinate;
        for(QVariant waypoint : m_track.getTreeModel()->getWaypoints())
        {
            markerCoordinate = waypoint.value<QGeoCoordinate>();
            m_xml.writeStartElement("trkpt");
            {
                m_xml.writeAttribute("lat", QString::number(markerCoordinate.latitude(), 'f'));
                m_xml.writeAttribute("lon", QString::number(markerCoordinate.longitude(), 'f'));
            }
            m_xml.writeEndElement();
        }
    }
    m_xml.writeEndElement();
}
