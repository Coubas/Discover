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
    Q_PROPERTY(int activeTrackSize READ getActiveTrackSize NOTIFY activeTrackSizeChanged FINAL)
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
    qsizetype getActiveTrackSize() const {return getActiveTrack()->size();}
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
    const QVariantList getTreeTrackWaypoints() const
    {
        return m_treeTrack.getTreeModel()->getWaypoints();
    }

signals:
    void activeTrackSizeChanged();
    void activeTrackNameChanged();

public slots:
    void addPointToActiveTrack(const QGeoCoordinate& _coord, const QString& _type = "pin", int _insertIndex = -1);
    void removePointFromActiveTrack(int _markerId);
    void setPointSelected(int _markerId, bool _selected /*= true*/);
    void setPointCoordinate(int _markerId, const QGeoCoordinate& _coord);
    void removeSelectedPointsFromActiveTrack();
    void changePointIndexFromActiveTrack(int _oldIndex, int _newIndex);

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
