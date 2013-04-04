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
 *  @file       WFindReqDock.h
 *  @brief      Wolverine::FindReqDock class interface.
 */



#ifndef __W_FIND_REQ_DOCK_H_
 #define __W_FIND_REQ_DOCK_H_


#include <QDockWidget>


namespace Wolverine
{

class FindReqDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit FindReqDock(QWidget *parent = 0);
    

private slots:

signals:


protected:


};



}

#endif // __W_FIND_REQ_DOCK_H_
