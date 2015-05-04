/****************************************************************************
** Meta object code from reading C++ file 'kfilewidget.h'
**
** Created: Mon Sep 24 15:00:40 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kfilewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kfilewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KFileWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      44,   39,   12,   12, 0x05,
      76,   66,   12,   12, 0x05,
     108,   12,   12,   12, 0x05,
     128,   12,   12,   12, 0x05,
     145,   12,   12,   12, 0x05,
     163,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     184,   12,   12,   12, 0x09,
     203,   12,   12,   12, 0x09,
     229,  224,   12,   12, 0x09,
     265,  224,   12,   12, 0x09,
     297,   12,   12,   12, 0x09,
     316,   12,   12,   12, 0x09,
     334,   12,   12,   12, 0x09,
     357,   12,   12,   12, 0x09,
     378,   12,   12,   12, 0x09,
     398,   12,   12,   12, 0x09,
     422,   12,   12,   12, 0x09,
     447,   12,   12,   12, 0x09,
     473,  464,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_KFileWidget[] = {
    "KFileWidget\0\0path\0pathDeleted(QString)\0"
    "text\0statusUpdate(QString)\0fileNames\0"
    "openFilesRequested(QStringList)\0"
    "settingsRequested()\0aboutRequested()\0"
    "manualRequested()\0dirContentsChanged()\0"
    "handleOpenAction()\0handleDeleteAction()\0"
    "item\0itemDoubleClicked(QListWidgetItem*)\0"
    "itemActivated(QListWidgetItem*)\0"
    "handleCopyAction()\0handleCutAction()\0"
    "handleSettingsAction()\0handleManualAction()\0"
    "handleAboutAction()\0handleSelectAllAction()\0"
    "handleSelectNoneAction()\0toggleViewMode()\0"
    "viewMode\0setViewMode(ViewMode)\0"
};

void KFileWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KFileWidget *_t = static_cast<KFileWidget *>(_o);
        switch (_id) {
        case 0: _t->pathDeleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->statusUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->openFilesRequested((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->settingsRequested(); break;
        case 4: _t->aboutRequested(); break;
        case 5: _t->manualRequested(); break;
        case 6: _t->dirContentsChanged(); break;
        case 7: _t->handleOpenAction(); break;
        case 8: _t->handleDeleteAction(); break;
        case 9: _t->itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->itemActivated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->handleCopyAction(); break;
        case 12: _t->handleCutAction(); break;
        case 13: _t->handleSettingsAction(); break;
        case 14: _t->handleManualAction(); break;
        case 15: _t->handleAboutAction(); break;
        case 16: _t->handleSelectAllAction(); break;
        case 17: _t->handleSelectNoneAction(); break;
        case 18: _t->toggleViewMode(); break;
        case 19: _t->setViewMode((*reinterpret_cast< ViewMode(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KFileWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KFileWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_KFileWidget,
      qt_meta_data_KFileWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KFileWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KFileWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KFileWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KFileWidget))
        return static_cast<void*>(const_cast< KFileWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int KFileWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void KFileWidget::pathDeleted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KFileWidget::statusUpdate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KFileWidget::openFilesRequested(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KFileWidget::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void KFileWidget::aboutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void KFileWidget::manualRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void KFileWidget::dirContentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
