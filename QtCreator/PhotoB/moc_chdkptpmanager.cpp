/****************************************************************************
** Meta object code from reading C++ file 'chdkptpmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chdkptpmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chdkptpmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChdkPtpManager_t {
    QByteArrayData data[10];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ChdkPtpManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ChdkPtpManager_t qt_meta_stringdata_ChdkPtpManager = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 19),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 9),
QT_MOC_LITERAL(4, 46, 6),
QT_MOC_LITERAL(5, 53, 16),
QT_MOC_LITERAL(6, 70, 12),
QT_MOC_LITERAL(7, 83, 16),
QT_MOC_LITERAL(8, 100, 5),
QT_MOC_LITERAL(9, 106, 14)
    },
    "ChdkPtpManager\0downloadRecentReady\0\0"
    "PhotoFile\0photos\0shootingProgress\0"
    "shootingDone\0QList<PhotoFile>\0files\0"
    "shootingFailed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChdkPtpManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06,
       5,    0,   37,    2, 0x06,
       6,    1,   38,    2, 0x06,
       9,    0,   41,    2, 0x06,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void ChdkPtpManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChdkPtpManager *_t = static_cast<ChdkPtpManager *>(_o);
        switch (_id) {
        case 0: _t->downloadRecentReady((*reinterpret_cast< PhotoFile(*)>(_a[1]))); break;
        case 1: _t->shootingProgress(); break;
        case 2: _t->shootingDone((*reinterpret_cast< QList<PhotoFile>(*)>(_a[1]))); break;
        case 3: _t->shootingFailed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChdkPtpManager::*_t)(PhotoFile );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::downloadRecentReady)) {
                *result = 0;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingProgress)) {
                *result = 1;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)(QList<PhotoFile> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingDone)) {
                *result = 2;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingFailed)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ChdkPtpManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChdkPtpManager.data,
      qt_meta_data_ChdkPtpManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *ChdkPtpManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChdkPtpManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChdkPtpManager.stringdata))
        return static_cast<void*>(const_cast< ChdkPtpManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ChdkPtpManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ChdkPtpManager::downloadRecentReady(PhotoFile _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChdkPtpManager::shootingProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ChdkPtpManager::shootingDone(QList<PhotoFile> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChdkPtpManager::shootingFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
