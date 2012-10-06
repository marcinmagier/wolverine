
#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


QtManagedToolBar::QtManagedToolBar(QWidget *parent, QString toolbarName) :
    QToolBar(parent), m_toolbarName(toolbarName)
{ 
    m_actionsAvailable.clear();
    m_isManagerEnabled = true;
    contextMenu = 0;
}


void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    bool isLocalMenu = false;

    if(m_isManagerEnabled) {
        if(!contextMenu) {
            //There is no menu created by successor, create it for "Customize" item
            contextMenu = new QMenu(this);
            isLocalMenu = true;
        }
        QAction *action = contextMenu->addAction(tr("Customize"));
        action->setIcon(QIcon(":/qtmanagedtoolbar/customize.png"));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
    }

    if(contextMenu)
        contextMenu->exec(event->globalPos());

    if(isLocalMenu) {
        delete contextMenu;
        contextMenu = 0;
    }
}


void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    dlg.actionsAvailable = &m_actionsAvailable;
    QStringList tmpActionsVisible = createConfiguration();
    dlg.actionsVisible = &tmpActionsVisible;

    if(dlg.exec()) {
        applyConfiguration(tmpActionsVisible);
    }
}


void QtManagedToolBar::restoreConfig()
{
    findActionsAvailable();

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");
    QVariant var = qset.value(m_toolbarName);
    QStringList list = var.toStringList();

    applyConfiguration(list);
}


void QtManagedToolBar::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");

    if (!qset.isWritable())
        return;

    QStringList actionList = createConfiguration();
    qset.setValue(m_toolbarName, QVariant::fromValue(actionList));
}



void QtManagedToolBar::findActionsAvailable()
{
    QList<QAction*> tmp = this->actions();

    //Currently we only remove separators
    //We assume that acctions with the same name wan't be added
    //TODO: Add removing dupplicates if necessary.
    for (int i=0; i< tmp.size(); ++i) {
        if (tmp.at(i)->isSeparator())
            continue;
        m_actionsAvailable.append(tmp.at(i));
    }
}


QAction* QtManagedToolBar::getActionFromString(const QString &name)
{
    for (int i=0; i<m_actionsAvailable.size(); ++i) {
        if (m_actionsAvailable.at(i)->text() == name)
            return m_actionsAvailable.at(i);
    }

    return 0;
}

void QtManagedToolBar::applyConfiguration(const QStringList &config)
{
    clear();
    for (int i=0; i<config.size(); ++i) {
        if(config.at(i) == "Separator") {
            addSeparator();
            continue;
        }
        QAction *action = getActionFromString(config.at(i));
        if (action != 0)
            addAction(action);
    }
}

QStringList QtManagedToolBar::createConfiguration()
{
    QStringList list;
    QList<QAction*> actions = this->actions();

    for (int i=0; i<actions.size(); ++i) {
        if (actions.at(i)->isSeparator()) {
            list.append("Separator");
            continue;
        }
        list.append( actions.at(i)->text() );
    }
    return list;
}


