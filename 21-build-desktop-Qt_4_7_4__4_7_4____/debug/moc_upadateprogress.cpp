/****************************************************************************
** Meta object code from reading C++ file 'upadateprogress.h'
**
** Created: Sat Oct 17 10:57:07 2020
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../21/upadateprogress.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upadateprogress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpadateProgress[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   16,   16,   16, 0x0a,
      48,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UpadateProgress[] = {
    "UpadateProgress\0\0UpdateSteps(int)\0"
    "TimeOutSlot()\0UpadateProgressSlot()\0"
};

const QMetaObject UpadateProgress::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UpadateProgress,
      qt_meta_data_UpadateProgress, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpadateProgress::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpadateProgress::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpadateProgress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpadateProgress))
        return static_cast<void*>(const_cast< UpadateProgress*>(this));
    return QObject::qt_metacast(_clname);
}

int UpadateProgress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UpdateSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: TimeOutSlot(); break;
        case 2: UpadateProgressSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UpadateProgress::UpdateSteps(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
