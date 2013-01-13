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

#include <QMouseEvent>



using namespace Wolverine;


/**
 *  Constructor
 * @param parent
 */
PanelTabBar::PanelTabBar(QWidget *parent) :
    QtTabBar(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);

    AppSettings *settings = AppSettings::instance();
    this->setMovable(!settings->general->isTabBarLocked());

    this->setTabsClosable(settings->general->isTabBarCloseVisible());

    this->setMovable(true);
    this->setTabsClosable(true);
    this->setDocumentMode(true);
    this->setExpanding(false);
    this->setIconSize(QSize(13, 13));
    this->enableModernStyle(true);

}


/**
 *  focusInEvent() handler
 *
 * @param event
 */
//virtual
void PanelTabBar::focusInEvent(QFocusEvent *event)
{
    emit focusReceived();
    QtTabBar::focusInEvent(event);
}


/**
 *  mouseReleaseEvent() handler
 *
 * @param event
 */
//virtual
void PanelTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::MidButton) {
        int idx = this->tabAt(event->pos());
        AppSettings *settings = AppSettings::instance();
        if(idx < 0) {
            if(settings->general->isTabBarMiddleBtnNew())
                emit tabNewRequested();
        } else {
            if(settings->general->isTabBarMiddleBtnClose())
                emit tabCloseRequested(idx);
        }
    }
    QtTabBar::mouseReleaseEvent(event);
}


/**
 *  mouseReleaseEvent() handler
 *
 * @param event
 */
//virtual
void PanelTabBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton) {
        int idx = this->tabAt(event->pos());
        AppSettings *settings = AppSettings::instance();
        if(idx < 0) {
            if(settings->general->isTabBarDoubleClkNew())
                emit tabNewRequested();
        } else {
            if(settings->general->isTabBarDoubleClkClose())
                emit tabCloseRequested(idx);
        }
    }
    QtTabBar::mouseDoubleClickEvent(event);
}
