/****************************************************************************
** Meta object code from reading C++ file 'QloginDialog.h'
**
** Created: Sun Dec 16 16:14:58 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../18-2/QloginDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QloginDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLoginDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      36,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLoginDialog[] = {
    "QLoginDialog\0\0mynButtonOk_Clicked()\0"
    "mynButtonCancel_Clicked()\0"
};

const QMetaObject QLoginDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QLoginDialog,
      qt_meta_data_QLoginDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLoginDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLoginDialog))
        return static_cast<void*>(const_cast< QLoginDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QLoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mynButtonOk_Clicked(); break;
        case 1: mynButtonCancel_Clicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
