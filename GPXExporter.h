#ifndef GPXEXPORTER_H
#define GPXEXPORTER_H

#include <QXmlStreamWriter>

class TreeTrack;

class GPXExporter
{
public:
    explicit GPXExporter(TreeTrack& _track);

    bool writeFile(QIODevice* _output);

private:
    void writeTrack();

    QXmlStreamWriter m_xml;
    TreeTrack& m_track;
};

#endif // GPXEXPORTER_H
