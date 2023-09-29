//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

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
