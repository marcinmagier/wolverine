
#include "qtconfig.h"
#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>



//Read all qobj properties using QSettings qset
void QtConfig::loadGroup(QSettings &qset, QObject *qobj)
{
    const QMetaObject* metaObject = qobj->metaObject();
    const QString group_name = metaObject->className();

    qset.beginGroup(group_name);
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i) {
        QMetaProperty objProp = metaObject->property(i);
        QVariant val = qset.value(objProp.name());
        objProp.write(qobj, val);
    }
    qset.endGroup();
}

//Write all qobj properties using QSettings qset
void QtConfig::saveGroup(QSettings &qset, QObject *qobj)
{
    const QMetaObject* metaObject = qobj->metaObject();
    const QString group_name = metaObject->className();

    qset.beginGroup(group_name);
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i) {
        QMetaProperty objProp = metaObject->property(i);
        QVariant val = objProp.read(qobj);
        qset.setValue(objProp.name(), val);
    }
    qset.endGroup();
}

//Copy all properties - backup
void QtConfig::copyGroup(QObject *to, const QObject *from)
{
    const QMetaObject *metaObjectFrom = from->metaObject();
    const QMetaObject *metaObjectTo = to->metaObject();

    if(metaObjectFrom != metaObjectTo)
        return;  //Different objects, bug

    for(int i = metaObjectFrom->propertyOffset(); i < metaObjectFrom->propertyCount(); ++i) {
        QMetaProperty objPropFrom = metaObjectFrom->property(i);
        QMetaProperty objPropTo = metaObjectTo->property(i);
         //Copy property
        QVariant val = objPropFrom.read(from);
        objPropTo.write(to, val);
    }
}
