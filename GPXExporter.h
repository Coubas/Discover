#ifndef GPXEXPORTER_H
#define GPXEXPORTER_H

#include <QXmlStreamWriter>

class Track;

class GPXExporter
{
public:
    explicit GPXExporter(const Track& _track);

    bool writeFile(QIODevice* _output);

private:
    void writeTrack();

    QXmlStreamWriter m_xml;
    const Track& m_track;
};

#endif // GPXEXPORTER_H
