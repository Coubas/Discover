#include "TracksManager.h"

#include <QFileDialog>
#include <QMessageBox>

#include <InputHandler.h>
#include <GPXExporter.h>

TracksManager::TracksManager(QObject *parent)
    : QObject{parent}
{
//    m_track.setName("My first track");
//    m_track.addPoint(QGeoCoordinate(43.77483, 3.86748), "circle");
//    m_track.addPoint(QGeoCoordinate(43.78895, 3.80571));
//    m_track.addPoint(QGeoCoordinate(43.82016, 3.81434));
//    m_track.addPoint(QGeoCoordinate(43.89330, 3.85638));

    m_treeTrack.setName("My first tree track");
    // id, type, coord, loop, selected, active
    MapMarkerTreeItemData item1{0, "pin", QGeoCoordinate(43.844537, 3.699751), "Name 1", false, false, true};
    MapMarkerTreeItemData item11{1, "pin", QGeoCoordinate(43.835689, 3.742811), "Name 11", false, false, true};
    MapMarkerTreeItemData item12{2, "pin", QGeoCoordinate(43.788150, 3.732020), "Name 12", true, false, true};
    MapMarkerTreeItemData item121{3, "pin", QGeoCoordinate(43.786633, 3.856006), "Name 121", false, false, true};
    MapMarkerTreeItemData item122{4, "pin", QGeoCoordinate(43.737513, 3.832989), "Name 122", false, false, true};
    MapMarkerTreeItemData item13{5, "pin", QGeoCoordinate(43.745660, 3.708688), "Name 13", false, false, true};
    MapMarkerTreeItemData item2{6, "pin", QGeoCoordinate(43.723447, 3.628990), "Name 2", false, false, true};
    MapMarkerTreeItemData item3{7, "pin", QGeoCoordinate(43.706158, 3.600439), "Name 3", false, false, false};

    m_treeTrack.getTreeModel()->getRoot()->appendChild(item1);
    m_treeTrack.getTreeModel()->getRoot()->child(0)->appendChild(item11);
    m_treeTrack.getTreeModel()->getRoot()->child(0)->appendChild(item12);
    m_treeTrack.getTreeModel()->getRoot()->child(0)->child(1)->appendChild(item121);
    m_treeTrack.getTreeModel()->getRoot()->child(0)->child(1)->appendChild(item122);
    m_treeTrack.getTreeModel()->getRoot()->child(0)->appendChild(item13);
    m_treeTrack.getTreeModel()->getRoot()->appendChild(item2);
    m_treeTrack.getTreeModel()->getRoot()->appendChild(item3);
    m_treeTrack.getTreeModel()->setIdCounter(8);
    m_treeTrack.getTreeModel()->updateTreeItemIndexInfo();
}

void TracksManager::connectInputs(const InputHandler* _inputHdl)
{
    if(_inputHdl == nullptr)
    {
        return;
    }

    //connect(_inputHdl, SIGNAL(mapClicked(QGeoCoordinate)), this, SLOT(addPointToActiveTrack(QGeoCoordinate)));
}

const QString &TracksManager::getActiveTrackName() const
{
    return getTreeTrack()->name();
}

void TracksManager::setActiveTrackName(const QString &_name)
{
    getTreeTrack()->setName(_name);
    emit activeTrackNameChanged();
}

bool TracksManager::addPointToActiveTrack(const QString& _name, const QGeoCoordinate &_coord, const QString& _type /*= "pin"*/, int _insertIndex /*= -1*/)
{
    return getTreeTrack()->addPoint(_name, _coord, _type, _insertIndex);
}

bool TracksManager::addPointAfterFirstSelectedToActiveTrack(const QString& _name, const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return getTreeTrack()->addPointAfterFirstSelected(_name, _coord, _type);
}

bool TracksManager::addPointAsChildOfFirstSelectedToActiveTrack(const QString& _name, const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return getTreeTrack()->addPointAsChildOfFirstSelected(_name, _coord, _type);
}

bool TracksManager::removePointFromActiveTrack(int _markerId)
{
    return getTreeTrack()->removePoint(_markerId);
}

bool TracksManager::setPointSelected(int _markerId, bool _selected /*= true*/)
{
    return getTreeTrack()->setPointSelected(_markerId, _selected);
}

bool TracksManager::setPointCoordinate(int _markerId, const QGeoCoordinate &_coord)
{
    return getTreeTrack()->setPointCoordinate(_markerId, _coord);
}

void TracksManager::removeSelectedPointsFromActiveTrack()
{
    getTreeTrack()->removeSelectedPoints();
}

void TracksManager::removeAllPointsFromActiveTrack()
{
    getTreeTrack()->removeAllPoints();
}

QString TracksManager::getSaveLoadPath()
{
    QDir dir = QDir::current();
    QString path = dir.path() + "/Mytracks/";
    dir.mkpath(path);

    return path;
}

void TracksManager::saveActiveTrackToFile()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save ") + getActiveTrackName(), getSaveLoadPath() + getActiveTrackName(), tr("Discover Track (*.dtrack);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(nullptr, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_6_5);
        out << *getTreeTrack();

        file.close();
    }
}

void TracksManager::loadActiveTrackFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Track"), getSaveLoadPath(), tr("Discover Track (*.dtrack);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5);
        getTreeTrack()->clear();
        in >> *getTreeTrack();

        file.close();
        emit activeTrackNameChanged();
    }
}

void TracksManager::exportActiveTrackToGPX()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Export ") + getActiveTrackName(), getSaveLoadPath() + getActiveTrackName(), tr("GPX (*.gpx);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(nullptr, tr("Unable to open file"), file.errorString());
            return;
        }

        GPXExporter exporter{*getTreeTrack()};
        exporter.writeFile(&file);

        file.close();
    }
}
