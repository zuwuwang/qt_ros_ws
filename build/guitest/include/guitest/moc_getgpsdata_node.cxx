/****************************************************************************
** Meta object code from reading C++ file 'getgpsdata_node.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/guitest/include/guitest/getgpsdata_node.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getgpsdata_node.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_guitest__GetGpsDataNode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      42,   24,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_guitest__GetGpsDataNode[] = {
    "guitest::GetGpsDataNode\0\0loggingUpdated()\0"
    "rosShutdown()\0"
};

void guitest::GetGpsDataNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GetGpsDataNode *_t = static_cast<GetGpsDataNode *>(_o);
        switch (_id) {
        case 0: _t->loggingUpdated(); break;
        case 1: _t->rosShutdown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData guitest::GetGpsDataNode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject guitest::GetGpsDataNode::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_guitest__GetGpsDataNode,
      qt_meta_data_guitest__GetGpsDataNode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &guitest::GetGpsDataNode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *guitest::GetGpsDataNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *guitest::GetGpsDataNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_guitest__GetGpsDataNode))
        return static_cast<void*>(const_cast< GetGpsDataNode*>(this));
    return QThread::qt_metacast(_clname);
}

int guitest::GetGpsDataNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void guitest::GetGpsDataNode::loggingUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void guitest::GetGpsDataNode::rosShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
