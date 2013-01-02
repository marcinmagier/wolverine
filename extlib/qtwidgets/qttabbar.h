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
 *  @file       qttabbar.h
 *  @brief      QtTabBar class interface.
 */



#ifndef __QT_TAB_BAR_H_
 #define __QT_TAB_BAR_H_


#include <QTabBar>


class QtTabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit QtTabBar(QWidget *parent = 0);
    bool areScrollButtonsHidden();
    

signals:
    void scrollButtonsHiddenChanged(bool hidden);


protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void tabLayoutChange();


private:
    void checkScrollButtons();

    bool mScrollButtonsHidden;
};

#endif // __QT_TAB_BAR_H_
