/****************************************************************************
** Meta object code from reading C++ file 'NavigationManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../App/NavigationManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NavigationManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NavigationManager_t {
    QByteArrayData data[14];
    char stringdata[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationManager_t qt_meta_stringdata_NavigationManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "NavigationManager"
QT_MOC_LITERAL(1, 18, 11), // "SG_goToPage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "page"
QT_MOC_LITERAL(4, 36, 25), // "number_of_pages_displayed"
QT_MOC_LITERAL(5, 62, 21), // "reload_first_and_last"
QT_MOC_LITERAL(6, 84, 12), // "goToLastPage"
QT_MOC_LITERAL(7, 97, 13), // "goToFirstPage"
QT_MOC_LITERAL(8, 111, 8), // "goToPage"
QT_MOC_LITERAL(9, 120, 12), // "goToNextPage"
QT_MOC_LITERAL(10, 133, 16), // "goToPreviousPage"
QT_MOC_LITERAL(11, 150, 25), // "setNumberPagesInComicBook"
QT_MOC_LITERAL(12, 176, 12), // "number_pages"
QT_MOC_LITERAL(13, 189, 23) // "setNumberPagesDisplayed"

    },
    "NavigationManager\0SG_goToPage\0\0page\0"
    "number_of_pages_displayed\0"
    "reload_first_and_last\0goToLastPage\0"
    "goToFirstPage\0goToPage\0goToNextPage\0"
    "goToPreviousPage\0setNumberPagesInComicBook\0"
    "number_pages\0setNumberPagesDisplayed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   61,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,
      11,    1,   68,    2, 0x0a /* Public */,
      13,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::UInt,   12,

       0        // eod
};

void NavigationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NavigationManager *_t = static_cast<NavigationManager *>(_o);
        switch (_id) {
        case 0: _t->SG_goToPage((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->goToLastPage(); break;
        case 2: _t->goToFirstPage(); break;
        case 3: _t->goToPage((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: _t->goToNextPage(); break;
        case 5: _t->goToPreviousPage(); break;
        case 6: _t->setNumberPagesInComicBook((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 7: _t->setNumberPagesDisplayed((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NavigationManager::*_t)(unsigned int , unsigned int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NavigationManager::SG_goToPage)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject NavigationManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NavigationManager.data,
      qt_meta_data_NavigationManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NavigationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationManager.stringdata))
        return static_cast<void*>(const_cast< NavigationManager*>(this));
    return QObject::qt_metacast(_clname);
}

int NavigationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void NavigationManager::SG_goToPage(unsigned int _t1, unsigned int _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
