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
#include "WFindReqDock.h"
#include "WFindReqWidget.h"
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


void Finder::showFindWidget(bool visible)
{
    if(visible) {
        createFindWidget();
        mFindReqWidget->setCurrentIndex(0);
        mFindInFilesAction->setChecked(false);
        mReplaceAction->setChecked(false);
    } else {
        mFindRequestDock->setVisible(false);
    }
    mFindRequestDock->setWindowTitle(tr("Find"));
}

void Finder::showFindInFilesWidget(bool visible)
{
    if(visible) {
        createFindWidget();
        mFindReqWidget->setCurrentIndex(2);
        mFindAction->setChecked(false);
        mReplaceAction->setChecked(false);
    } else {
        mFindRequestDock->setVisible(false);
    }
    mFindRequestDock->setWindowTitle(tr("Find In Files"));
}

void Finder::showReplaceWidget(bool visible)
{
    if(visible) {
        createFindWidget();
        mFindReqWidget->setCurrentIndex(1);
        mFindAction->setChecked(false);
        mFindInFilesAction->setChecked(false);
    } else {
        mFindRequestDock->setVisible(false);
    }
    mFindRequestDock->setWindowTitle(tr("Replace"));
}

void Finder::findNext()
{
    if(mFindRequestDock == 0)
        return;

    qDebug() << "Find next";
}

void Finder::findPrev()
{
    if(mFindRequestDock == 0)
        return;

    qDebug() << "Find prev";
}



void Finder::createFindWidget()
{
    if(mFindRequestDock == 0) {
        mFindReqWidget = new FindReqWidget();
        mFindRequestDock = new FindReqDock();
        mFindRequestDock->setWidget(mFindReqWidget);

        connect( mFindRequestDock, SIGNAL(closeRequested()),
                             this, SLOT(onCloseRequested()) );

        mFindRequestDock->setContextMenuPolicy(Qt::CustomContextMenu);
        connect( mFindRequestDock, SIGNAL(customContextMenuRequested(QPoint)),
                             this, SLOT(onCustomContextMenuRequested(QPoint)) );
        emit showWidgetRequested(mFindRequestDock, Qt::BottomDockWidgetArea, tr("Find/Replace"));
    } else {
        mFindRequestDock->setVisible(true);
        mFindRequestDock->setFocus();
    }
}




void Finder::onCloseRequested()
{
    mFindAction->setChecked(false);
    mFindInFilesAction->setChecked(false);
    mReplaceAction->setChecked(false);
}

void Finder::onCustomContextMenuRequested(const QPoint &/*pos*/)
{
    QMenu *menu = new QMenu();
    menu->addAction(mFindAction);
    menu->addAction(mReplaceAction);
    menu->addAction(mFindInFilesAction);

    menu->exec(QCursor::pos());
}
