/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtmanagedtoolbar.cpp
 *  @brief      QtManagedToolbar class implementation.
 */

#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


#define QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE	":/qtmanagedtoolbar/customize.png"


static int defToolbarCount = 0;
static const QString defToolbarName = "NoNamedToolbar";

static int defItemCount = 0;
static const QString defItemName = "NoNamedItem";





/**
 *  Default constructor.
 *
 *  This constructor should not be used in reliable application. Always give a name for toolbar.
 *
 * @param parent
 */
QtManagedToolBar::QtManagedToolBar(QWidget *parent) :
    QToolBar(parent)
{
    // Calculate unique name to prevent future problems.
    QString toolbarName = defToolbarName + QString::number(defToolbarCount++);
    initialize(toolbarName);
}


/**
 *  Parametrized constructor. Creates named toolbar.
 *
 * @param parent
 * @param toolbarName
 */
QtManagedToolBar::QtManagedToolBar(QWidget *parent, const QString &toolbarName) :
    QToolBar(parent)
{ 
    initialize(toolbarName);
}


/**
 *  Sets fields to their default values.
 *
 * @param name
 */
void QtManagedToolBar::initialize(const QString &name)
{
    mToolbarName = name;
    mActionsAvailable.clear();
    mIsManagerEnabled = true;
}


/**
 *  Adds action into toolbar.
 *
 * @param name
 * @param action
 */
void QtManagedToolBar::addAction(const QString &name, QAction *action)
{
    addActionAvailable(name, action);
    QToolBar::addAction(action);
}


/**
 * Adds widget into toolbar.
 *
 * @param name
 * @param widget
 * @return
 */
QAction* QtManagedToolBar::addWidget(const QString &name, QWidget *widget)
{
    QAction *tmp = QToolBar::addWidget(widget);
    addActionAvailable(name, tmp);
    return tmp;
}


/**
 * Removes action from toolbar.
 *
 * @param action
 */
void QtManagedToolBar::removeAction(QAction *action)
{
    QString key = mActionsAvailable.key(action);
    if(!key.isEmpty()) {
        mActionsAvailable.remove(key);
        QToolBar::removeAction(action);
    }
}


/**
 *  Removes action from toolbar.
 *
 * @param name
 */
void QtManagedToolBar::removeAction(const QString &name)
{
    if(mActionsAvailable.contains(name)) {
        QAction *action = mActionsAvailable[name];
        mActionsAvailable.remove(name);
        QToolBar::removeAction(action);
    }
}


/**
 *  Creates and shows context menu.
 *
 *  This function is used when child class doesn't define context menu. Menu is only shown when
 *  manager is enabled.
 *
 * @param event
 */
void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    if(mIsManagerEnabled) {
        QMenu *contextMenu = new QMenu(this);
        QAction *action = contextMenu->addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));

        contextMenu->exec(event->globalPos());

        delete contextMenu;
        //check if action is deleted
    }
}


/**
 *  Adds \a Customize to the context menu and shows it.
 *
 *  Function is created to be invoked from child class. \a Customize item is only added when
 *  manager is enabled.
 *
 * @param event
 * @param menu
 */
void QtManagedToolBar::showContextMenu(QContextMenuEvent *event, QMenu *menu)
{
	if(mIsManagerEnabled) {
		QAction *action = menu->addAction(tr("Customize"));
		action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
		connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
	}

	menu->exec(event->globalPos());
}


/**
 *  Shows dialog where we can customize toolbar's items.
 */
void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    QStringList tmpActionsVisible = createConfiguration();

    if(dlg.exec(&mActionsAvailable, &tmpActionsVisible)) {
        applyConfiguration(tmpActionsVisible);
        saveConfig(tmpActionsVisible);
    }
}


/**
 *  Creates and saves items that are currently available on toolbar.
 */
void QtManagedToolBar::saveConfig()
{
    QStringList actionsVisible = createConfiguration();
    saveConfig(actionsVisible);
}


/**
 * Saves given configuration to the file.
 *
 * @param actionNames
 */
void QtManagedToolBar::saveConfig(const QStringList &actionNames)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");

    if (!qset.isWritable())
        return;

    qset.setValue(mToolbarName, QVariant::fromValue(actionNames));
}


/**
 *  Reads configuration from the file and apply it.
 */
void QtManagedToolBar::restoreConfig()
{

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");
    QVariant var = qset.value(mToolbarName);
    QStringList actionNames = var.toStringList();

    applyConfiguration(actionNames);
}


/**
 * Stores \a action in \a mActionsAvailable map. Provides default name if necessary.
 *
 * @param name
 * @param action
 */
void QtManagedToolBar::addActionAvailable(const QString &name, QAction *action)
{
    if(action->text().isEmpty())
        // WARNING: It is wrong way to add actions without names
        action->setText( defItemName + QString::number(defItemCount++) );
    mActionsAvailable[name] = action;
}


/**
 * Reorganizes toolbar items according to \a actionNames.
 *
 * @param actionNames
 */
void QtManagedToolBar::applyConfiguration(const QStringList &actionNames)
{
    if(actionNames.size() == 0)
        return;

    clear();
    foreach(QString name, actionNames) {
        if(name == "Separator") {
            QToolBar::addSeparator();
            continue;
        }
        if(mActionsAvailable.contains(name))
            QToolBar::addAction(mActionsAvailable[name]);
    }
}


/**
 * Creates list of items that are currently available on toolbar.
 *
 * @return
 */
QStringList QtManagedToolBar::createConfiguration()
{
    QStringList actionNames;
    QList<QAction*> actions = this->actions();

    foreach(QAction *action, actions) {
        if(action->isSeparator()) {
            actionNames.append("Separator");
            continue;
        }
        QString name = mActionsAvailable.key(action);
        if(!name.isEmpty())
            actionNames.append(name);
    }
    return actionNames;
}


