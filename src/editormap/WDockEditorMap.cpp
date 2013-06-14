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
 *  @file       WDockEditorMap.cpp
 *  @brief      Wolverine::DockEditorMap class implementation.
 */



#include "WDockEditorMap.h"
#include "WEditorMap.h"

#include "Logger.h"




using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
DockEditorMap::DockEditorMap(QWidget *parent) :
    QtDockWidget(tr("MiniMap"), parent),
    mEditorMap(0)
{

}


/**
 *  Destructor
 */
DockEditorMap::~DockEditorMap()
{
    if(mEditorMap) {
        delete mEditorMap;
        mEditorMap = 0;
    }
}


/**
 *  Creates/deletes internal widget when dock visibility is changing.
 *
 * @param visible
 */
//virtual
void DockEditorMap::changeVisibility(bool visible)
{
    if(visible) {
        if(mEditorMap == 0)
            mEditorMap = new EditorMap();
        else
            LOG_DEBUG("EditorMap is not null");
        this->setWidget(mEditorMap);
        QtDockWidget::changeVisibility(visible);

    } else {
        QtDockWidget::changeVisibility(visible);
        this->setWidget(0);

        if(mEditorMap) {
            delete mEditorMap;
            mEditorMap = 0;
        }
        else {
            LOG_DEBUG("Editor is null");
       }
    }
}
