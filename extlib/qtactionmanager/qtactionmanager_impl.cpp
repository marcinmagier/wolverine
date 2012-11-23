/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanager_impl.cpp
 *  @brief      Impl::QtActionManager class implementation.
 */


#include "qtactionmanager_impl.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>


using namespace Impl;




/**
 *  Default constructor.
 */
QtActionManager::QtActionManager()
{
    mCurrentScheme = "Default";
    mSchemes.append("Default");
}


/**
 *  Copy constructor.
 *
 * @param other
 */
QtActionManager::QtActionManager(const QtActionManager &other)
{
    foreach(QString category, other.mActionCategories.keys()) {
        QtActionsMap qtactions = other.mActionCategories.value(category);
        QtActionsMap tmp;

        foreach(QString name, qtactions.keys()) {
            QtAction *action = qtactions[name];
            QtAction *newAction = new QtAction(*action);
            tmp[name] = newAction;
        }

        this->mActionCategories[category] = tmp;
    }
    this->mCurrentScheme = other.mCurrentScheme;
    this->mSchemes = other.mSchemes;
}


/**
 *  Destructor.
 */
QtActionManager::~QtActionManager()
{
    foreach(QString category, mActionCategories.keys()) {
        QtActionsMap qtactions = mActionCategories.value(category);

        foreach(QString name, qtactions.keys()) {
            QtAction *action = qtactions[name];
            delete action;
        }
    }

}


/**
 *  Adds action to the \a group.
 *
 * @param group
 * @param name
 * @param action
 */
void QtActionManager::addAction(const QString &group, const QString &name, QAction *action)
{
    QtAction *qtAction = new QtAction(action);
    mActionCategories[group].insert(name, qtAction);
}


/**
 *  Retrieves action.
 *
 * @param group
 * @param name
 * @return
 */
QAction* QtActionManager::getAction(const QString &group, const QString &name)
{
    QtActionsMap qtactions = mActionCategories[group];
    QtAction *qtAction = qtactions[name];
    return qtAction->action;
}


/**
 *  Saves current configuration of key binding.
 */
void QtActionManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "actionbinding");

    if(!qset.isWritable())
        return;

    foreach(QString category, mActionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsMap qtactions = mActionCategories.value(category);

        foreach(QString name, qtactions.keys()) {
            QtAction *qtAction = qtactions[name];
            QStringList tmpConfig = qtAction->createBindingList();
            qset.setValue(name, QVariant::fromValue(tmpConfig));
        }
        qset.endGroup();
    }
}


/**
 *  Reads saved configuration of key binding and applies it.
 */
void QtActionManager::restoreConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "actionbinding");

    //Read only valid values, ommit not existed actions/schemes etc.
    foreach(QString category, mActionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsMap qtactions = mActionCategories.value(category);
        foreach(QString name, qtactions.keys()) {
            QtAction *qtAction = qtactions[name];
            QVariant var = qset.value(name);
            QStringList tmpConfig = var.toStringList();
            if(!tmpConfig.isEmpty())
                qtAction->applyBindingList(tmpConfig);
        }
        qset.endGroup();
    }
    //Reload shortcuts for current scheme
    setCurrentScheme(mCurrentScheme);
}


/**
 *  Creates new builtin scheme. User cannot delete it.
 *
 * @param name
 */
void QtActionManager::addScheme(const QString &name)
{
    if(!mSchemes.contains(name))
        mSchemes.append(name);

    setCurrentScheme(name);
}


/**
 *  Reconfigures actions in accordance with given scheme.
 *
 * @param name
 */
void QtActionManager::setCurrentScheme(const QString &name)
{
    if(!mSchemes.contains(name))
        return;

    mCurrentScheme = name;

    foreach(QString category, mActionCategories.keys()) {
        QtActionsMap qtactions = mActionCategories.value(category);

        foreach(QString actionName, qtactions.keys()) {
            QtAction *qtAction = qtactions[actionName];
            QKeySequence shortcut = qtAction->shortcut(mCurrentScheme);
            qtAction->action->setShortcut(shortcut);
        }
    }

}


/**
 *  Retrieves current scheme.
 *
 * @return
 */
QString QtActionManager::getCurrentScheme()
{
    return mCurrentScheme;
}



