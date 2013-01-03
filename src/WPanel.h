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
 *  @file       WPanel.h
 *  @brief      Wolverine::Panel class interface.
 */



#ifndef __W_PANEL_H_
 #define __W_PANEL_H_


#include "qttabwidget.h"




namespace Wolverine
{

class PanelTabBar;



class Panel : public QtTabWidget
{
    Q_OBJECT

public:

    enum Position {
        RightPanel,
        LeftPanel
    };

    explicit Panel(QWidget *parent = 0);
    virtual ~Panel();
    
signals:
    
public slots:

private:
    PanelTabBar *mTabBar;

};


}

#endif // __W_PANEL_H_