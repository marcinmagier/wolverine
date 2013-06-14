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
 *  @file       WDockEditorMap.h
 *  @brief      Wolverine::DockEditorMap class interface.
 */



#ifndef __W_DOCK_EDITOR_MAP_H_
 #define __W_DOCK_EDITOR_MAP_H_

#include "qtdockwidget.h"


namespace Wolverine
{

class EditorMap;


class DockEditorMap : public QtDockWidget
{
    Q_OBJECT

public:
    explicit DockEditorMap(QWidget *parent = 0);
    ~DockEditorMap();
    

protected:
    virtual void changeVisibility(bool visible);


private:
    EditorMap *mEditorMap;
    
};


}

#endif // __W_DOCK_EDITOR_MAP_H_
