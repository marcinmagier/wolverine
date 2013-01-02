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
 *  @file       WPanelTabBar.cpp
 *  @brief      Wolverine::PanelTabBar class implementation.
 */

#include "WPanelTabBar.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "QDebug"


using namespace Wolverine;

PanelTabBar::PanelTabBar(QWidget *parent) :
    QTabBar(parent),
    mAreButtonsVisible(false)
{
    AppSettings *settings = AppSettings::instance();
    this->setMovable(!settings->general->isTabBarLocked());

    this->setTabsClosable(settings->general->isTabBarCloseVisible());

    this->setMovable(true);
    this->setTabsClosable(true);
    this->setDocumentMode(true);
    this->setExpanding(false);
    this->setFocusPolicy(Qt::NoFocus);

    this->setIconSize(QSize(8, 8));


}

/**
 * @brief PanelTabBar::checkButtons
 */
void PanelTabBar::checkButtons()
{
    //qDebug() << "check buttons";

    QRect tabBar = this->geometry();
    QRect firstTab = this->tabRect(0);
    QRect lastTab = this->tabRect(this->count()-1);

    if(mAreButtonsVisible) {
        if(firstTab.x() < 0)
            return;
        if(lastTab.x() + lastTab.width() > tabBar.width())
            return;

        // Buttons are not visible now
        mAreButtonsVisible = false;
        emit buttonsVisibleChanged(mAreButtonsVisible);
    } else {
        if(firstTab.x()==0)
            if(lastTab.x() + lastTab.width() < tabBar.width())
                return;

        //Buttons are visible now
        mAreButtonsVisible = true;
        emit buttonsVisibleChanged(mAreButtonsVisible);
    }
}

/**
 * @brief PanelTabBar::tabLayoutChange
 */
//virtual
void PanelTabBar::resizeEvent(QResizeEvent *event)
{
   // qDebug() << "resize";
    checkButtons();
    QTabBar::resizeEvent(event);
}

/**
 * @brief PanelTabBar::tabLayoutChange
 */
//virtual
void PanelTabBar::tabLayoutChange()
{
   // qDebug() << "layout";
    checkButtons();
}
