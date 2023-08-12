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
