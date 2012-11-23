/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtaction.cpp
 *  @brief      QtAction class implementation.
 */


#include "qtaction.h"




/**
 *  Default constructor.
 */
QtAction::QtAction()
{
    this->action = 0;
    this->schemeBinding["Default"] = "";
}


/**
 *  Parametrized constructor.
 *
 * @param action
 */
QtAction::QtAction(QAction *action)
{
    this->action = action;
    this->schemeBinding["Default"] = action->shortcut().toString();
}


/**
 *  Copy constructor.
 *
 * @param other
 */
QtAction::QtAction(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
}


/**
 *  Assignment operator.
 *
 * @param other
 * @return
 */
QtAction& QtAction::operator =(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
    return *this;
}


/**
 *  Retrieves shortcut for given scheme.
 *
 * @param scheme
 * @return
 */
QString QtAction::shortcut(QString scheme)
{
    return this->schemeBinding[scheme];
}


/**
 *  Creates binding list that can be written with QSettings.
 *
 * @return
 */
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


/**
 *  Configures action bindings according to the binding \a list.
 *
 * @param list
 */
void QtAction::applyBindingList(const QStringList &schemes, const QStringList &list)
{
    foreach(QString bindings, list) {
        QStringList list = bindings.split(":");
         //Example:
         //list[0] - Default
         //list[1] - Ctrl+H
         //apply only existed schemes
        if(schemes.contains(list[0]))
            //Make sure value is a QKeySequence
            schemeBinding[list[0]] = QKeySequence(list[1]).toString();
    }
}
