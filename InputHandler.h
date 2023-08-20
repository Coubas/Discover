#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QObject>

class InputHandler : public QObject
{
    Q_OBJECT

public:
    explicit InputHandler(QObject *parent = nullptr);

public slots:
    void onMapZoomed(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor);
    void onMapDraged(const QGeoCoordinate& _newMapCenter);
    void onMapClicked(const QGeoCoordinate& _mouseCoord);

    void onCursorGeolocComputed(const QGeoLocation& _loc);
    void onCursorPosChanged(const QGeoCoordinate& _coord);

signals:
    void mapZoomed(const QGeoCoordinate& _centerCoord, const QGeoCoordinate& _mouseCoord, int _zoomFactor);
    void mapDraged(const QGeoCoordinate& _newMapCenter);
    void mapClicked(const QGeoCoordinate& _mouseCoord);

    void cursorPosChanged(const QGeoCoordinate& _coord);
    void cursorGeolocComputed(const QGeoLocation& _loc);
};

#endif // INPUTHANDLER_H
