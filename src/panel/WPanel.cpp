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

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgViewSettings.h"


#include <QContextMenuEvent>



using namespace Wolverine;





/**
 *  Constructor
 *
 * @param parent
 */
Panel::Panel(QWidget *parent) :
    QtTabWidget(parent)
{
    mEditorProxy = EditorProxy::instance();
    mTabBar = new PanelTabBar(this);
    this->setModernStyleListButtonEnabled(true);
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
    disconnect( this, SIGNAL(currentChanged(int)),
                this, SLOT(onCurrentTabChanged(int)) );

    while(this->count() > 0) {
        Editor *editor = this->getEditor(0);
        this->removeTab(0);
        Editor::removeEditor(editor);
    }

    delete mTabBar;
}


/**
 *  Adds new tab to the panel.
 *
 * @param editor
 * @return
 */
int Panel::addTab(Editor *editor, const QIcon &icon)
{
    PanelTabContent *tabContent = new PanelTabContent(this);
    connect( tabContent, SIGNAL(focusReceived()),
                 this, SLOT(onInternalWidgetFocusReceived()), Qt::UniqueConnection );
    tabContent->addWidget(editor);

    EditorBinder *binder = editor->getBinder();
    return QtTabWidget::addTab(tabContent, icon, binder->fileName());
}


/**
 *  Inserts new tab
 *
 * @param index
 * @param editor
 * @param icon
 * @return
 */
int Panel::insertTab(int index, Editor *editor, const QIcon &icon)
{
    PanelTabContent *tabContent = new PanelTabContent(this);
    connect( tabContent, SIGNAL(focusReceived()),
                 this, SLOT(onInternalWidgetFocusReceived()), Qt::UniqueConnection );
    tabContent->addWidget(editor);

    EditorBinder *binder = editor->getBinder();
    return QtTabWidget::insertTab(index, tabContent, icon, binder->fileName());
}


/**
 *  Checks if given editor is already opened in panel.
 *
 * @param editor
 * @return
 */
int Panel::indexOf(Editor *editor)
{
    for(int i=0; i<count(); i++) {
        PanelTabContent *tabContent = this->getTabContent(i);
        if(tabContent->hasEditor(editor))
            return i;
    }
    return -1;
}


/**
 *  Checks if file path associated with given editor is already opened in panel.
 *
 * @param filePath
 * @return
 */
int Panel::indexOf(const QString &filePath)
{
    for(int i=0; i<count(); i++) {
        PanelTabContent *tabContent = this->getTabContent(i);
        if(tabContent->hasEditor(filePath))
            return i;
    }
    return -1;
}


/**
 *  Returns tab index from given point. Used by context menu handler.
 *
 * @param pos
 * @return
 */
int Panel::tabAt(const QPoint &pos)
{
    return mTabBar->tabAt(pos);
}


/**
 *  Returns editor placed on the given index.
 *
 * @param index
 * @return
 */
Editor* Panel::getEditor(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    return tabContent->getEditor();
}


/**
 *  Splits editor.
 *
 * @param index
 */
void Panel::splitTab(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    tabContent->split();
}


/**
 *  Removes tab.
 *
 * @param index
 */
void Panel::removeTab(int index)
{
    PanelTabContent *tabContent = this->getTabContent(index);
    QtTabWidget::removeTab(index);
    delete tabContent;
}


/**
 *  Activates or deactivates panel.
 *
 * @param active
 */
void Panel::setActive(bool active)
{
    if(active)
        mTabBar->setHighlightColor(AppSettings::instance()->view->getTabBarActiveBgColor());
    else
        mTabBar->setHighlightColor(QColor());
}


/**
 *  TabBar's customContextMenuRequested() signal handler.
 *
 * @param pos
 */
void Panel::onCustomContextMenuRequested(QPoint pos)
{
    emit customContextMenuRequested(pos);
}


/**
 *  Internal widgets focusReceived() signal handler.
 */
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


/**
 *  TabWidget's currentChanged() signal handler.
 *
 * @param idx
 */
void Panel::onCurrentTabChanged(int idx)
{
    if(idx<0)
        return;

    Editor *edit = this->getEditor(idx);
    mEditorProxy->setCurrentEditor(edit);
    edit->setFocus();
}


/**
 *  TabBar's tabNewRequested() signal handler.
 */
void Panel::onTabNewRequested()
{
    emit tabNewRequested();
}


/**
 *  Retrieves PanelTabContent from the given index.
 *
 * @param idx
 * @return
 */
PanelTabContent* Panel::getTabContent(int idx)
{
    return dynamic_cast<PanelTabContent*>(this->widget(idx));
}
