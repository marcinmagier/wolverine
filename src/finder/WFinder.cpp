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
#include "WFindRequest.h"
#include "WFindResults.h"
#include "WFindReqWidget.h"
#include "WFindResWidget.h"

#include "WEditor.h"
#include "WEditorProxy.h"

#include "WCentralWidget.h"

#include "qtdockwidget.h"

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
    mFindReqWidget = 0;
    mFindResWidget = 0;
    mFindResults = 0;
    qAddPostRoutine(deleteInstance);

    mDockReqWidget = new QtDockWidget(tr("Find"));
    mDockResWidget = new QtDockWidget(tr("Find Results"));

    mDockReqWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect( mDockReqWidget, SIGNAL(dockVisibilityChanged(bool)),
                       this, SLOT(onReqDockVisibilityChanged(bool)) );
    connect( mDockReqWidget, SIGNAL(customContextMenuRequested(QPoint)),
                       this, SLOT(onReqDockCustomContextMenuRequested(QPoint)) );

    connect( mDockResWidget, SIGNAL(dockVisibilityChanged(bool)),
                       this, SLOT(onResDockVisibilityChanged(bool)) );



    mEditorProxy = EditorProxy::instance();
    connect( mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                     this, SLOT(onEditorChanged(Editor*)) );
    connect( mEditorProxy, SIGNAL(currentEditorNotValid(Editor*)),
                     this, SLOT(onEditorNotValid(Editor*)) );
}


/**
 *  Destructor.
 */
Finder::~Finder()
{
    if(mFindResults)
        delete mFindResults;


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


void Finder::setFindAction(QAction *action)
{
    mFindAction = action;
}


void Finder::setReplaceAction(QAction *action)
{
    mReplaceAction = action;
}


void Finder::setFindInFilesAction(QAction *action)
{
    mFindInFilesAction = action;
}


void Finder::setCentralWidget(CentralWidget *central)
{
    mCentralWidget = central;
}

QDockWidget* Finder::getFindReqDock()
{
    return mDockReqWidget;
}

QDockWidget* Finder::getFindResDock()
{
    return mDockResWidget;
}



void Finder::showFindWidget()
{
    mDockReqWidget->setWindowTitle(tr("Find"));

    setupFindWidget();

    mFindReqWidget->setCurrentIndex(FindReqWidget::FindIdx);
    mFindAction->setChecked(true);
    mFindInFilesAction->setChecked(false);
    mReplaceAction->setChecked(false);
}

void Finder::showFindInFilesWidget()
{
    mDockReqWidget->setWindowTitle(tr("Find In Files"));

    setupFindWidget();

    mFindReqWidget->setCurrentIndex(FindReqWidget::FindInFilesIdx);
    mFindAction->setChecked(false);
    mFindInFilesAction->setChecked(true);
    mReplaceAction->setChecked(false);
}

void Finder::showReplaceWidget()
{
    mDockReqWidget->setWindowTitle(tr("Replace"));

    setupFindWidget();

    mFindReqWidget->setCurrentIndex(FindReqWidget::ReplaceIdx);
    mFindAction->setChecked(false);
    mFindInFilesAction->setChecked(false);
    mReplaceAction->setChecked(true);
}


void Finder::setupFindWidget()
{
    if(mFindReqWidget == 0) {
        mDockReqWidget->show();
    } else {
        mDockReqWidget->setFocus();
    }

    QString selection = mEditorProxy->getCurrentEditor()->selectedText();
    if(!selection.isEmpty())
        mFindReqWidget->setInitialSearchPattern(selection);

    mDockReqWidget->raise();
}


void Finder::findNext()
{
    if(mFindReqWidget == 0)
        return;

    mFindReqWidget->updateSearchHistory();
    find(mFindReqWidget->getFindRequest(), false);
}


void Finder::findPrev()
{
    if(mFindReqWidget == 0)
        return;

    mFindReqWidget->updateSearchHistory();
    find(mFindReqWidget->getFindRequest(), true);
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
    createResultsWidget();
    mFindResWidget->find(mFindReqWidget->getFindRequest());
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





void Finder::createResultsWidget()
{
    if(mFindResWidget == 0)
        mDockResWidget->show();
    else
        mDockResWidget->setFocus();

    mDockResWidget->raise();
}


void Finder::onReqDockVisibilityChanged(bool visible)
{
    if(visible) {
        if(mFindReqWidget == 0) {
            mFindReqWidget = new FindReqWidget(this);
            mFindReqWidget->setCurrentIndex(FindReqWidget::FindIdx);
            mDockReqWidget->setWidget(mFindReqWidget);

            mFindAction->setChecked(true);
            mFindInFilesAction->setChecked(false);
            mReplaceAction->setChecked(false);

            mDockResWidget->toggleViewAction()->setEnabled(true);
        }
    } else {
        if(mFindReqWidget) {
            delete mFindReqWidget;
            mFindReqWidget = 0;
            mDockReqWidget->setWidget(0);
            mDockReqWidget->setWindowTitle(tr("Find"));

            mDockResWidget->toggleViewAction()->setEnabled(false);
        }
        mFindAction->setChecked(false);
        mFindInFilesAction->setChecked(false);
        mReplaceAction->setChecked(false);
    }
}

void Finder::onReqDockCustomContextMenuRequested(const QPoint &/*pos*/)
{
    QMenu *menu = new QMenu();
    menu->addAction(mFindAction);
    menu->addAction(mReplaceAction);
    menu->addAction(mFindInFilesAction);
    menu->addAction( tr("Close"), mDockReqWidget, SLOT(hide()) );

    menu->exec(QCursor::pos());
}



void Finder::onResDockVisibilityChanged(bool visible)
{
    if(visible) {
        if(mFindReqWidget == 0) {
            mDockResWidget->hide();
            return;
        }

        if(mFindResWidget == 0) {
            mFindResWidget = new FindResWidget(this, mDockResWidget);
            mDockResWidget->setWidget(mFindResWidget);
        }
    } else {
        if(mFindResWidget) {
            delete mFindResWidget;
            mFindResWidget = 0;
            mDockResWidget->setWidget(0);
        }
    }
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


void Finder::find(const FindRequest &req, bool reverse)
{
    Editor *edit = mEditorProxy->getCurrentEditor();
    bool forward = (req.isReverseDirection == reverse) ? true : false;
    bool ret;


    if(req.isInSelection) {
        ret = edit->findFirstInSelection(req.searchPattern,
                                   req.isRegexp,
                                   req.isCaseSensitive,
                                   req.isWholeWords,
                                   forward);
    } else {
        int line = -1;
        int index = -1;
        if(!forward) {
            edit->getCursorPosition(&line, &index);
            index--;
        }
        ret = edit->findFirst(req.searchPattern,
                        req.isRegexp,
                        req.isCaseSensitive,
                        req.isWholeWords,
                        req.isWrap,
                        forward,
                        line,
                        index);
    }
    qDebug() << ret;
}

FindResults* Finder::find(const FindRequest &req)
{
    FindResults *results = new FindResults(req);

    mEditorProxy->getCurrentEditor()->findFirst(req.searchPattern, false, false, false, false);

    return results;
}
