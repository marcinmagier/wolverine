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
 *  @file       WPanel.cpp
 *  @brief      Wolverine::Panel class implementation.
 */

#include "WActionManager.h"
#include "WDocument.h"
#include "WEditor.h"
#include "WPanel.h"
#include "WPanelTabBar.h"

#include <QContextMenuEvent>
#include <QDebug>


#define W_ACTION_MOVE_TAB "MoveTab"


using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
Panel::Panel(Position position, QWidget *parent) :
    QtTabWidget(parent)
{
    mTabBar = new PanelTabBar(this);
    this->setTabBar(mTabBar);

    connect( mTabBar, SIGNAL(scrollButtonsHiddenChanged(bool)),
                this, SLOT(setListButtonHidden(bool)) );


    QAction *action;
    ActionManager *actionManager = ActionManager::instance();
    mMenu = new QtManagedMenu(this, "TabWidgetMenu");
    action = actionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE);
    mMenu->addAction(W_ACTION_CLOSE, action);
    action = actionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_OTHERS);
    mMenu->addAction(W_ACTION_CLOSE_OTHERS, action);
    action = actionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_ALL);
    mMenu->addAction(W_ACTION_CLOSE_ALL, action);
    mMenu->addSeparator();
    if(position == Panel::LeftPanel) {
        action = actionManager->getAction(W_ACTION_GROUP_MISC, W_ACTION_MOVE_RIGHT);
        mMenu->addAction(W_ACTION_MOVE_TAB, action);
    } else {
        action = actionManager->getAction(W_ACTION_GROUP_MISC, W_ACTION_MOVE_LEFT);
        mMenu->addAction(W_ACTION_MOVE_TAB, action);
    }

    mMenu->restoreConfig();


}


/**
 *  Destructor
 */
Panel::~Panel()
{
    delete mTabBar;
    delete mMenu;
}


int Panel::addTab(Editor *editor)
{
    Document *doc = editor->getDocument();

    return QtTabWidget::addTab(editor, doc->getIcon(), doc->fileName());
}




void Panel::contextMenuEvent(QContextMenuEvent *event)
{
        qDebug() << mTabBar->tabAt(event->pos());
        mMenu->exec(event->globalPos());
}
