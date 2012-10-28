

#include "qtactionmanager.h"
#include "qtactionmanagerwidget.h"
#include "qtaction.h"

#include <QObject>
#include <QAction>


QtActionManager* QtActionManager::s_actionManager = 0;



QtActionManager::QtActionManager()
{
    m_currentScheme = "Default";
    m_schemes.append("Default");
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

QtActionManager* QtActionManager::instance()
{
    if(s_actionManager == 0)
        s_actionManager = new QtActionManager();
    return s_actionManager;
}


void QtActionManager::addAction(QAction *action)
{
    addAction("Default", action);
}

void QtActionManager::addAction(const QString &category, QAction *action)
{
    QtAction *qtAction = new QtAction(action);
    m_actionCategories[category].append(qtAction);
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



QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(this, parent);
}
