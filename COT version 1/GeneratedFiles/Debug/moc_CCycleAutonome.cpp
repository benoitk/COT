/****************************************************************************
** Meta object code from reading C++ file 'CCycleAutonome.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CCycleAutonome.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CCycleAutonome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CCycleAutonome_t {
    QByteArrayData data[12];
    char stringdata[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCycleAutonome_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCycleAutonome_t qt_meta_stringdata_CCycleAutonome = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 12),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 14),
QT_MOC_LITERAL(4, 44, 13),
QT_MOC_LITERAL(5, 58, 16),
QT_MOC_LITERAL(6, 75, 16),
QT_MOC_LITERAL(7, 92, 16),
QT_MOC_LITERAL(8, 109, 17),
QT_MOC_LITERAL(9, 127, 28),
QT_MOC_LITERAL(10, 156, 24),
QT_MOC_LITERAL(11, 181, 16)
    },
    "CCycleAutonome\0slotRunCycle\0\0"
    "slotPauseCycle\0slotStopCycle\0"
    "slotUnPauseCycle\0slotStopEndCycle\0"
    "slotGoToEndCycle\0slotGoToStepCycle\0"
    "slotGetReadyForPlayNextCycle\0"
    "slotGetReadyForPlayCycle\0slotExecNextStep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCycleAutonome[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    1,   70,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    0,   75,    2, 0x0a /* Public */,

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

void CCycleAutonome::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCycleAutonome *_t = static_cast<CCycleAutonome *>(_o);
        switch (_id) {
        case 0: _t->slotRunCycle(); break;
        case 1: _t->slotPauseCycle(); break;
        case 2: _t->slotStopCycle(); break;
        case 3: _t->slotUnPauseCycle(); break;
        case 4: _t->slotStopEndCycle(); break;
        case 5: _t->slotGoToEndCycle(); break;
        case 6: _t->slotGoToStepCycle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotGetReadyForPlayNextCycle(); break;
        case 8: _t->slotGetReadyForPlayCycle(); break;
        case 9: _t->slotExecNextStep(); break;
        default: ;
        }
    }
}

const QMetaObject CCycleAutonome::staticMetaObject = {
    { &ICycle::staticMetaObject, qt_meta_stringdata_CCycleAutonome.data,
      qt_meta_data_CCycleAutonome,  qt_static_metacall, 0, 0}
};


const QMetaObject *CCycleAutonome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCycleAutonome::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCycleAutonome.stringdata))
        return static_cast<void*>(const_cast< CCycleAutonome*>(this));
    return ICycle::qt_metacast(_clname);
}

int CCycleAutonome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ICycle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
