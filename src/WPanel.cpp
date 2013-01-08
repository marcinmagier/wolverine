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

#include "WDocument.h"
#include "WEditor.h"
#include "WPanel.h"
#include "WPanelTabBar.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>



using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
Panel::Panel(QWidget *parent) :
    QtTabWidget(parent)
{
    mTabBar = new PanelTabBar(this);
    this->setTabBar(mTabBar);

    connect( mTabBar, SIGNAL(scrollButtonsHiddenChanged(bool)),
                this, SLOT(setListButtonHidden(bool)) );

}


/**
 *  Destructor
 */
Panel::~Panel()
{
    delete mTabBar;
}


int Panel::addTab(Editor *editor)
{
    Document *doc = editor->getDocument();

    return QtTabWidget::addTab(editor, doc->getIcon(), doc->fileName());
}




void Panel::contextMenuEvent(QContextMenuEvent *event)
{
        QMenu *contextMenu = new QMenu(this);
        QAction *action = contextMenu->addAction(tr("Customize"));
        //action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
        //connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));

        contextMenu->exec(event->globalPos());

        delete contextMenu;
        //check if action is deleted
}
