/****************************************************************************
** Meta object code from reading C++ file 'PagesContainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../App/PagesContainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PagesContainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PagesContainer_t {
    QByteArrayData data[20];
    char stringdata[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PagesContainer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PagesContainer_t qt_meta_stringdata_PagesContainer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PagesContainer"
QT_MOC_LITERAL(1, 15, 16), // "pagesSizeChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "width"
QT_MOC_LITERAL(4, 39, 9), // "fitHeight"
QT_MOC_LITERAL(5, 49, 8), // "fitWidth"
QT_MOC_LITERAL(6, 58, 9), // "fitScreen"
QT_MOC_LITERAL(7, 68, 7), // "refresh"
QT_MOC_LITERAL(8, 76, 8), // "setPages"
QT_MOC_LITERAL(9, 85, 17), // "QVector<QPixmap*>"
QT_MOC_LITERAL(10, 103, 8), // "newPages"
QT_MOC_LITERAL(11, 112, 17), // "setPersonalPolicy"
QT_MOC_LITERAL(12, 130, 8), // "newWidth"
QT_MOC_LITERAL(13, 139, 17), // "setFitWidthPolicy"
QT_MOC_LITERAL(14, 157, 18), // "setFitHeightPolicy"
QT_MOC_LITERAL(15, 176, 18), // "setFitScreenPolicy"
QT_MOC_LITERAL(16, 195, 15), // "setResizePolicy"
QT_MOC_LITERAL(17, 211, 12), // "ResizePolicy"
QT_MOC_LITERAL(18, 224, 9), // "newPolicy"
QT_MOC_LITERAL(19, 234, 17) // "applyResizePolicy"

    },
    "PagesContainer\0pagesSizeChanged\0\0width\0"
    "fitHeight\0fitWidth\0fitScreen\0refresh\0"
    "setPages\0QVector<QPixmap*>\0newPages\0"
    "setPersonalPolicy\0newWidth\0setFitWidthPolicy\0"
    "setFitHeightPolicy\0setFitScreenPolicy\0"
    "setResizePolicy\0ResizePolicy\0newPolicy\0"
    "applyResizePolicy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PagesContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   77,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    1,   81,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      15,    0,   89,    2, 0x0a /* Public */,
      16,    1,   90,    2, 0x0a /* Public */,
      19,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

       0        // eod
};

void PagesContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PagesContainer *_t = static_cast<PagesContainer *>(_o);
        switch (_id) {
        case 0: _t->pagesSizeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->fitHeight(); break;
        case 2: _t->fitWidth(); break;
        case 3: _t->fitScreen(); break;
        case 4: _t->refresh(); break;
        case 5: _t->setPages((*reinterpret_cast< const QVector<QPixmap*>(*)>(_a[1]))); break;
        case 6: _t->setPersonalPolicy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setFitWidthPolicy(); break;
        case 8: _t->setFitHeightPolicy(); break;
        case 9: _t->setFitScreenPolicy(); break;
        case 10: _t->setResizePolicy((*reinterpret_cast< const ResizePolicy(*)>(_a[1]))); break;
        case 11: _t->applyResizePolicy(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PagesContainer::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PagesContainer::pagesSizeChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject PagesContainer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PagesContainer.data,
      qt_meta_data_PagesContainer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PagesContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PagesContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PagesContainer.stringdata))
        return static_cast<void*>(const_cast< PagesContainer*>(this));
    return QWidget::qt_metacast(_clname);
}

int PagesContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void PagesContainer::pagesSizeChanged(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
