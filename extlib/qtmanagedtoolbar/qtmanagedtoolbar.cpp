
#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


#define QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE	":/qtmanagedtoolbar/customize.png"




QtManagedToolBar::QtManagedToolBar(QWidget *parent, QString toolbarName) :
    QToolBar(parent), m_toolbarName(toolbarName)
{ 
    m_actionsAvailable.clear();
    m_isManagerEnabled = true;
}


void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_isManagerEnabled) {
        QMenu *contextMenu = new QMenu(this);
        QAction *action = contextMenu->addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));

        contextMenu->exec(event->globalPos());

        delete contextMenu;
    }
}

void QtManagedToolBar::showContextMenu(QContextMenuEvent *event, QMenu *menu)
{
	if(m_isManagerEnabled) {
		QAction *action = menu->addAction(tr("Customize"));
		action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
		connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
	}

	menu->exec(event->globalPos());
}


void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    dlg.actionsAvailable = &m_actionsAvailable;
    QStringList tmpActionsVisible = createConfiguration();
    dlg.actionsVisible = &tmpActionsVisible;

    if(dlg.exec()) {
        applyConfiguration(tmpActionsVisible);
        saveConfig(tmpActionsVisible);
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
    QStringList actionsVisible = createConfiguration();
    saveConfig(actionsVisible);
}

void QtManagedToolBar::saveConfig(QStringList &actionList)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");

    if (!qset.isWritable())
        return;

    qset.setValue(m_toolbarName, QVariant::fromValue(actionList));
}



void QtManagedToolBar::findActionsAvailable()
{
    QList<QAction*> tmp = this->actions();
	m_actionsAvailable.clear();

    //Currently we only remove separators
    //We assume that actions with the same name won't be added
    foreach(QAction *action, tmp) {
    	if(action->isSeparator())
    		continue;
    	m_actionsAvailable.append(action);
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


