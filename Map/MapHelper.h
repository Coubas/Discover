//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef MAPHELPER_H
#define MAPHELPER_H

#include "qqmlengine.h"
#include <QObject>

class MapHelper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MapHelper)

    MapHelper() {}

public:
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new MapHelper;
    }

    Q_INVOKABLE static float getPosition() {return 5.2f;}

};

#endif // MAPHELPER_H
