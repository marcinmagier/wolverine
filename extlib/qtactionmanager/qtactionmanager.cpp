
#include "qtactionmanager.h"
#include "qtactionmanagerwidget.h"

#include <QAction>


QtActionManager* QtActionManager::s_actionManager = 0;

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

void QtActionManager::addAction(const QString &group, QAction *action)
{
    m_actionGroups[group].insert(action->text(), action);

    QMutableMapIterator<QString, QMapBindingGroupName> scheme(m_actionSchemes);
    while(scheme.hasNext()) {
        scheme.next();
        scheme.value()[group].insert(action->text(), action->shortcut().toString());
    }
}

/*
void QtActionManager::removeAction(const QString &name)
{
    removeAction("Default", name);
}

void QtActionManager::removeAction(const QString &group, const QString &name)
{
    m_actionGroups[group].remove(name);
    if(m_actionGroups[group].empty())
        m_actionGroups.remove(group);
}

void QtActionManager::removeAll(const QString &name)
{
    QMutableMapIterator<QString, QMapActionName> i(m_actionGroups);
    while(i.hasNext()) {
        i.next();

        QMapActionName &mapper = i.value();
        mapper.remove(name);

        if(mapper.empty())
            i.remove();
    }
}
*/

QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(this, parent);
}
