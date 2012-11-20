/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/


#include "qtactionmanager.h"
#include "qtactionmanager_impl.h"
#include "qtactionmanagerwidget.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>



//*************************************************************************************************
/** \brief  Default constructor.
*
**************************************************************************************************/
QtActionManager::QtActionManager()
{
    mActionManagerImpl = new Impl::QtActionManager();
    mActionManagerImplBackup = 0;
}


//*************************************************************************************************
/** \brief  Default destructor.
*
**************************************************************************************************/
QtActionManager::~QtActionManager()
{
    if(mActionManagerImplBackup)
        delete mActionManagerImplBackup;
    delete mActionManagerImpl;
}


//*************************************************************************************************
/** \brief  Adds \a action to \a group.
*
*   Parameters \a group and \a name are not translated
**************************************************************************************************/
void QtActionManager::addAction(const QString &group, const QString &name, QAction *action)
{
    mActionManagerImpl->addAction(group, name, action);
}


//*************************************************************************************************
/** \brief  Retrieves action
*
*   Parameters \a group and \a name are not translated
**************************************************************************************************/
QAction* QtActionManager::getAction(const QString &group, const QString &name)
{
    return mActionManagerImpl->getAction(group, name);
}


//*************************************************************************************************
/** \brief  Saves configuration.
*
**************************************************************************************************/
void QtActionManager::saveConfig()
{
    mActionManagerImpl->saveConfig();
}


//*************************************************************************************************
/** \brief  Restrores configuration.
*
**************************************************************************************************/
void QtActionManager::restoreConfig()
{
    mActionManagerImpl->restoreConfig();
}


//*************************************************************************************************
/** \brief  Creates backup of current configuration.
*
**************************************************************************************************/
void QtActionManager::createConfigurationBackup()
{
    if(mActionManagerImplBackup)
        delete mActionManagerImplBackup;
    mActionManagerImplBackup = new Impl::QtActionManager(*mActionManagerImpl);

}


//*************************************************************************************************
/** \brief  Restores saved configuration
*
**************************************************************************************************/
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


//*************************************************************************************************
/** \brief  Throws saved configuration away
*
**************************************************************************************************/
void QtActionManager::dropConfigurationBackup()
{
    if(mActionManagerImplBackup) {
        delete mActionManagerImplBackup;
        mActionManagerImplBackup = 0;
    }
}


//*************************************************************************************************
/** \brief  Adds new shortcuts binding scheme
*
**************************************************************************************************/
void QtActionManager::addScheme(const QString &name)
{
    mActionManagerImpl->addScheme(name);
}


//*************************************************************************************************
/** \brief  Changes current scheme
*
**************************************************************************************************/
void QtActionManager::setScheme(const QString &name)
{
    mActionManagerImpl->setCurrentScheme(name);
}


//*************************************************************************************************
/** \brief  Retrieves current binding scheme
*
**************************************************************************************************/
QString QtActionManager::getScheme()
{
    return mActionManagerImpl->getCurrentScheme();
}


//*************************************************************************************************
/** \brief  Creates and returns widget for binding manipulation
*
**************************************************************************************************/
QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(mActionManagerImpl, parent);
}
