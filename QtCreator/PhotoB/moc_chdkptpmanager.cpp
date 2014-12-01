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
    QByteArrayData data[15];
    char stringdata[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ChdkPtpManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ChdkPtpManager_t qt_meta_stringdata_ChdkPtpManager = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 22),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 32),
QT_MOC_LITERAL(4, 72, 21),
QT_MOC_LITERAL(5, 94, 18),
QT_MOC_LITERAL(6, 113, 24),
QT_MOC_LITERAL(7, 138, 19),
QT_MOC_LITERAL(8, 158, 9),
QT_MOC_LITERAL(9, 168, 6),
QT_MOC_LITERAL(10, 175, 16),
QT_MOC_LITERAL(11, 192, 12),
QT_MOC_LITERAL(12, 205, 16),
QT_MOC_LITERAL(13, 222, 5),
QT_MOC_LITERAL(14, 228, 14)
    },
    "ChdkPtpManager\0signalCamerasListReady\0"
    "\0signalAdditionalCamerasInfoReady\0"
    "signalSettingsApplied\0signalShootingDone\0"
    "signalDownloadPhotosDone\0downloadRecentReady\0"
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
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06,
       3,    0,   60,    2, 0x06,
       4,    0,   61,    2, 0x06,
       5,    0,   62,    2, 0x06,
       6,    0,   63,    2, 0x06,
       7,    1,   64,    2, 0x06,
      10,    0,   67,    2, 0x06,
      11,    1,   68,    2, 0x06,
      14,    0,   71,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

       0        // eod
};

void ChdkPtpManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChdkPtpManager *_t = static_cast<ChdkPtpManager *>(_o);
        switch (_id) {
        case 0: _t->signalCamerasListReady(); break;
        case 1: _t->signalAdditionalCamerasInfoReady(); break;
        case 2: _t->signalSettingsApplied(); break;
        case 3: _t->signalShootingDone(); break;
        case 4: _t->signalDownloadPhotosDone(); break;
        case 5: _t->downloadRecentReady((*reinterpret_cast< PhotoFile(*)>(_a[1]))); break;
        case 6: _t->shootingProgress(); break;
        case 7: _t->shootingDone((*reinterpret_cast< QList<PhotoFile>(*)>(_a[1]))); break;
        case 8: _t->shootingFailed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::signalCamerasListReady)) {
                *result = 0;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::signalAdditionalCamerasInfoReady)) {
                *result = 1;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::signalSettingsApplied)) {
                *result = 2;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::signalShootingDone)) {
                *result = 3;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::signalDownloadPhotosDone)) {
                *result = 4;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)(PhotoFile );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::downloadRecentReady)) {
                *result = 5;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingProgress)) {
                *result = 6;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)(QList<PhotoFile> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingDone)) {
                *result = 7;
            }
        }
        {
            typedef void (ChdkPtpManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChdkPtpManager::shootingFailed)) {
                *result = 8;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ChdkPtpManager::signalCamerasListReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ChdkPtpManager::signalAdditionalCamerasInfoReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ChdkPtpManager::signalSettingsApplied()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ChdkPtpManager::signalShootingDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ChdkPtpManager::signalDownloadPhotosDone()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ChdkPtpManager::downloadRecentReady(PhotoFile _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChdkPtpManager::shootingProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ChdkPtpManager::shootingDone(QList<PhotoFile> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ChdkPtpManager::shootingFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
