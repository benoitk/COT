/****************************************************************************
** Meta object code from reading C++ file 'ICycle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ICycle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ICycle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ICycle_t {
    QByteArrayData data[17];
    char stringdata[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ICycle_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ICycle_t qt_meta_stringdata_ICycle = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 15),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 14),
QT_MOC_LITERAL(4, 39, 14),
QT_MOC_LITERAL(5, 54, 27),
QT_MOC_LITERAL(6, 82, 23),
QT_MOC_LITERAL(7, 106, 12),
QT_MOC_LITERAL(8, 119, 14),
QT_MOC_LITERAL(9, 134, 16),
QT_MOC_LITERAL(10, 151, 13),
QT_MOC_LITERAL(11, 165, 16),
QT_MOC_LITERAL(12, 182, 16),
QT_MOC_LITERAL(13, 199, 17),
QT_MOC_LITERAL(14, 217, 28),
QT_MOC_LITERAL(15, 246, 24),
QT_MOC_LITERAL(16, 271, 16)
    },
    "ICycle\0signalImStopped\0\0signalImPaused\0"
    "signalImRunned\0signalReadyForPlayNextCycle\0"
    "signalReadyForPlayCycle\0slotRunCycle\0"
    "slotPauseCycle\0slotUnPauseCycle\0"
    "slotStopCycle\0slotStopEndCycle\0"
    "slotGoToEndCycle\0slotGoToStepCycle\0"
    "slotGetReadyForPlayNextCycle\0"
    "slotGetReadyForPlayCycle\0slotExecNextStep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ICycle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    1,  100,    2, 0x0a /* Public */,
      14,    0,  103,    2, 0x0a /* Public */,
      15,    0,  104,    2, 0x0a /* Public */,
      16,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ICycle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ICycle *_t = static_cast<ICycle *>(_o);
        switch (_id) {
        case 0: _t->signalImStopped(); break;
        case 1: _t->signalImPaused(); break;
        case 2: _t->signalImRunned(); break;
        case 3: _t->signalReadyForPlayNextCycle(); break;
        case 4: _t->signalReadyForPlayCycle(); break;
        case 5: _t->slotRunCycle(); break;
        case 6: _t->slotPauseCycle(); break;
        case 7: _t->slotUnPauseCycle(); break;
        case 8: _t->slotStopCycle(); break;
        case 9: _t->slotStopEndCycle(); break;
        case 10: _t->slotGoToEndCycle(); break;
        case 11: _t->slotGoToStepCycle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slotGetReadyForPlayNextCycle(); break;
        case 13: _t->slotGetReadyForPlayCycle(); break;
        case 14: _t->slotExecNextStep(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ICycle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ICycle::signalImStopped)) {
                *result = 0;
            }
        }
        {
            typedef void (ICycle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ICycle::signalImPaused)) {
                *result = 1;
            }
        }
        {
            typedef void (ICycle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ICycle::signalImRunned)) {
                *result = 2;
            }
        }
        {
            typedef void (ICycle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ICycle::signalReadyForPlayNextCycle)) {
                *result = 3;
            }
        }
        {
            typedef void (ICycle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ICycle::signalReadyForPlayCycle)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject ICycle::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ICycle.data,
      qt_meta_data_ICycle,  qt_static_metacall, 0, 0}
};


const QMetaObject *ICycle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ICycle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ICycle.stringdata))
        return static_cast<void*>(const_cast< ICycle*>(this));
    return QObject::qt_metacast(_clname);
}

int ICycle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ICycle::signalImStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ICycle::signalImPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ICycle::signalImRunned()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ICycle::signalReadyForPlayNextCycle()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ICycle::signalReadyForPlayCycle()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
