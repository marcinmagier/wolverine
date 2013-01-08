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
 *  @file       qtmanagedtoolbarlistbox.h
 *  @brief      QtManagedToolbarListbox class interface.
 *  @details    It shouldn't be used outside qtmanagedtoolbar library.
 */

#ifndef __QT_MANAGED_TOOLBAR_LISTBOX_H_
 #define __QT_MANAGED_TOOLBAR_LISTBOX_H_


#include <QListWidget>



class QtManagedToolbarListbox : public QListWidget
{
    Q_OBJECT
    
public:
    explicit QtManagedToolbarListbox(QWidget *parent = 0);

    void dropEvent(QDropEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // __QT_MANAGED_TOOLBAR_LISTBOX_H_
