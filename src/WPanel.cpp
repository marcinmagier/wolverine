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

#include "WEditor.h"
#include "WEditorBinder.h"
#include "WPanel.h"
#include "WPanelTabBar.h"

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
    mTabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    //this->setFocusPolicy(Qt::StrongFocus);

    connect( mTabBar, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mTabBar, SIGNAL(scrollButtonsHiddenChanged(bool)),
                this, SLOT(setListButtonHidden(bool)) );
    connect( mTabBar, SIGNAL(focusReceived()),
                this, SLOT(onInternalWidgetFocusReceived()) );
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
    EditorBinder *doc = editor->getBinder();

    return QtTabWidget::addTab(editor, doc->getIcon(), doc->fileName());
}


int Panel::indexOf(Editor *editor)
{
    for(int i=0; i<count(); i++) {
        Editor *tmp = dynamic_cast<Editor*>(this->widget(i));
        if(tmp->getBinder() == editor->getBinder())
            return i;
    }
    return -1;
}

Editor* Panel::getEditor(int idx)
{
    return dynamic_cast<Editor*>(this->widget(idx));
}

int Panel::tabAt(const QPoint &pos)
{
    return mTabBar->tabAt(pos);
}





void Panel::onCustomContextMenuRequested(QPoint pos)
{
    emit customContextMenuRequested(pos);
}

void Panel::onInternalWidgetFocusReceived()
{
    emit focusReceived();
}

