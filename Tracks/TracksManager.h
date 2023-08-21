#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include <QObject>

#include <Track.h>

class InputHandler;

class TracksManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Track* activeTrack READ getActiveTrack CONSTANT)
    Q_PROPERTY(int activeTrackSize READ getActiveTrackSize NOTIFY activeTrackSizeChanged FINAL)
    Q_PROPERTY(QString activeTrackName READ getActiveTrackName WRITE setActiveTrackName NOTIFY activeTrackNameChanged FINAL)

public:
    explicit TracksManager(QObject *parent = nullptr);

    void connectInputs(const InputHandler *_inputHdl);

    const Track* getActiveTrack() const {return &m_track;}
    Track* getActiveTrack() {return &m_track;}
    const QString& getActiveTrackName() const;
    void setActiveTrackName(const QString& _name);
    qsizetype getActiveTrackSize() const {return getActiveTrack()->size();}

signals:
    void activeTrackSizeChanged();
    void activeTrackNameChanged();

public slots:
    void addPointToActiveTrack(const QGeoCoordinate& _coord, int _insertIndex = -1, const QString& _type = "pin");
    void removePointFromActiveTrack(int _markerId);
    void setPointSelected(int _markerId, bool _selected /*= true*/);
    void setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPointsFromActiveTrack();
    void changePointIndexFromActiveTrack(int _oldIndex, int _newIndex);

private:
    Track m_track;

    int m_selectedPoint;
};

#endif // TRACKSMANAGER_H
