/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
    char stringdata[521];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 17),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 20),
QT_MOC_LITERAL(4, 51, 28),
QT_MOC_LITERAL(5, 80, 30),
QT_MOC_LITERAL(6, 111, 15),
QT_MOC_LITERAL(7, 127, 9),
QT_MOC_LITERAL(8, 137, 8),
QT_MOC_LITERAL(9, 146, 25),
QT_MOC_LITERAL(10, 172, 27),
QT_MOC_LITERAL(11, 200, 17),
QT_MOC_LITERAL(12, 218, 16),
QT_MOC_LITERAL(13, 235, 22),
QT_MOC_LITERAL(14, 258, 22),
QT_MOC_LITERAL(15, 281, 31),
QT_MOC_LITERAL(16, 313, 14),
QT_MOC_LITERAL(17, 328, 15),
QT_MOC_LITERAL(18, 344, 23),
QT_MOC_LITERAL(19, 368, 17),
QT_MOC_LITERAL(20, 386, 4),
QT_MOC_LITERAL(21, 391, 12),
QT_MOC_LITERAL(22, 404, 24),
QT_MOC_LITERAL(23, 429, 20),
QT_MOC_LITERAL(24, 450, 5),
QT_MOC_LITERAL(25, 456, 19),
QT_MOC_LITERAL(26, 476, 22),
QT_MOC_LITERAL(27, 499, 17),
QT_MOC_LITERAL(28, 517, 2)
    },
    "MainWindow\0slotReloadCameras\0\0"
    "slotCamerasListReady\0slotGetAdditionalCamerasInfo\0"
    "slotAdditionalCamerasInfoReady\0"
    "collectSettings\0Settings&\0settings\0"
    "slotApplyShootingSettings\0"
    "slotShootingSettingsApplied\0"
    "slotStartShooting\0slotShootingDone\0"
    "slotDownloadLastPhotos\0slotDownloadPhotosDone\0"
    "slotStartSelectedCameraShooting\0"
    "updateSettings\0slotShutdownAll\0"
    "slotCameraDoubleClicked\0QTableWidgetItem*\0"
    "item\0slotDiagnose\0slotConfigureStaticProps\0"
    "slotFlashModeChanged\0state\0"
    "slotPreshootChanged\0slotManualFocusChanged\0"
    "serialNumberReady\0sn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x0a,
       3,    0,  120,    2, 0x0a,
       4,    0,  121,    2, 0x0a,
       5,    0,  122,    2, 0x0a,
       6,    1,  123,    2, 0x0a,
       9,    0,  126,    2, 0x0a,
      10,    0,  127,    2, 0x0a,
      11,    0,  128,    2, 0x0a,
      12,    0,  129,    2, 0x0a,
      13,    0,  130,    2, 0x0a,
      14,    0,  131,    2, 0x0a,
      15,    0,  132,    2, 0x0a,
      16,    0,  133,    2, 0x0a,
      17,    0,  134,    2, 0x0a,
      18,    1,  135,    2, 0x0a,
      21,    0,  138,    2, 0x0a,
      22,    0,  139,    2, 0x0a,
      23,    1,  140,    2, 0x0a,
      25,    1,  143,    2, 0x0a,
      26,    1,  146,    2, 0x0a,
      27,    1,  149,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->slotReloadCameras(); break;
        case 1: _t->slotCamerasListReady(); break;
        case 2: _t->slotGetAdditionalCamerasInfo(); break;
        case 3: _t->slotAdditionalCamerasInfoReady(); break;
        case 4: _t->collectSettings((*reinterpret_cast< Settings(*)>(_a[1]))); break;
        case 5: _t->slotApplyShootingSettings(); break;
        case 6: _t->slotShootingSettingsApplied(); break;
        case 7: _t->slotStartShooting(); break;
        case 8: _t->slotShootingDone(); break;
        case 9: _t->slotDownloadLastPhotos(); break;
        case 10: _t->slotDownloadPhotosDone(); break;
        case 11: _t->slotStartSelectedCameraShooting(); break;
        case 12: _t->updateSettings(); break;
        case 13: _t->slotShutdownAll(); break;
        case 14: _t->slotCameraDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 15: _t->slotDiagnose(); break;
        case 16: _t->slotConfigureStaticProps(); break;
        case 17: _t->slotFlashModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->slotPreshootChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slotManualFocusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->serialNumberReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
