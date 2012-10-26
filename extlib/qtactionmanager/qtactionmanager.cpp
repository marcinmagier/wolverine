
#include "qtactionmanager.h"
#include "qtactionmanagerwidget.h"

#include <QObject>
#include <QAction>


QtActionManager* QtActionManager::s_actionManager = 0;



QtAction::QtAction(QAction *action)
{
    this->action = action;
    this->schemeBinding["Default"] = action->shortcut().toString();
}

QtAction::QtAction(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
}

QtAction& QtAction::operator =(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
    return *this;
}



QtActionManager::QtActionManager()
{
    m_currentScheme = "Default";
    m_schemes.append("Default");
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
    QtAction qtAction(action);
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
            QtAction &qtaction = qtactions[i];
            QKeySequence shortcut = qtaction.schemeBinding[m_currentScheme];
            qtaction.action->setShortcut(shortcut);
        }
    }

}



QWidget* QtActionManager::getActionManagerWidget(QWidget *parent)
{
    return new QtActionManagerWidget(this, parent);
}
