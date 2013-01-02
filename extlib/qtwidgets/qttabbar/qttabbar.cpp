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
 *  @file       qttabbar.cpp
 *  @brief      QtTabBar class implementation.
 */


#include "qttabbar.h"




/**
 *  Constructor
 *
 * @param parent
 */
QtTabBar::QtTabBar(QWidget *parent) :
    QTabBar(parent),
    mScrollButtonsHidden(true)
{
}


/**
 *  Returns state of scroll buttons
 *
 * @return
 */
bool QtTabBar::areScrollButtonsHidden()
{
    return mScrollButtonsHidden;
}


/**
 *  resizeEvent() handler
 */
//virtual
void QtTabBar::resizeEvent(QResizeEvent *event)
{
    checkScrollButtons();
    QTabBar::resizeEvent(event);
}


/**
 *  tabLayoutChange() handler
 */
//virtual
void QtTabBar::tabLayoutChange()
{
    checkScrollButtons();
}


/**
 *  Checks if scroll buttons visibility changed
 */
void QtTabBar::checkScrollButtons()
{
    if(this->count() < 2)
        return; // Nothing to do when there is no tabs or only one tab

    QRect tabBar = this->geometry();
    QRect firstTab = this->tabRect(0);
    QRect lastTab = this->tabRect(this->count()-1);

    if(mScrollButtonsHidden) {
        // Check if scroll buttons appeared
        if(firstTab.x()==0)
            if(lastTab.x() + lastTab.width() < tabBar.width())
                return;

        //Buttons are visible now
        mScrollButtonsHidden = false;
        emit scrollButtonsHiddenChanged(mScrollButtonsHidden);
    } else {
        // Check if scroll buttons disappeared
        if(firstTab.x() < 0)
            return;
        if(lastTab.x() + lastTab.width() > tabBar.width())
            return;

        // Buttons are hidden now
        mScrollButtonsHidden = true;
        emit scrollButtonsHiddenChanged(mScrollButtonsHidden);
    }
}
