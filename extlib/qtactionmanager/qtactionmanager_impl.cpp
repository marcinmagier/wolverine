/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/


#include "qtactionmanager_impl.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>


using namespace Impl;



//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
QtActionManager::QtActionManager()
{
    mCurrentScheme = "Default";
    mSchemes.append("Default");
}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
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
    this->mUserSchemes = other.mUserSchemes;
}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
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


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::addAction(const QString &group, const QString &name, QAction *action)
{
    QtAction *qtAction = new QtAction(action);
    mActionCategories[group].insert(name, qtAction);
}

QAction* QtActionManager::getAction(const QString &group, const QString &name)
{
    QtActionsMap qtactions = mActionCategories[group];
    QtAction *qtAction = qtactions[name];
    return qtAction->action;
}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
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


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
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


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::addScheme(const QString &name)
{

}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::addUserScheme(const QString &name)
{

}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::removeUserScheme(const QString &name)
{

}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::setCurrentScheme(const QString &name)
{
    if(!mSchemes.contains(name))
        mSchemes.append(name);

    mCurrentScheme = name;

    foreach(QString category, mActionCategories.keys()) {
        QtActionsMap qtactions = mActionCategories.value(category);

        foreach(QString name, qtactions.keys()) {
            QtAction *qtAction = qtactions[name];
            QKeySequence shortcut = qtAction->shortcut(mCurrentScheme);
            qtAction->action->setShortcut(shortcut);
        }
    }

}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
QString QtActionManager::getCurrentScheme()
{
    return "FIXME";
}



