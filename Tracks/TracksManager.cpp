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

bool TracksManager::addPointToActiveTrack(const QGeoCoordinate &_coord, const QString& _type /*= "pin"*/, int _insertIndex /*= -1*/)
{
    return getTreeTrack()->addPoint(_coord, _type, _insertIndex);
}

bool TracksManager::addPointAfterFirstSelectedToActiveTrack(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return getTreeTrack()->addPointAfterFirstSelected(_coord, _type);
}

bool TracksManager::addPointAsChildOfFirstSelectedToActiveTrack(const QGeoCoordinate &_coord, const QString &_type /*= "pin"*/)
{
    return getTreeTrack()->addPointAsChildOfFirstSelected(_coord, _type);
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
        out << *getActiveTrack();

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
        getActiveTrack()->clear();
        in >> *getActiveTrack();

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

        GPXExporter exporter{*getActiveTrack()};
        exporter.writeFile(&file);

        file.close();
    }
}
