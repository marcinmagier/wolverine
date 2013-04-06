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
#include "CfgViewSettings.h"

#include <QMouseEvent>
#include <QColor>



using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
PanelTabBar::PanelTabBar(QWidget *parent) :
    QtTabBar(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);

    AppSettings *settings = AppSettings::instance();

    this->setMovable(settings->view->isTabBarMovable());
    this->setTabsClosable(settings->view->isTabBarCloseVisible());
    this->setHighlightColor(settings->view->getTabBarActiveBgColor());
    this->onTabBarModernStyleEnabledChanged(settings->view->isTabBarModernStyleEnabled());

    this->setDocumentMode(true);
    this->setExpanding(false);
    this->setIconSize(QSize(13, 13));


    connect( settings->view, SIGNAL(tabBarModernStyleEnabledChanged(bool)),
                       this, SLOT(onTabBarModernStyleEnabledChanged(bool)), Qt::DirectConnection );
    connect( settings->view, SIGNAL(tabBarCloseVisibleChanged(bool)),
                       this, SLOT(onTabBarCloseVisibleChanged(bool)), Qt::DirectConnection );
    connect( settings->view, SIGNAL(tabBarMovableChanged(bool)),
                       this, SLOT(onTabBarMovableChanged(bool)), Qt::DirectConnection );
    connect( settings->view, SIGNAL(tabBarActiveBgColorChanged(QColor)),
                       this, SLOT(onTabBarBgColorChanged(QColor)), Qt::DirectConnection );

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
            if(settings->view->isTabBarMiddleBtnNew())
                emit tabNewRequested();
        } else {
            if(settings->view->isTabBarMiddleBtnClose())
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
            if(settings->view->isTabBarDoubleClkNew())
                emit tabNewRequested();
        } else {
            if(settings->view->isTabBarDoubleClkClose())
                emit tabCloseRequested(idx);
        }
    }
    QtTabBar::mouseDoubleClickEvent(event);
}


/**
 *  tabBarActiveBgColorChanged() handler
 *
 * @param color
 */
void PanelTabBar::onTabBarBgColorChanged(const QColor &color)
{
    if(getHighlightColor().isValid())
        setHighlightColor(color);
}

/**
 *  tabBarLockedChanged() handler
 *
 * @param val
 */
void PanelTabBar::onTabBarMovableChanged(bool val)
{
    this->setMovable(val);
}


/**
 *  tabBarCloseVisibleChanged() handler
 *
 * @param val
 */
void PanelTabBar::onTabBarCloseVisibleChanged(bool val)
{
    this->setTabsClosable(val);
}


/**
 *  tabBarModernStyleEnabledChanged() handler
 *
 * @param val
 */
void PanelTabBar::onTabBarModernStyleEnabledChanged(bool val)
{
    if(val)
        this->setStyle( static_cast<QtTabBar::HiStyle>(AppSettings::instance()->view->getTabBarStyle()) );
    else
        this->setStyle( QtTabBar::CLASSIC );
}
