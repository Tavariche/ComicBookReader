/****************************************************************************
** Meta object code from reading C++ file 'PagesContainerDouble.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../App/PagesContainerDouble.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PagesContainerDouble.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PagesContainerDouble_t {
    QByteArrayData data[8];
    char stringdata[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PagesContainerDouble_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PagesContainerDouble_t qt_meta_stringdata_PagesContainerDouble = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PagesContainerDouble"
QT_MOC_LITERAL(1, 21, 17), // "cursorResizePages"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "width"
QT_MOC_LITERAL(4, 46, 9), // "fitHeight"
QT_MOC_LITERAL(5, 56, 8), // "fitWidth"
QT_MOC_LITERAL(6, 65, 9), // "fitScreen"
QT_MOC_LITERAL(7, 75, 7) // "refresh"

    },
    "PagesContainerDouble\0cursorResizePages\0"
    "\0width\0fitHeight\0fitWidth\0fitScreen\0"
    "refresh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PagesContainerDouble[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PagesContainerDouble::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PagesContainerDouble *_t = static_cast<PagesContainerDouble *>(_o);
        switch (_id) {
        case 0: _t->cursorResizePages((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->fitHeight(); break;
        case 2: _t->fitWidth(); break;
        case 3: _t->fitScreen(); break;
        case 4: _t->refresh(); break;
        default: ;
        }
    }
}

const QMetaObject PagesContainerDouble::staticMetaObject = {
    { &PagesContainer::staticMetaObject, qt_meta_stringdata_PagesContainerDouble.data,
      qt_meta_data_PagesContainerDouble,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PagesContainerDouble::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PagesContainerDouble::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PagesContainerDouble.stringdata))
        return static_cast<void*>(const_cast< PagesContainerDouble*>(this));
    return PagesContainer::qt_metacast(_clname);
}

int PagesContainerDouble::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PagesContainer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
