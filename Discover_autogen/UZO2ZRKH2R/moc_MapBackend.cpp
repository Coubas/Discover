/****************************************************************************
** Meta object code from reading C++ file 'MapBackend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Discover/Map/MapBackend.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapBackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMapBackendENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMapBackendENDCLASS = QtMocHelpers::stringData(
    "MapBackend",
    "QML.Element",
    "auto",
    "locusPosUptated",
    "",
    "zoomLevelUpdated",
    "cursorPosChanged",
    "cursorVisibleChanged",
    "onMapClick",
    "QGeoCoordinate",
    "_clickCoord",
    "onMapZoom",
    "_centerCoord",
    "_mouseCoord",
    "_zoomFactor",
    "onMapDrag",
    "_newMapCenter",
    "zoomLevel",
    "locusPos",
    "cursorPos",
    "cursorVisible"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMapBackendENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[16];
    char stringdata4[1];
    char stringdata5[17];
    char stringdata6[17];
    char stringdata7[21];
    char stringdata8[11];
    char stringdata9[15];
    char stringdata10[12];
    char stringdata11[10];
    char stringdata12[13];
    char stringdata13[12];
    char stringdata14[12];
    char stringdata15[10];
    char stringdata16[14];
    char stringdata17[10];
    char stringdata18[9];
    char stringdata19[10];
    char stringdata20[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMapBackendENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMapBackendENDCLASS_t qt_meta_stringdata_CLASSMapBackendENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MapBackend"
        QT_MOC_LITERAL(11, 11),  // "QML.Element"
        QT_MOC_LITERAL(23, 4),  // "auto"
        QT_MOC_LITERAL(28, 15),  // "locusPosUptated"
        QT_MOC_LITERAL(44, 0),  // ""
        QT_MOC_LITERAL(45, 16),  // "zoomLevelUpdated"
        QT_MOC_LITERAL(62, 16),  // "cursorPosChanged"
        QT_MOC_LITERAL(79, 20),  // "cursorVisibleChanged"
        QT_MOC_LITERAL(100, 10),  // "onMapClick"
        QT_MOC_LITERAL(111, 14),  // "QGeoCoordinate"
        QT_MOC_LITERAL(126, 11),  // "_clickCoord"
        QT_MOC_LITERAL(138, 9),  // "onMapZoom"
        QT_MOC_LITERAL(148, 12),  // "_centerCoord"
        QT_MOC_LITERAL(161, 11),  // "_mouseCoord"
        QT_MOC_LITERAL(173, 11),  // "_zoomFactor"
        QT_MOC_LITERAL(185, 9),  // "onMapDrag"
        QT_MOC_LITERAL(195, 13),  // "_newMapCenter"
        QT_MOC_LITERAL(209, 9),  // "zoomLevel"
        QT_MOC_LITERAL(219, 8),  // "locusPos"
        QT_MOC_LITERAL(228, 9),  // "cursorPos"
        QT_MOC_LITERAL(238, 13)   // "cursorVisible"
    },
    "MapBackend",
    "QML.Element",
    "auto",
    "locusPosUptated",
    "",
    "zoomLevelUpdated",
    "cursorPosChanged",
    "cursorVisibleChanged",
    "onMapClick",
    "QGeoCoordinate",
    "_clickCoord",
    "onMapZoom",
    "_centerCoord",
    "_mouseCoord",
    "_zoomFactor",
    "onMapDrag",
    "_newMapCenter",
    "zoomLevel",
    "locusPos",
    "cursorPos",
    "cursorVisible"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMapBackendENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       1,   14, // classinfo
       7,   16, // methods
       4,   75, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   58,    4, 0x06,    5 /* Public */,
       5,    0,   59,    4, 0x06,    6 /* Public */,
       6,    0,   60,    4, 0x06,    7 /* Public */,
       7,    0,   61,    4, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   62,    4, 0x0a,    9 /* Public */,
      11,    3,   65,    4, 0x0a,   11 /* Public */,
      15,    1,   72,    4, 0x0a,   15 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 9,   16,

 // properties: name, type, flags
      17, QMetaType::Float, 0x00015803, uint(1), 0,
      18, 0x80000000 | 9, 0x0001590b, uint(0), 0,
      19, 0x80000000 | 9, 0x0001590b, uint(2), 0,
      20, QMetaType::Bool, 0x00015903, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MapBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSMapBackendENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMapBackendENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'zoomLevel'
        float,
        // property 'locusPos'
        QGeoCoordinate,
        // property 'cursorPos'
        QGeoCoordinate,
        // property 'cursorVisible'
        bool,
        // Q_OBJECT / Q_GADGET
        MapBackend,
        // method 'locusPosUptated'
        void,
        // method 'zoomLevelUpdated'
        void,
        // method 'cursorPosChanged'
        void,
        // method 'cursorVisibleChanged'
        void,
        // method 'onMapClick'
        void,
        const QGeoCoordinate &,
        // method 'onMapZoom'
        void,
        const QGeoCoordinate &,
        const QGeoCoordinate &,
        int,
        // method 'onMapDrag'
        void,
        const QGeoCoordinate &
    >,
    nullptr
} };

void MapBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapBackend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->locusPosUptated(); break;
        case 1: _t->zoomLevelUpdated(); break;
        case 2: _t->cursorPosChanged(); break;
        case 3: _t->cursorVisibleChanged(); break;
        case 4: _t->onMapClick((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 5: _t->onMapZoom((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 6: _t->onMapDrag((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MapBackend::*)();
            if (_t _q_method = &MapBackend::locusPosUptated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MapBackend::*)();
            if (_t _q_method = &MapBackend::zoomLevelUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MapBackend::*)();
            if (_t _q_method = &MapBackend::cursorPosChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MapBackend::*)();
            if (_t _q_method = &MapBackend::cursorVisibleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGeoCoordinate >(); break;
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MapBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->currentZoomLevel(); break;
        case 1: *reinterpret_cast< QGeoCoordinate*>(_v) = _t->locusPos(); break;
        case 2: *reinterpret_cast< QGeoCoordinate*>(_v) = _t->cursorPos(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->cursorVisible(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MapBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCurrentZoomLevel(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setLocusPos(*reinterpret_cast< QGeoCoordinate*>(_v)); break;
        case 2: _t->setCursorPos(*reinterpret_cast< QGeoCoordinate*>(_v)); break;
        case 3: _t->setCursorVisible(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *MapBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMapBackendENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MapBackend::locusPosUptated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MapBackend::zoomLevelUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MapBackend::cursorPosChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MapBackend::cursorVisibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
