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

#include "qtmanagedmenu.h"
#include "qttabwidget.h"




namespace Wolverine
{

class Editor;
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


    int addTab(Editor *editor);
    int indexOf(Editor *editor);
    Editor* getEditor(int idx);
    int tabAt(const QPoint &pos);
    

public slots:


signals:
    void focusReceived();
    void tabNewRequested();


private slots:
    void onCustomContextMenuRequested(QPoint pos);
    void onInternalWidgetFocusReceived();
    void onTabNewRequested();

private:
    PanelTabBar *mTabBar;

};


}

#endif // __W_PANEL_H_
