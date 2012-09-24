
#include "Settings.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>


//Read all qobj properties using QSettings qset
void Settings::readGroup(QSettings &qset, QObject *qobj)
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
void Settings::writeGroup(QSettings &qset, QObject *qobj)
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
