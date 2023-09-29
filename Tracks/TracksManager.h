//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include <QObject>

#include <TreeTrack.h>

class InputHandler;

class TracksManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TreeTrack* activeTrack READ getActiveTrack CONSTANT)
    Q_PROPERTY(QString activeTrackName READ getActiveTrackName WRITE setActiveTrackName NOTIFY activeTrackNameChanged FINAL)
    Q_PROPERTY(const QVariantList& activeTrackWaypoints READ getActiveTrackWaypoints CONSTANT FINAL)

public:
    explicit TracksManager(QObject *parent = nullptr);

    void connectInputs(const InputHandler *_inputHdl);

    const TreeTrack* getActiveTrack() const {return &m_treeTrack;}
    TreeTrack* getActiveTrack() {return &m_treeTrack;}
    const QString& getActiveTrackName() const;
    void setActiveTrackName(const QString& _name);
    const QVariantList& getActiveTrackWaypoints()
    {
        return getActiveTrack()->getTreeModel()->getWaypoints();
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
    void removeAllPointsFromActiveTrack();

    // Save, Load, Export
    void saveActiveTrackToFile();
    void loadActiveTrackFromFile();
    void exportActiveTrackToGPX();

private:
    TreeTrack m_treeTrack{};

    int m_selectedPoint;
    QString getSaveLoadPath();
};

#endif // TRACKSMANAGER_H
