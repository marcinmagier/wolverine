
#include "qtactionmanager.h"
#include "qtactionmanagerwidget.h"

#include <QAction>



void QtActionManager::addAction(QAction *action)
{
    addAction("Default", action);
}

void QtActionManager::addAction(const QString &group, QAction *action)
{
    m_actionGroups[group].insert(action->text(), action);
}

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
    QMutableMapIterator<QString, QActionMapper> i(m_actionGroups);
    while(i.hasNext()) {
        i.next();

        QActionMapper &mapper = i.value();
        mapper.remove(name);

        if(mapper.empty())
            i.remove();
    }
}


QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(m_actionGroups, parent);
}
