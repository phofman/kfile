/****************************************************************************
** Meta object code from reading C++ file 'ktexteditor.h'
**
** Created: Mon Sep 24 15:00:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ktexteditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ktexteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KTextEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      56,   43,   12,   12, 0x05,
      97,   12,   12,   12, 0x05,
     122,  117,   12,   12, 0x05,
     158,   12,   12,   12, 0x05,
     175,   12,   12,   12, 0x05,
     198,  193,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     220,   12,   12,   12, 0x08,
     239,   12,   12,   12, 0x08,
     258,   12,   12,   12, 0x08,
     281,   12,   12,   12, 0x08,
     306,   12,   12,   12, 0x08,
     327,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_KTextEditor[] = {
    "KTextEditor\0\0self\0closeRequested(QWidget*)\0"
    "widget,title\0tabTitleChanged(QWidget*,const QString*)\0"
    "settingsRequested()\0path\0"
    "newBrowserRequested(const QString*)\0"
    "aboutRequested()\0manualRequested()\0"
    "text\0statusUpdate(QString)\0"
    "handleExitAction()\0handleSaveAction()\0"
    "handleSettingsAction()\0handleNewBrowserAction()\0"
    "handleManualAction()\0handleAboutAction()\0"
};

void KTextEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KTextEditor *_t = static_cast<KTextEditor *>(_o);
        switch (_id) {
        case 0: _t->closeRequested((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->tabTitleChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< const QString*(*)>(_a[2]))); break;
        case 2: _t->settingsRequested(); break;
        case 3: _t->newBrowserRequested((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 4: _t->aboutRequested(); break;
        case 5: _t->manualRequested(); break;
        case 6: _t->statusUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->handleExitAction(); break;
        case 8: _t->handleSaveAction(); break;
        case 9: _t->handleSettingsAction(); break;
        case 10: _t->handleNewBrowserAction(); break;
        case 11: _t->handleManualAction(); break;
        case 12: _t->handleAboutAction(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KTextEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KTextEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_KTextEditor,
      qt_meta_data_KTextEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KTextEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KTextEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KTextEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KTextEditor))
        return static_cast<void*>(const_cast< KTextEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int KTextEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void KTextEditor::closeRequested(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KTextEditor::tabTitleChanged(QWidget * _t1, const QString * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KTextEditor::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void KTextEditor::newBrowserRequested(const QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KTextEditor::aboutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void KTextEditor::manualRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void KTextEditor::statusUpdate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
