
#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


#define QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE	":/qtmanagedtoolbar/customize.png"


static int defToolbarCount = 0;
static const QString defToolbarName = "NoNamedToolbar";


QtManagedToolBar::QtManagedToolBar(QWidget *parent) :
    QToolBar(parent)
{
    //This constructor should not be used in reliable application
    //Calculate unique name to prevent future problems
    QString toolbarName = defToolbarName + QString::number(defToolbarCount);
    defToolbarCount++;
    init(toolbarName);
}

QtManagedToolBar::QtManagedToolBar(QWidget *parent, const QString &toolbarName) :
    QToolBar(parent)
{ 
    init(toolbarName);
}

void QtManagedToolBar::init(const QString &name)
{
    m_toolbarName = name;
    m_actionsAvailable.clear();
    m_isManagerEnabled = true;
}




void QtManagedToolBar::addAction(QAction *action)
{
    m_actionsAvailable.append(action);
    QToolBar::addAction(action);
}

QAction* QtManagedToolBar::addAction(const QString &text)
{
    QAction *tmp = QToolBar::addAction(text);
    m_actionsAvailable.append(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QIcon &icon, const QString &text)
{
    QAction *tmp = QToolBar::addAction(icon, text);
    m_actionsAvailable.append(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QString &text, const QObject *receiver, const char* member)
{
    QAction *tmp = QToolBar::addAction(text, receiver, member);
    m_actionsAvailable.append(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char* member)
{
    QAction *tmp = QToolBar::addAction(icon, text, receiver, member);
    m_actionsAvailable.append(tmp);
    return tmp;
}


QAction* QtManagedToolBar::addWidget(QWidget *widget)
{
    QAction *tmp = QToolBar::addWidget(widget);
    m_actionsAvailable.append(tmp);
    return tmp;
}

QAction* QtManagedToolBar::insertWidget(QAction *before, QWidget *widget)
{
    QAction *tmp = QToolBar::insertWidget(before, widget);
    m_actionsAvailable.append(tmp);
    return tmp;
}


void QtManagedToolBar::addActions(QList<QAction*> actions)
{
    m_actionsAvailable.append(actions);
    QWidget::addActions(actions);
}

void QtManagedToolBar::insertAction(QAction *before, QAction *action)
{
    m_actionsAvailable.append(action);
    QWidget::insertAction(before, action);
}

void QtManagedToolBar::insertActions(QAction *before, QList<QAction*> actions)
{
    m_actionsAvailable.append(actions);
    QWidget::insertActions(before, actions);
}

void QtManagedToolBar::removeAction(QAction *action)
{
    m_actionsAvailable.removeAll(action);
    QWidget::removeAction(action);
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


QAction* QtManagedToolBar::getActionAvailableFromString(const QString &name)
{
    for (int i=0; i<m_actionsAvailable.size(); ++i) {
        if (m_actionsAvailable.at(i)->text() == name)
            return m_actionsAvailable.at(i);
    }

    return 0;
}

void QtManagedToolBar::applyConfiguration(const QStringList &config)
{
    if(config.size() == 0)
        return;

    clear();
    for (int i=0; i<config.size(); ++i) {
        if(config.at(i) == "Separator") {
            addSeparator();
            continue;
        }
        QAction *action = getActionAvailableFromString(config.at(i));
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


