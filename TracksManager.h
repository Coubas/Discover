#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include <QObject>

#include <Track.h>
#include <Track2.h>

class InputHandler;

class TracksManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Track* activeTrack READ getActiveTrack CONSTANT)

public:
    explicit TracksManager(QObject *parent = nullptr);

    void connectInputs(const InputHandler *_inputHdl);
    const Track* getActiveTrack() const {return &m_track;}
    Track* getActiveTrack() {return &m_track;}

    const Track2* getActiveTrack2() const {return &m_track2;}
    Track2* getActiveTrack2() {return &m_track2;}

signals:

public slots:
    qsizetype getActiveTrackSize() const {return getActiveTrack()->size();}
    void addPointToActiveTrack(const QGeoCoordinate& _coord);
    void removePointFromActiveTrack(int _markerId);
    void setPointSelected(int _markerId, bool _selected /*= true*/);
    void removeSelectedPointsFromActiveTrack();
    void changePointIndexFromActiveTrack(int _oldIndex, int _newIndex);

private:
    Track m_track;
    Track2 m_track2;

    int m_selectedPoint;
};

#endif // TRACKSMANAGER_H
