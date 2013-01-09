/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms
**  of the GNU General Public License as published by the Free Software Foundation,
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       qtmanagedmenu.cpp
 *  @brief      QtManagedMenu class implementation.
 */

#include "qtmanagedmenu.h"
#include "qtmanagedwidgetsdialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


#define QT_MANAGEDMENU_ICON_CUSTOMIZE	":/qtmanagedwidgets/customize.png"


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
QtManagedMenu::QtManagedMenu(QWidget *parent) :
    QMenu(parent)
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
QtManagedMenu::QtManagedMenu(QWidget *parent, const QString &toolbarName) :
    QMenu(parent)
{ 
    initialize(toolbarName);
}


/**
 *  Sets fields to their default values.
 *
 * @param name
 */
void QtManagedMenu::initialize(const QString &name)
{
    mMenuName = name;
    mActionsAvailable.clear();
    mIsManagerEnabled = true;
}


/**
 *  Adds action into toolbar.
 *
 * @param name
 * @param action
 */
void QtManagedMenu::addActiona(const QString &name, QAction *action)
{
    addActionAvailable(name, action);
    QMenu::addAction(action);
}




QAction* QtManagedMenu::exec()
{
    if(mIsManagerEnabled) {
        QAction *action = QMenu::addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDMENU_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
    }
    return QMenu::exec();
}


QAction* QtManagedMenu::exec(const QPoint &pos, QAction *at)
{
    if(mIsManagerEnabled) {
        QAction *action = QMenu::addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDMENU_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
    }
    return QMenu::exec(pos, at);
}


/**
 *  Shows dialog where we can customize toolbar's items.
 */
void QtManagedMenu::showManagerDialog()
{
    QtManagedWidgetsDialog dlg(this);
    QStringList tmpActionsVisible = createConfiguration();

    if(dlg.exec(&mActionsAvailable, &tmpActionsVisible)) {
        applyConfiguration(tmpActionsVisible);
        saveConfig(tmpActionsVisible);
    }
}


/**
 *  Creates and saves items that are currently available on toolbar.
 */
void QtManagedMenu::saveConfig()
{
    QStringList actionsVisible = createConfiguration();
    saveConfig(actionsVisible);
}


/**
 * Saves given configuration to the file.
 *
 * @param actionNames
 */
void QtManagedMenu::saveConfig(const QStringList &actionNames)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "menus");

    if (!qset.isWritable())
        return;

    qset.setValue(mMenuName, QVariant::fromValue(actionNames));
}


/**
 *  Reads configuration from the file and apply it.
 */
void QtManagedMenu::restoreConfig()
{

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "menus");
    QVariant var = qset.value(mMenuName);
    QStringList actionNames = var.toStringList();

    applyConfiguration(actionNames);
}


/**
 * Stores \a action in \a mActionsAvailable map. Provides default name if necessary.
 *
 * @param name
 * @param action
 */
void QtManagedMenu::addActionAvailable(const QString &name, QAction *action)
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
void QtManagedMenu::applyConfiguration(const QStringList &actionNames)
{
    if(actionNames.size() == 0)
        return;

    clear();
    foreach(QString name, actionNames) {
        if(name == "Separator") {
            QMenu::addSeparator();
            continue;
        }
        if(mActionsAvailable.contains(name))
            QMenu::addAction(mActionsAvailable[name]);
    }
}


/**
 * Creates list of items that are currently available on toolbar.
 *
 * @return
 */
QStringList QtManagedMenu::createConfiguration()
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


