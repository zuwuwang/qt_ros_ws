/****************************************************************************
** Meta object code from reading C++ file 'imagesave_node.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/guitest/include/guitest/imagesave_node.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagesave_node.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_guitest__ImageSaveNode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      45,   23,   23,   23, 0x05,
      62,   23,   23,   23, 0x05,
      75,   23,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_guitest__ImageSaveNode[] = {
    "guitest::ImageSaveNode\0\0displayCameraImage()\0"
    "loggingUpdated()\0socketSend()\0"
    "rosShutdown()\0"
};

void guitest::ImageSaveNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageSaveNode *_t = static_cast<ImageSaveNode *>(_o);
        switch (_id) {
        case 0: _t->displayCameraImage(); break;
        case 1: _t->loggingUpdated(); break;
        case 2: _t->socketSend(); break;
        case 3: _t->rosShutdown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData guitest::ImageSaveNode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject guitest::ImageSaveNode::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_guitest__ImageSaveNode,
      qt_meta_data_guitest__ImageSaveNode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &guitest::ImageSaveNode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *guitest::ImageSaveNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *guitest::ImageSaveNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_guitest__ImageSaveNode))
        return static_cast<void*>(const_cast< ImageSaveNode*>(this));
    return QThread::qt_metacast(_clname);
}

int guitest::ImageSaveNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void guitest::ImageSaveNode::displayCameraImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void guitest::ImageSaveNode::loggingUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void guitest::ImageSaveNode::socketSend()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void guitest::ImageSaveNode::rosShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
