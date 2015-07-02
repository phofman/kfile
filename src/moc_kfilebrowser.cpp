/****************************************************************************
** Meta object code from reading C++ file 'kfilebrowser.h'
**
** Created: Thu 2. Jul 03:30:46 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kfilebrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kfilebrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KFileBrowser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x05,
      52,   44,   13,   13, 0x05,
     101,   88,   13,   13, 0x05,
     147,  142,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,   13,   13,   13, 0x08,
     188,   13,   13,   13, 0x08,
     207,   13,   13,   13, 0x08,
     226,   13,   13,   13, 0x08,
     245,   13,   13,   13, 0x08,
     270,   13,   13,   13, 0x08,
     292,   13,   13,   13, 0x08,
     313,   13,   13,   13, 0x08,
     333,   13,   13,   13, 0x08,
     355,   13,   13,   13, 0x08,
     376,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_KFileBrowser[] = {
    "KFileBrowser\0\0self\0closeRequested(QWidget*)\0"
    "dirName\0newBrowserRequested(const QString*)\0"
    "widget,title\0tabTitleChanged(QWidget*,const QString*)\0"
    "path\0searchFromPath(QString)\0"
    "handleUpAction()\0handleHomeAction()\0"
    "handleViewAction()\0handleExitAction()\0"
    "handleNewBrowserAction()\0handleNewFileAction()\0"
    "handleNewDirAction()\0handlePasteAction()\0"
    "handleRefreshAction()\0handleSearchAction()\0"
    "handleRenameAction()\0"
};

void KFileBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KFileBrowser *_t = static_cast<KFileBrowser *>(_o);
        switch (_id) {
        case 0: _t->closeRequested((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->newBrowserRequested((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 2: _t->tabTitleChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< const QString*(*)>(_a[2]))); break;
        case 3: _t->searchFromPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->handleUpAction(); break;
        case 5: _t->handleHomeAction(); break;
        case 6: _t->handleViewAction(); break;
        case 7: _t->handleExitAction(); break;
        case 8: _t->handleNewBrowserAction(); break;
        case 9: _t->handleNewFileAction(); break;
        case 10: _t->handleNewDirAction(); break;
        case 11: _t->handlePasteAction(); break;
        case 12: _t->handleRefreshAction(); break;
        case 13: _t->handleSearchAction(); break;
        case 14: _t->handleRenameAction(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KFileBrowser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KFileBrowser::staticMetaObject = {
    { &KFileWidget::staticMetaObject, qt_meta_stringdata_KFileBrowser,
      qt_meta_data_KFileBrowser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KFileBrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KFileBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KFileBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KFileBrowser))
        return static_cast<void*>(const_cast< KFileBrowser*>(this));
    return KFileWidget::qt_metacast(_clname);
}

int KFileBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KFileWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void KFileBrowser::closeRequested(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KFileBrowser::newBrowserRequested(const QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KFileBrowser::tabTitleChanged(QWidget * _t1, const QString * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KFileBrowser::searchFromPath(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
