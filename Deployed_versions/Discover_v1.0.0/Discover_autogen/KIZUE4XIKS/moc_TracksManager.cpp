/****************************************************************************
** Meta object code from reading C++ file 'TracksManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Discover/Tracks/TracksManager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TracksManager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTracksManagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTracksManagerENDCLASS = QtMocHelpers::stringData(
    "TracksManager",
    "activeTrackNameChanged",
    "",
    "addPointToActiveTrack",
    "_name",
    "QGeoCoordinate",
    "_coord",
    "_type",
    "_insertIndex",
    "addPointAfterFirstSelectedToActiveTrack",
    "addPointAsChildOfFirstSelectedToActiveTrack",
    "removePointFromActiveTrack",
    "_markerId",
    "setPointSelected",
    "_selected",
    "setPointCoordinate",
    "removeSelectedPointsFromActiveTrack",
    "removeAllPointsFromActiveTrack",
    "saveActiveTrackToFile",
    "loadActiveTrackFromFile",
    "exportActiveTrackToGPX",
    "activeTrack",
    "TreeTrack*",
    "activeTrackName",
    "activeTrackWaypoints"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTracksManagerENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[14];
    char stringdata1[23];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[6];
    char stringdata5[15];
    char stringdata6[7];
    char stringdata7[6];
    char stringdata8[13];
    char stringdata9[40];
    char stringdata10[44];
    char stringdata11[27];
    char stringdata12[10];
    char stringdata13[17];
    char stringdata14[10];
    char stringdata15[19];
    char stringdata16[36];
    char stringdata17[31];
    char stringdata18[22];
    char stringdata19[24];
    char stringdata20[23];
    char stringdata21[12];
    char stringdata22[11];
    char stringdata23[16];
    char stringdata24[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTracksManagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTracksManagerENDCLASS_t qt_meta_stringdata_CLASSTracksManagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "TracksManager"
        QT_MOC_LITERAL(14, 22),  // "activeTrackNameChanged"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 21),  // "addPointToActiveTrack"
        QT_MOC_LITERAL(60, 5),  // "_name"
        QT_MOC_LITERAL(66, 14),  // "QGeoCoordinate"
        QT_MOC_LITERAL(81, 6),  // "_coord"
        QT_MOC_LITERAL(88, 5),  // "_type"
        QT_MOC_LITERAL(94, 12),  // "_insertIndex"
        QT_MOC_LITERAL(107, 39),  // "addPointAfterFirstSelectedToA..."
        QT_MOC_LITERAL(147, 43),  // "addPointAsChildOfFirstSelecte..."
        QT_MOC_LITERAL(191, 26),  // "removePointFromActiveTrack"
        QT_MOC_LITERAL(218, 9),  // "_markerId"
        QT_MOC_LITERAL(228, 16),  // "setPointSelected"
        QT_MOC_LITERAL(245, 9),  // "_selected"
        QT_MOC_LITERAL(255, 18),  // "setPointCoordinate"
        QT_MOC_LITERAL(274, 35),  // "removeSelectedPointsFromActiv..."
        QT_MOC_LITERAL(310, 30),  // "removeAllPointsFromActiveTrack"
        QT_MOC_LITERAL(341, 21),  // "saveActiveTrackToFile"
        QT_MOC_LITERAL(363, 23),  // "loadActiveTrackFromFile"
        QT_MOC_LITERAL(387, 22),  // "exportActiveTrackToGPX"
        QT_MOC_LITERAL(410, 11),  // "activeTrack"
        QT_MOC_LITERAL(422, 10),  // "TreeTrack*"
        QT_MOC_LITERAL(433, 15),  // "activeTrackName"
        QT_MOC_LITERAL(449, 20)   // "activeTrackWaypoints"
    },
    "TracksManager",
    "activeTrackNameChanged",
    "",
    "addPointToActiveTrack",
    "_name",
    "QGeoCoordinate",
    "_coord",
    "_type",
    "_insertIndex",
    "addPointAfterFirstSelectedToActiveTrack",
    "addPointAsChildOfFirstSelectedToActiveTrack",
    "removePointFromActiveTrack",
    "_markerId",
    "setPointSelected",
    "_selected",
    "setPointCoordinate",
    "removeSelectedPointsFromActiveTrack",
    "removeAllPointsFromActiveTrack",
    "saveActiveTrackToFile",
    "loadActiveTrackFromFile",
    "exportActiveTrackToGPX",
    "activeTrack",
    "TreeTrack*",
    "activeTrackName",
    "activeTrackWaypoints"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTracksManagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       3,  174, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    4,  111,    2, 0x0a,    5 /* Public */,
       3,    3,  120,    2, 0x2a,   10 /* Public | MethodCloned */,
       3,    2,  127,    2, 0x2a,   14 /* Public | MethodCloned */,
       9,    3,  132,    2, 0x0a,   17 /* Public */,
       9,    2,  139,    2, 0x2a,   21 /* Public | MethodCloned */,
      10,    3,  144,    2, 0x0a,   24 /* Public */,
      10,    2,  151,    2, 0x2a,   28 /* Public | MethodCloned */,
      11,    1,  156,    2, 0x0a,   31 /* Public */,
      13,    2,  159,    2, 0x0a,   33 /* Public */,
      15,    2,  164,    2, 0x0a,   36 /* Public */,
      16,    0,  169,    2, 0x0a,   39 /* Public */,
      17,    0,  170,    2, 0x0a,   40 /* Public */,
      18,    0,  171,    2, 0x0a,   41 /* Public */,
      19,    0,  172,    2, 0x0a,   42 /* Public */,
      20,    0,  173,    2, 0x0a,   43 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5, QMetaType::QString, QMetaType::Int,    4,    6,    7,    8,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5, QMetaType::QString,    4,    6,    7,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5, QMetaType::QString,    4,    6,    7,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5, QMetaType::QString,    4,    6,    7,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Bool, QMetaType::Int,   12,
    QMetaType::Bool, QMetaType::Int, QMetaType::Bool,   12,   14,
    QMetaType::Bool, QMetaType::Int, 0x80000000 | 5,   12,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      21, 0x80000000 | 22, 0x00015409, uint(-1), 0,
      23, QMetaType::QString, 0x00015903, uint(0), 0,
      24, QMetaType::QVariantList, 0x00015c01, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject TracksManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTracksManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTracksManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTracksManagerENDCLASS_t,
        // property 'activeTrack'
        QtPrivate::TypeAndForceComplete<TreeTrack*, std::true_type>,
        // property 'activeTrackName'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'activeTrackWaypoints'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TracksManager, std::true_type>,
        // method 'activeTrackNameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addPointToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'addPointToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'addPointToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'addPointAfterFirstSelectedToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'addPointAfterFirstSelectedToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'addPointAsChildOfFirstSelectedToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'addPointAsChildOfFirstSelectedToActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'removePointFromActiveTrack'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setPointSelected'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setPointCoordinate'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QGeoCoordinate &, std::false_type>,
        // method 'removeSelectedPointsFromActiveTrack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeAllPointsFromActiveTrack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveActiveTrackToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadActiveTrackFromFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportActiveTrackToGPX'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TracksManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TracksManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->activeTrackNameChanged(); break;
        case 1: { bool _r = _t->addPointToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->addPointToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->addPointToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->addPointAfterFirstSelectedToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->addPointAfterFirstSelectedToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->addPointAsChildOfFirstSelectedToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->addPointAsChildOfFirstSelectedToActiveTrack((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->removePointFromActiveTrack((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->setPointSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->setPointCoordinate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QGeoCoordinate>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->removeSelectedPointsFromActiveTrack(); break;
        case 12: _t->removeAllPointsFromActiveTrack(); break;
        case 13: _t->saveActiveTrackToFile(); break;
        case 14: _t->loadActiveTrackFromFile(); break;
        case 15: _t->exportActiveTrackToGPX(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TracksManager::*)();
            if (_t _q_method = &TracksManager::activeTrackNameChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TreeTrack* >(); break;
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TracksManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< TreeTrack**>(_v) = _t->getActiveTrack(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getActiveTrackName(); break;
        case 2: *reinterpret_cast< QVariantList*>(_v) = _t->getActiveTrackWaypoints(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TracksManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setActiveTrackName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *TracksManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TracksManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTracksManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TracksManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TracksManager::activeTrackNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
