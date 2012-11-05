

#include "qtactionmanager.h"
#include "qtactionmanager_impl.h"
#include "qtactionmanagerwidget.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>


QtActionManager* QtActionManager::s_actionManager = 0;



QtActionManager::QtActionManager()
{
    m_actionManager = new Impl::QtActionManager();
    m_actionManagerBackup = 0;
}


QtActionManager::~QtActionManager()
{
    if(m_actionManagerBackup)
        delete m_actionManagerBackup;
    delete m_actionManager;
}

QtActionManager* QtActionManager::instance()
{
    if(s_actionManager == 0)
        s_actionManager = new QtActionManager();
    return s_actionManager;
}


void QtActionManager::addAction(QAction *action)
{
    m_actionManager->addAction("Default", action);
}

void QtActionManager::addAction(const QString &category, QAction *action)
{
    m_actionManager->addAction(category, action);
}


void QtActionManager::saveConfig()
{
    m_actionManager->saveConfig();
}

void QtActionManager::restoreConfig()
{
    m_actionManager->restoreConfig();
}

void QtActionManager::createConfigurationBackup()
{
    if(m_actionManagerBackup)
        delete m_actionManagerBackup;
    m_actionManagerBackup = new Impl::QtActionManager(*m_actionManager);

}

void QtActionManager::restoreConfigurationBackup()
{
    if(m_actionManagerBackup == 0)
        return;

     //TODO: Add quards against threading
    Impl::QtActionManager *tmp = m_actionManager;
    m_actionManager = m_actionManagerBackup;
    delete tmp;
    m_actionManagerBackup = 0;
}

void QtActionManager::dropConfigurationBackup()
{
    if(m_actionManagerBackup) {
        delete m_actionManagerBackup;
        m_actionManagerBackup = 0;
    }
}


void QtActionManager::setCurrentScheme(const QString &name)
{
   m_actionManager->setCurrentScheme(name);
}



QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(m_actionManager, parent);
}
