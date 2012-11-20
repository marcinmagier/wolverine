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



QtActionManager::QtActionManager()
{
    mCurrentScheme = "Default";
    mSchemes.append("Default");
}

QtActionManager::QtActionManager(const QtActionManager &other)
{
    foreach(QString category, other.mActionCategories.keys()) {
        QtActionsMap qtactions = other.mActionCategories.value(category);
        QtActionsMap tmp;

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QtAction *newAction = new QtAction(*qtAction);
            tmp.append(newAction);
        }
        this->mActionCategories[category] = tmp;
    }
    this->mCurrentScheme = other.mCurrentScheme;
    this->mSchemes = other.mSchemes;
}

QtActionManager::~QtActionManager()
{
    foreach(QString category, mActionCategories.keys()) {
        QtActionsMap qtactions = mActionCategories.value(category);

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            delete qtAction;
        }
    }

}


void QtActionManager::addAction(const QString &group, const QString &name, QAction *action)
{
    QtAction *qtAction = new QtAction(action);
    mActionCategories[group].append(qtAction);
}

QAction* QtActionManager::getAction(const QString &group, const QString &name)
{
    //FIXME:
    return 0;
}

void QtActionManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "actionbinding");

    if(!qset.isWritable())
        return;

    foreach(QString category, mActionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsMap qtactions = mActionCategories.value(category);
        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QStringList tmpList = qtAction->createBindingList();
            qset.setValue(qtAction->action->text(), QVariant::fromValue(tmpList));
        }
        qset.endGroup();
    }
}

void QtActionManager::restoreConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "actionbinding");

    //Read only valid values, ommit not existed actions/schemes etc.
    foreach(QString category, mActionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsMap qtactions = mActionCategories.value(category);
        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QVariant var = qset.value(qtAction->action->text());
            QStringList tmpList = var.toStringList();
            if(!tmpList.isEmpty())
                qtAction->applyBindingList(tmpList);
        }
        qset.endGroup();
    }
    //Reload shortcuts for current scheme
    setCurrentScheme(mCurrentScheme);
}


void QtActionManager::addScheme(const QString &name)
{

}

void QtActionManager::addUserScheme(const QString &name)
{

}

void QtActionManager::removeUserScheme(const QString &name)
{

}


void QtActionManager::setCurrentScheme(const QString &name)
{
    if(!mSchemes.contains(name))
        mSchemes.append(name);

    mCurrentScheme = name;

    foreach(QString category, mActionCategories.keys()) {
        QtActionsMap qtactions = mActionCategories.value(category);

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QKeySequence shortcut = qtAction->shortcut(mCurrentScheme);
            qtAction->action->setShortcut(shortcut);
        }
    }

}

QString QtActionManager::getCurrentScheme()
{
    return "FIXME";
}



