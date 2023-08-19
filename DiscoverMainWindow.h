#ifndef DISCOVERMAINWINDOW_H
#define DISCOVERMAINWINDOW_H

#include <QObject>

class QGeoCoordinate;
class QGeoLocation;
class InputHandler;
class QQuickWindow;

class DiscoverMainWindow : public QObject
{
    Q_OBJECT
public:
    DiscoverMainWindow(QQuickWindow* _window);

    void connectInputs(const InputHandler *_inputHdl);

    void show(bool _fullscreen = false);

public slots:
    void displayCurrentPos(const QGeoCoordinate& _coord);
    void displayAdress(const QGeoLocation& _loc);

private:
    void bindWindowObjects();

    QQuickWindow* m_window;
    QObject* m_clickLatText;
    QObject* m_clickLonText;
    QObject* m_clickAdressText;
};

#endif // DISCOVERMAINWINDOW_H
