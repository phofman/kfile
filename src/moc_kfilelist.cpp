/****************************************************************************
** Meta object code from reading C++ file 'kfilelist.h'
**
** Created: Mon Sep 24 15:00:39 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kfilelist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kfilelist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KFileList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x05,
      46,   41,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   10,   10,   10, 0x08,
     101,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_KFileList[] = {
    "KFileList\0\0self\0closeRequested(QWidget*)\0"
    "path\0newBrowserRequested(const QString*)\0"
    "handleExitAction()\0handleNewBrowserAction()\0"
};

void KFileList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KFileList *_t = static_cast<KFileList *>(_o);
        switch (_id) {
        case 0: _t->closeRequested((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->newBrowserRequested((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 2: _t->handleExitAction(); break;
        case 3: _t->handleNewBrowserAction(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KFileList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KFileList::staticMetaObject = {
    { &KFileWidget::staticMetaObject, qt_meta_stringdata_KFileList,
      qt_meta_data_KFileList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KFileList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KFileList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KFileList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KFileList))
        return static_cast<void*>(const_cast< KFileList*>(this));
    return KFileWidget::qt_metacast(_clname);
}

int KFileList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KFileWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KFileList::closeRequested(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KFileList::newBrowserRequested(const QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
