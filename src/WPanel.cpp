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

#include "WPanel.h"
#include "WPanelTabBar.h"

#include "QToolButton"

#include <QDebug>



using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
Panel::Panel(QWidget *parent) :
    QTabWidget(parent)
{
    mTabBar = new PanelTabBar(this);
    this->setTabBar(mTabBar);

    button = new QToolButton(this);
    this->setCornerWidget(button, Qt::TopRightCorner);
    button->setCursor(Qt::ArrowCursor);
    button->setHidden(false);

    connect( mTabBar, SIGNAL(scrollButtonsHiddenChanged(bool)),
                this, SLOT(onButtonsVisibleChanged(bool)) );

}


/**
 *  Destructor
 */
Panel::~Panel()
{
    delete mTabBar;
    delete button;
}



void Panel::onButtonsVisibleChanged(bool hidden)
{
    if(hidden) {
        setCornerWidget(0, Qt::TopRightCorner);
    } else {
        setCornerWidget(button, Qt::TopRightCorner);
    }
}
