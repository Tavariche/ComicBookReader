/****************************************************************************
** Meta object code from reading C++ file 'ComicBook.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../App/ComicBook.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComicBook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ComicBook_t {
    QByteArrayData data[11];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComicBook_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComicBook_t qt_meta_stringdata_ComicBook = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ComicBook"
QT_MOC_LITERAL(1, 10, 14), // "SG_pagesLoaded"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 31), // "QVector<QVector<PageManager*> >"
QT_MOC_LITERAL(4, 58, 6), // "buffer"
QT_MOC_LITERAL(5, 65, 22), // "SG_numberPagesComputed"
QT_MOC_LITERAL(6, 88, 12), // "number_pages"
QT_MOC_LITERAL(7, 101, 9), // "loadPages"
QT_MOC_LITERAL(8, 111, 10), // "index_page"
QT_MOC_LITERAL(9, 122, 25), // "number_of_pages_displayed"
QT_MOC_LITERAL(10, 148, 21) // "reload_first_and_last"

    },
    "ComicBook\0SG_pagesLoaded\0\0"
    "QVector<QVector<PageManager*> >\0buffer\0"
    "SG_numberPagesComputed\0number_pages\0"
    "loadPages\0index_page\0number_of_pages_displayed\0"
    "reload_first_and_last"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComicBook[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    3,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::UInt,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,    8,    9,   10,

       0        // eod
};

void ComicBook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComicBook *_t = static_cast<ComicBook *>(_o);
        switch (_id) {
        case 0: _t->SG_pagesLoaded((*reinterpret_cast< QVector<QVector<PageManager*> >(*)>(_a[1]))); break;
        case 1: _t->SG_numberPagesComputed((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->loadPages((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<PageManager*> > >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ComicBook::*_t)(QVector<QVector<PageManager*> > );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComicBook::SG_pagesLoaded)) {
                *result = 0;
            }
        }
        {
            typedef void (ComicBook::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComicBook::SG_numberPagesComputed)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ComicBook::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ComicBook.data,
      qt_meta_data_ComicBook,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ComicBook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComicBook::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ComicBook.stringdata))
        return static_cast<void*>(const_cast< ComicBook*>(this));
    return QObject::qt_metacast(_clname);
}

int ComicBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ComicBook::SG_pagesLoaded(QVector<QVector<PageManager*> > _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComicBook::SG_numberPagesComputed(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
