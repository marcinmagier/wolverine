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
#include "WPanelSplitter.h"
#include "WPanelTabBar.h"

#include <QContextMenuEvent>
#include <QDebug>



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
    PanelSplitter *splitter = new PanelSplitter(this);
    connect( splitter, SIGNAL(focusReceived()),
                 this, SLOT(onInternalWidgetFocusReceived()) );
    splitter->addWidget(editor);
    return QtTabWidget::addTab(splitter, doc->getIcon(), doc->fileName());
}


int Panel::indexOf(Editor *editor)
{
    for(int i=0; i<count(); i++) {
        PanelSplitter *splitter = this->getSplitter(i);
        if(splitter->hasEditor(editor))
            return i;
    }
    return -1;
}

int Panel::indexOf(const QString &filePath)
{
    for(int i=0; i<count(); i++) {
        PanelSplitter *splitter = this->getSplitter(i);
        if(splitter->hasEditor(filePath))
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
    PanelSplitter *splitter = this->getSplitter(index);
    return splitter->getEditor();
}

void Panel::splitTab(int index)
{
    PanelSplitter *splitter = this->getSplitter(index);
    splitter->split();
}

void Panel::removeTab(int index)
{
    PanelSplitter *splitter = this->getSplitter(index);
    QtTabWidget::removeTab(index);
    delete splitter;
}




void Panel::onCustomContextMenuRequested(QPoint pos)
{
    emit customContextMenuRequested(pos);
}

void Panel::onInternalWidgetFocusReceived()
{
    Editor *edit = this->getEditor(this->currentIndex());

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
    edit->setFocus();
    mEditorProxy->setCurrentEditor(edit);
}

void Panel::onTabNewRequested()
{
    emit tabNewRequested();
}


PanelSplitter* Panel::getSplitter(int idx)
{
    return dynamic_cast<PanelSplitter*>(this->widget(idx));
}
