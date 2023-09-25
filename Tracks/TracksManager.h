#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include <QObject>

#include <Track.h>
#include <TreeTrack.h>

class InputHandler;

class TracksManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Track* activeTrack READ getActiveTrack CONSTANT)
    Q_PROPERTY(QString activeTrackName READ getActiveTrackName WRITE setActiveTrackName NOTIFY activeTrackNameChanged FINAL)
    Q_PROPERTY(const QVariantList& activeTrackWaypoints READ getActiveTrackWaypoints CONSTANT FINAL)

    Q_PROPERTY(TreeTrack* treeTrack READ getTreeTrack CONSTANT)
    Q_PROPERTY(const QVariantList& treeTrackWaypoints READ getTreeTrackWaypoints CONSTANT FINAL)

public:
    explicit TracksManager(QObject *parent = nullptr);

    void connectInputs(const InputHandler *_inputHdl);

    const Track* getActiveTrack() const {return &m_track;}
    Track* getActiveTrack() {return &m_track;}
    const QString& getActiveTrackName() const;
    void setActiveTrackName(const QString& _name);
    const QVariantList& getActiveTrackWaypoints() const
    {
//        for (const QVariant& v : getActiveTrack()->getWaypoints())
//        {
//            qDebug() << Q_FUNC_INFO << v;
//        }
        return getActiveTrack()->getWaypoints();
    }

    const TreeTrack* getTreeTrack() const {return &m_treeTrack;}
    TreeTrack* getTreeTrack() {return &m_treeTrack;}
    const QVariantList getTreeTrackWaypoints()
    {
        return m_treeTrack.getTreeModel()->getWaypoints();
    }

signals:
    void activeTrackNameChanged();

public slots:
    bool addPointToActiveTrack(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin", int _insertIndex = -1);
    bool addPointAfterFirstSelectedToActiveTrack(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool addPointAsChildOfFirstSelectedToActiveTrack(const QString& _name, const QGeoCoordinate& _coord, const QString& _type = "pin");
    bool removePointFromActiveTrack(int _markerId);
    bool setPointSelected(int _markerId, bool _selected /*= true*/);
    bool setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPointsFromActiveTrack();

    // Save, Load, Export
    void saveActiveTrackToFile();
    void loadActiveTrackFromFile();
    void exportActiveTrackToGPX();

private:
    Track m_track{};
    TreeTrack m_treeTrack{};

    int m_selectedPoint;
    QString getSaveLoadPath();
};

#endif // TRACKSMANAGER_H
