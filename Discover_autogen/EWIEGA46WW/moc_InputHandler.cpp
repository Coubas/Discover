/****************************************************************************
** Meta object code from reading C++ file 'InputHandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Discover/InputHandler.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputHandler.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSInputHandlerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSInputHandlerENDCLASS = QtMocHelpers::stringData(
    "InputHandler",
    "mapZoomed",
    "",
    "QGeoCoordinate",
    "_centerCoord",
    "_mouseCoord",
    "_zoomFactor",
    "mapDraged",
    "_newMapCenter",
    "mapClicked",
    "cursorPosChanged",
    "_coord",
    "cursorGeolocComputed",
    "QGeoLocation",
    "_loc",
    "onMapZoomed",
    "onMapDraged",
    "onMapClicked",
    "onCursorGeolocComputed",
    "onCursorPosChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSInputHandlerENDCLASS_t {
    uint offsetsAndSizes[40];
    char stringdata0[13];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[13];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[10];
    char stringdata8[14];
    char stringdata9[11];
    char stringdata10[17];
    char stringdata11[7];
    char stringdata12[21];
    char stringdata13[13];
    char stringdata14[5];
    char stringdata15[12];
    char stringdata16[12];
    char stringdata17[13];
    char stringdata18[23];
    char stringdata19[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInputHandlerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSInputHandlerENDCLASS_t qt_meta_stringdata_CLASSInputHandlerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "InputHandler"
        QT_MOC_LITERAL(13, 9),  // "mapZoomed"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 14),  // "QGeoCoordinate"
        QT_MOC_LITERAL(39, 12),  // "_centerCoord"
        QT_MOC_LITERAL(52, 11),  // "_mouseCoord"
        QT_MOC_LITERAL(64, 11),  // "_zoomFactor"
        QT_MOC_LITERAL(76, 9),  // "mapDraged"
        QT_MOC_LITERAL(86, 13),  // "_newMapCenter"
        QT_MOC_LITERAL(100, 10),  // "mapClicked"
        QT_MOC_LITERAL(111, 16),  // "cursorPosChanged"
        QT_MOC_LITERAL(128, 6),  // "_coord"
        QT_MOC_LITERAL(135, 20),  // "cursorGeolocComputed"
        QT_MOC_LITERAL(156, 12),  // "QGeoLocation"
        QT_MOC_LITERAL(169, 4),  // "_loc"
        QT_MOC_LITERAL(174, 11),  // "onMapZoomed"
        QT_MOC_LITERAL(186, 11),  // "onMapDraged"
        QT_MOC_LITERAL(198, 12),  // "onMapClicked"
        QT_MOC_LITERAL(211, 22),  // "onCursorGeolocComputed"
        QT_MOC_LITERAL(234, 18)   // "onCursorPosChanged"
    },
    "InputHandler",
    "mapZoomed",
    "",
    "QGeoCoordinate",
    "_centerCoord",
    "_mouseCoord",
    "_zoomFactor",
    "mapDraged",
    "_newMapCenter",
    "mapClicked",
    "cursorPosChanged",
    "_coord",
    "cursorGeolocComputed",
    "QGeoLocation",
    "_loc",
    "onMapZoomed",
    "onMapDraged",
    "onMapClicked",
    "onCursorGeolocComputed",
    "onCursorPosChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInputHandlerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   74,    2, 0x06,    1 /* Public */,
       7,    1,   81,    2, 0x06,    5 /* Public */,
       9,    1,   84,    2, 0x06,    7 /* Public */,
      10,    1,   87,    2, 0x06,    9 /* Public */,
      12,    1,   90,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    3,   93,    2, 0x0a,   13 /* Public */,
      16,    1,  100,    2, 0x0a,   17 /* Public */,
      17,    1,  103,    2, 0x0a,   19 /* Public */,
      18,    1,  106,    2, 0x0a,   21 /* Public */,
      19,    1,  109,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    5,
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    5,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 3,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject InputHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSInputHandlerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInputHandlerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInputHandlerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InputHandler, std::true_type>,
        // method 'mapZoomed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'mapDraged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'mapClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'cursorPosChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'cursorGeolocComputed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoLocation &, std::false_type>,
        // method 'onMapZoomed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onMapDraged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'onMapClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'onCursorGeolocComputed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoLocation &, std::false_type>,
        // method 'onCursorPosChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>
    >,
    nullptr
} };

void InputHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InputHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mapZoomed((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->mapDraged((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 2: _t->mapClicked((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 3: _t->cursorPosChanged((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 4: _t->cursorGeolocComputed((*reinterpret_cast< std::add_pointer_t<QGeoLocation>>(_a[1]))); break;
        case 5: _t->onMapZoomed((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 6: _t->onMapDraged((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 7: _t->onMapClicked((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        case 8: _t->onCursorGeolocComputed((*reinterpret_cast< std::add_pointer_t<QGeoLocation>>(_a[1]))); break;
        case 9: _t->onCursorPosChanged((*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoLocation >(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoCoordinate >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QGeoLocation >(); break;
            }
            break;
        case 9:
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
            using _t = void (InputHandler::*)(const QGeoCoordinate & , const QGeoCoordinate & , int );
            if (_t _q_method = &InputHandler::mapZoomed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InputHandler::*)(const QGeoCoordinate & );
            if (_t _q_method = &InputHandler::mapDraged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InputHandler::*)(const QGeoCoordinate & );
            if (_t _q_method = &InputHandler::mapClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (InputHandler::*)(const QGeoCoordinate & );
            if (_t _q_method = &InputHandler::cursorPosChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (InputHandler::*)(const QGeoLocation & );
            if (_t _q_method = &InputHandler::cursorGeolocComputed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *InputHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInputHandlerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InputHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void InputHandler::mapZoomed(const QGeoCoordinate & _t1, const QGeoCoordinate & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InputHandler::mapDraged(const QGeoCoordinate & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InputHandler::mapClicked(const QGeoCoordinate & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void InputHandler::cursorPosChanged(const QGeoCoordinate & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void InputHandler::cursorGeolocComputed(const QGeoLocation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
