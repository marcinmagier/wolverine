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
#include "WEditorProxy.h"
#include "WPanel.h"
#include "WPanelTabBar.h"
#include "WPanelTabContent.h"

#include <QContextMenuEvent>



using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
Panel::Panel(EditorProxy *editorProxy, QWidget *parent) :
    QtTabWidget(parent),
    mEditorProxy(editorProxy)
{
    mTabBar = new PanelTabBar(this);
    this->setTabBar(mTabBar);

    connect( mTabBar, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mTabBar, SIGNAL(scrollButtonsHiddenChanged(bool)),
                this, SLOT(setListButtonHidden(bool)) );
    connect( mTabBar, SIGNAL(focusReceived()),
                this, SLOT(onInternalWidgetFocusReceived()) );
    connect( mTabBar, SIGNAL(tabNewRequested()),
                this, SLOT(onTabNewRequested()) );

    connect( this, SIGNAL(currentChanged(int)),
             this, SLOT(onCurrentTabChanged(int)) );
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
    PanelTabContent *tabContent = new PanelTabContent(this);
    connect( tabContent, SIGNAL(focusReceived()),
                 this, SLOT(onInternalWidgetFocusReceived()) );
    tabContent->addWidget(editor);
    return QtTabWidget::addTab(tabContent, doc->getIcon(), doc->fileName());
}


int Panel::indexOf(Editor *editor)
{
    for(int i=0; i<count(); i++) {
        PanelTabContent *tabContent = this->getTabContent(i);
        if(tabContent->hasEditor(editor))
            return i;
    }
    return -1;
}

int Panel::indexOf(const QString &filePath)
{
    for(int i=0; i<count(); i++) {
        PanelTabContent *tabContent = this->getTabContent(i);
        if(tabContent->hasEditor(filePath))
            return i;
    }
    return -1;
}

int Panel::tabAt(const QPoint &pos)
{
    return mTabBar->tabAt(pos);
}

Editor* Panel::getEditor(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    return tabContent->getEditor();
}

void Panel::splitTab(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    tabContent->split();
}

void Panel::removeTab(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    QtTabWidget::removeTab(index);
    delete tabContent;
}





void Panel::onCustomContextMenuRequested(QPoint pos)
{
    emit customContextMenuRequested(pos);
}

void Panel::onInternalWidgetFocusReceived()
{
    Editor *edit = this->getEditor(this->currentIndex());
    mEditorProxy->setCurrentEditor(edit);

    // Emit focusReceived() only if signal comes from editor
    if(!edit->hasFocus()) {
        edit->setFocus();
    } else {
        emit focusReceived();
    }
}

void Panel::onCurrentTabChanged(int idx)
{
    if(idx<0)
        return;

    Editor *edit = this->getEditor(idx);
    mEditorProxy->setCurrentEditor(edit);
    edit->setFocus();
}

void Panel::onTabNewRequested()
{
    emit tabNewRequested();
}


PanelTabContent* Panel::getTabContent(int idx)
{
    return dynamic_cast<PanelTabContent*>(this->widget(idx));
}
