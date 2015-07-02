/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu 2. Jul 03:30:47 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x08,
      53,   45,   11,   11, 0x08,
     102,   89,   11,   11, 0x08,
     153,  143,   11,   11, 0x08,
     190,  185,   11,   11, 0x08,
     217,  212,   11,   11, 0x08,
     247,  212,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     300,   11,   11,   11, 0x08,
     324,   11,   11,   11, 0x08,
     347,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0self\0tabCloseRequested(QWidget*)\0"
    "dirName\0newBrowserRequested(const QString*)\0"
    "widget,title\0tabTitleChanged(QWidget*,const QString*)\0"
    "fileNames\0openFilesRequested(QStringList)\0"
    "text\0statusUpdate(QString)\0path\0"
    "handleSearchFromPath(QString)\0"
    "handlePathDeleted(QString)\0"
    "handleSettingsRequested()\0"
    "handleManualRequested()\0handleAboutRequested()\0"
    "handleDirContentsChanged()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->tabCloseRequested((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->newBrowserRequested((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 2: _t->tabTitleChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< const QString*(*)>(_a[2]))); break;
        case 3: _t->openFilesRequested((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 4: _t->statusUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->handleSearchFromPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->handlePathDeleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->handleSettingsRequested(); break;
        case 8: _t->handleManualRequested(); break;
        case 9: _t->handleAboutRequested(); break;
        case 10: _t->handleDirContentsChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
