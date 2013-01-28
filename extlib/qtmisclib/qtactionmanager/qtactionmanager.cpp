/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanager.cpp
 *  @brief      QtActionManager class implementation.
 */


#include "qtactionmanager.h"
#include "qtactionmanager_impl.h"
#include "qtactionmanagerwidget.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>




/**
 *  Default constructor.
 */
QtActionManager::QtActionManager()
{
    mActionManagerImpl = new Impl::QtActionManager();
    mActionManagerImplBackup = 0;
}


/**
 *  Default destructor.
 */
QtActionManager::~QtActionManager()
{
    if(mActionManagerImplBackup)
        delete mActionManagerImplBackup;
    delete mActionManagerImpl;
}


/**
 *  Adds \a action to \a group.
 *
 *  Parameters \a group and \a name are not translated
 *
 * @param group
 * @param name
 * @param action
 */
void QtActionManager::addAction(const QString &group, const QString &name, QAction *action)
{
    mActionManagerImpl->addAction(group, name, action);
}


/**
 *  Retrieves action.
 *
 *  Parameters \a group and \a name are not translated
 *
 * @param group
 * @param name
 * @return
 */
QAction* QtActionManager::getAction(const QString &group, const QString &name)
{
    return mActionManagerImpl->getAction(group, name);
}


/**
 *  Saves configuration.
 */
void QtActionManager::saveConfig()
{
    mActionManagerImpl->saveConfig();
}


/**
 *  Restores configuration.
 */
void QtActionManager::restoreConfig()
{
    mActionManagerImpl->restoreConfig();
}


/**
 *  Creates backup of current configuration.
 */
void QtActionManager::createConfigurationBackup()
{
    if(mActionManagerImplBackup)
        delete mActionManagerImplBackup;
    mActionManagerImplBackup = new Impl::QtActionManager(*mActionManagerImpl);

}


/**
 *  Restores saved configuration.
 */
void QtActionManager::restoreConfigurationBackup()
{
    if(mActionManagerImplBackup == 0)
        return;

     //TODO: Add guards against threading
    Impl::QtActionManager *tmp = mActionManagerImpl;
    mActionManagerImpl = mActionManagerImplBackup;
    delete tmp;
    mActionManagerImplBackup = 0;
}


/**
 *  Throws saved configuration away.
 */
void QtActionManager::dropConfigurationBackup()
{
    if(mActionManagerImplBackup) {
        delete mActionManagerImplBackup;
        mActionManagerImplBackup = 0;
    }
}


/**
 *  Adds new shortcuts binding scheme.
 *
 * @param name
 */
void QtActionManager::addScheme(const QString &name)
{
    mActionManagerImpl->addScheme(name);
}


/**
 *  Changes current scheme.
 *
 * @param name
 */
void QtActionManager::setScheme(const QString &name)
{
    mActionManagerImpl->setCurrentScheme(name);
}


/**
 *  Retrieves current binding scheme.
 *
 * @return  Name of current scheme.
 */
QString QtActionManager::getScheme()
{
    return mActionManagerImpl->getCurrentScheme();
}


/**
 *  Creates and returns widget for binding manipulation.
 *
 * @param parent
 * @return
 */
QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(mActionManagerImpl, parent);
}
