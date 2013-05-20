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
 *  @file       WDockWidget.cpp
 *  @brief      Wolverine::DockWidget class implementation.
 */




#include "WDockWidget.h"

#include "Logger.h"

#include <QAction>
#include <QEvent>



using namespace Wolverine;


/**
 *  Constructor.
 *
 * @param parent
 */
DockWidget::DockWidget(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
    mAction = 0;
    connect(this, SIGNAL(visibilityChanged(bool)),
            this, SLOT(onVisibilityChanged(bool)) );
}

void DockWidget::addAction(QAction *action)
{
    mAction = action;
}


QAction* DockWidget::getAction()
{
    return mAction;
}


void DockWidget::onVisibilityChanged(bool visible)
{
    if(mAction == 0)
        return;
    if(mAction->isCheckable() == false)
        return;
    if(mAction->isChecked() == visible)
        return;

    mAction->setChecked(visible);
}
