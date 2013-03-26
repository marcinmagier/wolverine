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
 *  @file       WEditorProxy.cpp
 *  @brief      Wolverine::EditorProxy class implementation.
 */




#include "WEditorProxy.h"
#include "WEditor.h"
#include "WEditorBinder.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "qtmanagedmenu.h"

#include <QApplication>
#include <QCursor>
#include <QScrollBar>


#define W_ACTION_CUT "Cut"
#define W_ACTION_COPY "Copy"
#define W_ACTION_PASTE "Paste"

#define W_EDITOR_CONTEXT_MENU  "EditorContextMenu"


using namespace Wolverine;


EditorProxy *EditorProxy::sInstance = 0;


EditorProxy::EditorProxy()
{
    mCurrentEditor = 0;
    mSettings = AppSettings::instance();
    setupContextMenu();
    qAddPostRoutine(deleteInstance);

    connect( mSettings->general, SIGNAL(synchHEnabledChanged(bool)),
                           this, SLOT(onSynchHEnabledChanged(bool)), Qt::DirectConnection );
    connect( mSettings->general, SIGNAL(synchVEnabledChanged(bool)),
                           this, SLOT(onSynchVEnabledChanged(bool)), Qt::DirectConnection );
}

EditorProxy::~EditorProxy()
{
    delete mContextMenu;
}

//static
EditorProxy* EditorProxy::instance()
{
    if(sInstance == 0) {
        sInstance = new EditorProxy();
    }
    return sInstance;
}

void EditorProxy::deleteInstance()
{
    if(sInstance) {
        delete sInstance;
        sInstance = 0;
    }
}



Editor *EditorProxy::getCurrentEditor()
{
    return mCurrentEditor;
}

void EditorProxy::setCurrentEditor(Editor *editor)
{
    if(mCurrentEditor != editor) {
        cleanOldEditor(mCurrentEditor);
        mCurrentEditor = editor;
        if(mCurrentEditor) {
            setupNewEditor(mCurrentEditor);

            emit currentEditorChanged(mCurrentEditor);
        }
    }
}

void EditorProxy::setupNewEditor(Editor *editor)
{
    if(editor) {
        connect( editor, SIGNAL(customContextMenuRequested(QPoint)),
                           this, SLOT(onCustomContextMenuRequested(QPoint)), Qt::UniqueConnection );

        onSynchHEnabledChanged(mSettings->general->isSynchHEnabled());
        onSynchVEnabledChanged(mSettings->general->isSynchVEnabled());
    }
}

void EditorProxy::cleanOldEditor(Editor *editor)
{
    if(editor) {
        disconnect( editor->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                                             this, SLOT(onCurrentEditorScrollHChanged(int)) );
        disconnect( editor->verticalScrollBar(), SIGNAL(valueChanged(int)),
                                           this, SLOT(onCurrentEditorScrollVChanged(int)) );
    }
}



QString EditorProxy::getCurrentEditorDir()
{
    return mCurrentEditor->getBinder()->canonicalPath();
}

QString EditorProxy::getCurrentEditorName()
{
    return mCurrentEditor->getBinder()->fileName();
}







void EditorProxy::onUndo()
{
    mCurrentEditor->undo();
}

void EditorProxy::onRedo()
{
    mCurrentEditor->redo();
}

void EditorProxy::onCut()
{
    mCurrentEditor->cut();
}

void EditorProxy::onCopy()
{
    mCurrentEditor->copy();
}


void EditorProxy::onPaste()
{
    mCurrentEditor->paste();
}


void EditorProxy::onReload()
{
    int line, index;
    mCurrentEditor->getCursorPosition(&line, &index);
    int firstVisible = mCurrentEditor->firstVisibleLine();

    mCurrentEditor->getBinder()->loadFile();

    mCurrentEditor->setFirstVisibleLine(firstVisible);
    mCurrentEditor->setCursorPosition(line, index);
}

void EditorProxy::onZoomDefault()
{
    mCurrentEditor->zoomTo(0);
}

void EditorProxy::onZoomIn()
{
    mCurrentEditor->zoomIn();
}

void EditorProxy::onZoomOut()
{
    mCurrentEditor->zoomOut();
}




void EditorProxy::onSynchHEnabledChanged(bool value)
{
    QScrollBar *scrollBar = mCurrentEditor->horizontalScrollBar();
    if(value) {
        mCurrentEditorPrevScrollValH = scrollBar->value();
        connect( scrollBar, SIGNAL(valueChanged(int)),
                     this , SLOT(onCurrentEditorScrollHChanged(int)) );
    } else {
        disconnect( scrollBar, SIGNAL(valueChanged(int)),
                         this, SLOT(onCurrentEditorScrollHChanged(int)) );
    }
}

void EditorProxy::onSynchVEnabledChanged(bool value)
{
    QScrollBar *scrollBar = mCurrentEditor->verticalScrollBar();
    if(value) {
        mCurrentEditorPrevScrollValV = scrollBar->value();
        connect( scrollBar, SIGNAL(valueChanged(int)),
                     this , SLOT(onCurrentEditorScrollVChanged(int)), Qt::UniqueConnection );
    } else {
        disconnect( scrollBar, SIGNAL(valueChanged(int)),
                         this, SLOT(onCurrentEditorScrollVChanged(int)) );
    }
}

void EditorProxy::onCurrentEditorScrollHChanged(int value)
{
    int range = value - mCurrentEditorPrevScrollValH;
    mCurrentEditorPrevScrollValH = value;
    emit currentEditorScrollHChanged(range);
}

void EditorProxy::onCurrentEditorScrollVChanged(int value)
{
    int range = value - mCurrentEditorPrevScrollValV;
    mCurrentEditorPrevScrollValV = value;
    emit currentEditorScrollVChanged(range);
}



void EditorProxy::onCustomContextMenuRequested(const QPoint &pos)
{
    mContextMenu->exec(QCursor::pos());
}


void EditorProxy::setupContextMenu()
{
    QAction *action;
    mContextMenu = new QtManagedMenu(0, W_EDITOR_CONTEXT_MENU);
    mContextMenu->setManagerEnabled(mSettings->general->isAppCustomizeEnabled());
    connect( mSettings->general, SIGNAL(appCustomizeEnabledChanged(bool)),
                   mContextMenu, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    action = new QAction(tr("Cut"), mContextMenu);
    action->setIcon(QIcon(":/cut.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCut()) );
    mContextMenu->addAction(W_ACTION_CUT, action);

    action = new QAction(tr("Copy"), mContextMenu);
    action->setIcon(QIcon(":/copy.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCopy()) );
    mContextMenu->addAction(W_ACTION_COPY, action);

    action = new QAction(tr("Paste"), mContextMenu);
    action->setIcon(QIcon(":/paste.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onPaste()) );
    mContextMenu->addAction(W_ACTION_PASTE, action);




    mContextMenu->restoreConfig();
}
