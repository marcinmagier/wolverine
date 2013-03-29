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
#include "WFindReqWidget.h"

#include "Logger.h"


#include <QApplication>
#include <QDockWidget>

#include <QDebug>


using namespace Wolverine;


Finder *Finder::sInstance = 0;


/**
 *  Constructor.
 */
Finder::Finder() 
{
    mFindRequestDock = 0;
    qAddPostRoutine(deleteInstance);

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
}

void Finder::showFindInFilesWidget()
{
    createFindWidget();
}

void Finder::showReplaceWidget()
{
    createFindWidget();
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
        mFindRequestDock = new QDockWidget(tr("Find/Replace"));
        mFindRequestDock->setWidget(new FindReqWidget());
        emit showWidgetRequested(mFindRequestDock, Qt::BottomDockWidgetArea, tr("Find/Replace"));
    } else {
        mFindRequestDock->setFocus();
    }
}
