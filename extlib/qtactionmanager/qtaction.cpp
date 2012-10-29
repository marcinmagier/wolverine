
#include "qtaction.h"



QtAction::QtAction()
{
    this->action = 0;
    this->schemeBinding["Default"] = "";
}

QtAction::QtAction(QAction *action)
{
    this->action = action;
    this->schemeBinding["Default"] = action->shortcut().toString();
}

QtAction::QtAction(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
}

QtAction& QtAction::operator =(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
    return *this;
}

QString QtAction::shortcut(QString scheme)
{
    return this->schemeBinding[scheme];
}

QStringList QtAction::createBindingList()
{
    QStringList tmpList;
    foreach(QString scheme, schemeBinding.keys()) {
        QString binding = schemeBinding.value(scheme);
        if(!binding.isEmpty())
             // Example Default:Ctrl+H
            tmpList.append(scheme + ":" + binding);
    }
    return tmpList;
}

void QtAction::applyBindingList(const QStringList &list)
{
     //In order not to create new schemes build tmpMap
    QMap<QString, QString> tmpMap;
    foreach(QString schemeBinding, list) {
        QStringList list = schemeBinding.split(":");
         //Example:
         //list[0] - Default
         //list[1] - Ctrl+H
         //Make sure value is a QKeySequence
        tmpMap[list[0]] = QKeySequence(list[1]).toString();
    }

     //apply only existed schemes
    foreach(QString scheme, schemeBinding.keys()) {
        schemeBinding[scheme] = tmpMap[scheme];
    }
}
