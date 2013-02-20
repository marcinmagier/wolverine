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
 *  @file       WCentralWidget.cpp
 *  @brief      Wolverine::CentralWidget class implementation.
 */


#include "WCentralWidget.h"
#include "WEditor.h"
#include "WEditorBinder.h"
#include "WEditorProxy.h"
#include "WPanel.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "qtmanagedmenu.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QIcon>

#include <QDebug>


#define W_ACTION_NEW "New"
#define W_ACTION_CLOSE "Close"
#define W_ACTION_CLOSE_OTHERS "CloseOthers"
#define W_ACTION_CLOSE_ALL "CloseAll"
#define W_ACTION_SPLIT_TAB "SplitTab"
#define W_ACTION_MOVE_TAB "MoveTab"
#define W_ACTION_COPY_TAB "CopyTab"
#define W_ACTION_MOVE_DOCK "MoveDock"
#define W_ACTION_COPY_DOCK "CopyDock"
#define W_ACTION_MOVE_APP "MoveApp"
#define W_ACTION_COPY_APP "CopyApp"


#define W_TABBAR_CONTEXT_MENU  "TabBarContextMenu"


using namespace Wolverine;


CentralWidget::CentralWidget(QWidget *parent):
    QWidget(parent)
{
    mCurrentEditor = new EditorProxy();

    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mSplitter = new QSplitter(this);
    mSplitter->setOrientation(Qt::Horizontal);
    mPanelLeft = new Panel(mCurrentEditor, mSplitter);
    mPanelRight = new Panel(mCurrentEditor, mSplitter);
    mPanelRight->hide();
    mSplitter->addWidget(mPanelLeft);
    mSplitter->addWidget(mPanelRight);
    mLayout->addWidget(mSplitter);


    connect( mPanelLeft, SIGNAL(tabCloseRequested(int)),
                  this, SLOT(onCloseIdx(int)) );
    connect( mPanelLeft, SIGNAL(customContextMenuRequested(QPoint)),
                  this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mPanelLeft, SIGNAL(focusReceived()),
                   this, SLOT(onInternalWidgetFocusReceived()) );
    connect( mPanelLeft, SIGNAL(tabNewRequested()),
                   this, SLOT(onNew()) );

    connect( mPanelRight, SIGNAL(tabCloseRequested(int)),
                   this, SLOT(onCloseIdx(int)) );
    connect( mPanelRight, SIGNAL(customContextMenuRequested(QPoint)),
                   this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mPanelRight, SIGNAL(focusReceived()),
                   this, SLOT(onInternalWidgetFocusReceived()) );
    connect( mPanelRight, SIGNAL(tabNewRequested()),
                    this, SLOT(onNew()) );

    mSettings = AppSettings::instance();

    mPanelCurrent = mPanelLeft;

    setupContextMenu();
}

CentralWidget::~CentralWidget()
{
    delete mCurrentEditor;
    delete mContextMenu;
    //layout, spliter and panels are deleted automatically
}


EditorProxy* CentralWidget::getCurrentEditor()
{
    return mCurrentEditor;
}


void CentralWidget::removeTab(Panel *panel, int index)
{
    Editor *edit = panel->getEditor(index);
    panel->removeTab(index);
    Editor::removeEditor(edit);
}


void CentralWidget::removeOthers(Panel *panel, int index)
{
    if(panel->count() < 2)
        return;

    int idxToRemove = 0;    // Remove first widget for i < index
    int i=-1;
    int numOfTabs= panel->count();
    while(++i < numOfTabs) {
        if(i == index) {
            idxToRemove = 1;    // Remove second widget for i > index
            continue;
        }
        this->removeTab(panel, idxToRemove);
    }
}

void CentralWidget::moveAll(Panel *from, Panel *to)
{
    int idx = to->currentIndex();
    if(to->count() == 0)
        idx = from->currentIndex();

    int fromLength = from->count();
    for(int i=0; i<fromLength; i++) {
        Editor *edit = from->getEditor(0);
        from->removeTab(0);
        to->addTab(edit);
    }
    mPanelCurrent = to;
    to->setCurrentIndex(idx);
}


void CentralWidget::moveTab(Panel *from, int fromIdx, Panel *to)
{
    Editor *edit = from->getEditor(fromIdx);
    from->removeTab(fromIdx);
    mPanelCurrent = to;
    int idx = to->indexOf(edit);
    if(idx<0) {
        to->addTab(edit);
        to->setCurrentWidget(edit);
    } else {
        // There is already a copy of the editor on the other panel
        // Remove this linked copy
        Editor::removeEditor(edit);
        to->setCurrentIndex(idx);
    }
}

void CentralWidget::copyTab(Panel *from, int fromIdx, Panel *to)
{
    Editor *edit = from->getEditor(fromIdx);
    mPanelCurrent = to;
    int idx = to->indexOf(edit);
    if(idx<0) {
        Editor *copy = edit->getLinkedCopy();
        to->addTab(copy);
        to->setCurrentWidget(copy);
    } else {
        // There is already a copy of the editor - select it
        to->setCurrentIndex(idx);
    }
}


void CentralWidget::setCurrentPanel(Panel *panel)
{
    if(mPanelCurrent != panel) {
        mPanelCurrent = panel;
        this->setCurrentEditor(mPanelCurrent->getEditor(mPanelCurrent->currentIndex()));
    }
}

void CentralWidget::setCurrentEditor(Editor *editor)
{
    mCurrentEditor->setCurrentEditor(editor);
    editor->setFocus();

}


bool CentralWidget::setCurrentIfExists(Panel *panel, Editor *editor, int line)
{
    int idx = panel->indexOf(editor);
    if(idx >= 0) {
        mPanelCurrent = panel;
        mPanelCurrent->setCurrentIndex(idx);
        if(line >= 0)
            mPanelCurrent->getEditor(idx)->setCursorPosition(line, 0);
        return true;
    }

    return false;
}


bool CentralWidget::setCurrentIfExists(Panel *panel, const QString &path, int line)
{
    int idx = panel->indexOf(path);
    if(idx >= 0) {
        mPanelCurrent = panel;
        mPanelCurrent->setCurrentIndex(idx);
        if(line >= 0)
            mPanelCurrent->getEditor(idx)->setCursorPosition(line, 0);
        return true;
    }

    return false;
}


void CentralWidget::setupContextMenu()
{
    QAction *action;
    GeneralSettings *settings = AppSettings::instance()->general;
    mContextMenu = new QtManagedMenu(this, W_TABBAR_CONTEXT_MENU);
    mContextMenu->setManagerEnabled(settings->isAppCustomizeEnabled());
    connect(     settings, SIGNAL(appCustomizeEnabledChanged(bool)),
             mContextMenu, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    action = new QAction(tr("New"), mContextMenu);
    action->setIcon(QIcon(":/new.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onNew()) );
    mContextMenu->addAction(W_ACTION_NEW, action);

    action = new QAction(tr("Close"), mContextMenu);
    action->setIcon(QIcon(":/close.png"));
    //action is handled within context menu hander
    mMenuClose = action;
    mContextMenu->addAction(W_ACTION_CLOSE, action);

    action = new QAction(tr("Close Others"), mContextMenu);
    //action->setIcon(QIcon(":/close.png"));
    //action is handled within context menu hander
    mMenuCloseOthers = action;
    mContextMenu->addAction(W_ACTION_CLOSE_OTHERS, action);

    action = new QAction(tr("Close All"), mContextMenu);
    action->setIcon(QIcon(":/close_all.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCloseAll()) );
    mContextMenu->addAction(W_ACTION_CLOSE_ALL, action);

    action = new QAction(tr("Split"), mContextMenu);
    //action is handled within context menu hander
    mMenuSplitTab = action;
    mContextMenu->addAction(W_ACTION_SPLIT_TAB, action);

    action = new QAction(mContextMenu);
    //text is set within menu handler
    //action is handled within menu hander
    mMenuMoveTab = action;
    mContextMenu->addAction(W_ACTION_MOVE_TAB, action);

    action = new QAction(mContextMenu);
    //text is set within menu handler
    //action is handled within menu hander
    mMenuCopyTab = action;
    mContextMenu->addAction(W_ACTION_COPY_TAB, action);

    mMenuMoveDock = new QAction(tr("Move to dock"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_MOVE_DOCK, mMenuMoveDock);

    mMenuCopyDock = new QAction(tr("Copy to dock"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_COPY_DOCK, mMenuCopyDock);

    mMenuMoveApp = new QAction(tr("Move to new instance"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_MOVE_APP, mMenuMoveApp);

    mMenuCopyApp = new QAction(tr("Copy to new instance"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_COPY_APP, mMenuCopyApp);

    mContextMenu->restoreConfig();
}

