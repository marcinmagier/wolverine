


#include "qtactionmanager_impl.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>
#include <QSettings>
#include <QApplication>


using namespace Impl;



QtActionManager::QtActionManager()
{
    m_currentScheme = "Default";
    m_schemes.append("Default");
}

QtActionManager::QtActionManager(const QtActionManager &other)
{
    foreach(QString category, other.m_actionCategories.keys()) {
        QtActionsList qtactions = other.m_actionCategories.value(category);
        QtActionsList tmp;

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QtAction *newAction = new QtAction(*qtAction);
            tmp.append(newAction);
        }
        this->m_actionCategories[category] = tmp;
    }
    this->m_currentScheme = other.m_currentScheme;
    this->m_schemes = other.m_schemes;
}

QtActionManager::~QtActionManager()
{
    foreach(QString category, m_actionCategories.keys()) {
        QtActionsList qtactions = m_actionCategories.value(category);

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            delete qtAction;
        }
    }

}


void QtActionManager::addAction(const QString &category, QAction *action)
{
    QtAction *qtAction = new QtAction(action);
    m_actionCategories[category].append(qtAction);
}


void QtActionManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "actionbinding");

    if(!qset.isWritable())
        return;

    foreach(QString category, m_actionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsList qtactions = m_actionCategories.value(category);
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
    foreach(QString category, m_actionCategories.keys()) {
        qset.beginGroup(category);
        QtActionsList qtactions = m_actionCategories.value(category);
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
    setCurrentScheme(m_currentScheme);
}


void QtActionManager::setCurrentScheme(const QString &name)
{
    if(!m_schemes.contains(name))
        m_schemes.append(name);

    m_currentScheme = name;

    foreach(QString category, m_actionCategories.keys()) {
        QtActionsList qtactions = m_actionCategories.value(category);

        for(int i=0; i<qtactions.length(); ++i) {
            QtAction *qtAction = qtactions[i];
            QKeySequence shortcut = qtAction->shortcut(m_currentScheme);
            qtAction->action->setShortcut(shortcut);
        }
    }

}
