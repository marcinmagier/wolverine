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
 *  @file       WPanelTabBar.h
 *  @brief      Wolverine::PanelTabBar class interface.
 */



#ifndef __W_PANEL_TAB_BAR_H_
 #define __W_PANEL_TAB_BAR_H_


#include "qttabbar.h"

class QMouseEvent;


namespace Wolverine
{

class PanelTabBar : public QtTabBar
{
    Q_OBJECT

public:
    explicit PanelTabBar(QWidget *parent = 0);
    

public slots:

signals:
    void focusReceived();
    void tabNewRequested();


protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);


};



}

#endif // __W_PANEL_TAB_BAR_H_
