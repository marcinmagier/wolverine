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
 *  @file       WFinder.cpp
 *  @brief      Wolverine::Finder class implementation.
 */



#include "WFinder.h"
#include "WFindOptions.h"
#include "WFindReqDock.h"
#include "WFindReqWidget.h"


#include "WEditor.h"
#include "WEditorProxy.h"

#include "WActionManager.h"

#include "Logger.h"


#include <QApplication>
#include <QDockWidget>
#include <QAction>
#include <QMenu>
#include <QCursor>

#include <QDebug>


using namespace Wolverine;


Finder *Finder::sInstance = 0;


/**
 *  Constructor.
 */
Finder::Finder() 
{
    mFindRequestDock = 0;
    mFindReqWidget = 0;
    qAddPostRoutine(deleteInstance);

    mEditorProxy = EditorProxy::instance();
    connect( mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                     this, SLOT(onEditorChanged(Editor*)) );
    connect( mEditorProxy, SIGNAL(currentEditorNotValid(Editor*)),
                     this, SLOT(onEditorNotValid(Editor*)) );

    ActionManager *actionManager = ActionManager::instance();
    mFindAction = actionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND);
    mFindInFilesAction = actionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_IN_FILES);
    mReplaceAction = actionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_REPLACE);

}


/**
 *  Destructor.
 */
Finder::~Finder()
{

}


/**
 *  Creates and returns instance.
 * @return
 */
//static
Finder* Finder::instance()
{
    if(sInstance == 0) {
        sInstance = new Finder();
    }
    return sInstance;
}


/**
 *  Deletes instance.
 */
void Finder::deleteInstance()
{
    if(sInstance) {
        delete sInstance;
        sInstance = 0;
    }
}


void Finder::showFindWidget()
{

        createFindWidget();
        mFindReqWidget->setCurrentIndex(0);
        mFindAction->setChecked(true);
        mFindInFilesAction->setChecked(false);
        mReplaceAction->setChecked(false);

    mFindRequestDock->setWindowTitle(tr("Find"));

    QString selection = mEditorProxy->getCurrentEditor()->selectedText();
    if(!selection.isEmpty())
        mFindReqWidget->setInitialSearchPattern(selection);
}

void Finder::showFindInFilesWidget()
{

        createFindWidget();
        mFindReqWidget->setCurrentIndex(2);
        mFindAction->setChecked(false);
        mFindInFilesAction->setChecked(true);
        mReplaceAction->setChecked(false);

    mFindRequestDock->setWindowTitle(tr("Find In Files"));

    QString selection = mEditorProxy->getCurrentEditor()->selectedText();
    if(!selection.isEmpty())
        mFindReqWidget->setInitialSearchPattern(selection);
}

void Finder::showReplaceWidget()
{
        createFindWidget();
        mFindReqWidget->setCurrentIndex(1);
        mFindAction->setChecked(false);
        mFindInFilesAction->setChecked(false);
        mReplaceAction->setChecked(true);

    mFindRequestDock->setWindowTitle(tr("Replace"));

    QString selection = mEditorProxy->getCurrentEditor()->selectedText();
    if(!selection.isEmpty())
        mFindReqWidget->setInitialSearchPattern(selection);
}

void Finder::findNext()
{
    if(mFindRequestDock == 0)
        return;

    mFindReqWidget->updateSearchHistory();

    qDebug() << "Find next";
}


void Finder::findPrev()
{
    if(mFindRequestDock == 0)
        return;

    mFindReqWidget->updateSearchHistory();

    qDebug() << "Find prev";
}


void Finder::findAll()
{
    mFindReqWidget->updateSearchHistory();
}


void Finder::findInAllTabs()
{
    mFindReqWidget->updateSearchHistory();
}


void Finder::findInFiles()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateFilterAndDirectoryHistory();
}


void Finder::replace()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateReplaceHistory();
}

void Finder::replaceFindNext()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateReplaceHistory();
}

void Finder::replaceAll()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateReplaceHistory();
}

void Finder::replaceInAllTabs()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateReplaceHistory();
}

void Finder::replaceInFiles()
{
    mFindReqWidget->updateSearchHistory();
    mFindReqWidget->updateReplaceHistory();
    mFindReqWidget->updateFilterAndDirectoryHistory();
}



void Finder::markAll()
{

}

void Finder::markAll(int style)
{

}

void Finder::unmarkAll()
{

}

void Finder::unmarkAll(int style)
{

}

void Finder::jumpNextMark()
{

}

void Finder::jumpNextMark(int style)
{

}

void Finder::jumpPrevMark()
{

}

void Finder::jumpPrevMark(int style)
{

}



void Finder::createFindWidget()
{
    if(mFindRequestDock == 0) {
        mFindReqWidget = new FindReqWidget(this);
        mFindRequestDock = new FindReqDock();
        mFindRequestDock->setWidget(mFindReqWidget);

        connect( mFindRequestDock, SIGNAL(closeRequested()),
                             this, SLOT(onReqDockCloseRequested()) );

        mFindRequestDock->setContextMenuPolicy(Qt::CustomContextMenu);
        connect( mFindRequestDock, SIGNAL(customContextMenuRequested(QPoint)),
                             this, SLOT(onReqDockCustomContextMenuRequested(QPoint)) );
        emit showWidgetRequested(mFindRequestDock, Qt::BottomDockWidgetArea, tr("Find/Replace"));
    } else {
        mFindRequestDock->setVisible(true);
        mFindRequestDock->setFocus();
    }
}




void Finder::onReqDockCloseRequested()
{
    mFindAction->setChecked(false);
    mFindInFilesAction->setChecked(false);
    mReplaceAction->setChecked(false);
}

void Finder::onReqDockCustomContextMenuRequested(const QPoint &/*pos*/)
{
    QMenu *menu = new QMenu();
    menu->addAction(mFindAction);
    menu->addAction(mReplaceAction);
    menu->addAction(mFindInFilesAction);
    menu->addAction( tr("Close"), this, SLOT(onReqDockCloseTriggered()) );

    menu->exec(QCursor::pos());
}

void Finder::onReqDockCloseTriggered()
{
    onReqDockCloseRequested();
    mFindRequestDock->hide();
}

void Finder::onEditorChanged(Editor *edit)
{
    connect( edit, SIGNAL(selectionChanged()),
             this, SLOT(onEditorSelectionChanged()) );
    connect( edit, SIGNAL(cursorPositionChanged(int,int)),
             this, SLOT(onEditorCursorPositionChanged(int,int)) );
}

void Finder::onEditorNotValid(Editor *edit)
{
    disconnect( edit, SIGNAL(selectionChanged()),
                this, SLOT(onEditorSelectionChanged()) );
    disconnect( edit, SIGNAL(cursorPositionChanged(int,int)),
                this, SLOT(onEditorCursorPositionChanged(int,int)) );
}

void Finder::onEditorSelectionChanged()
{
    Editor *edit = dynamic_cast<Editor*>(sender());
    if(edit->selectedText().isEmpty())
        return;

    if(edit->isSignleWordSelected())
        qDebug() << "Word";
}

void Finder::onEditorCursorPositionChanged(int line, int index)
{
    qDebug() << "Cursor changed";
}
