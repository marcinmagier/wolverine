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
 *  @file       WEditorMapFrame.cpp
 *  @brief      Wolverine::EditorMapFrame class implementation.
 */


#include "WEditorMapFrame.h"

#include <QMouseEvent>
#include <QWheelEvent>



using namespace Wolverine;



/**
 *  Constructor
 *
 * @param parent
 */
EditorMapFrame::EditorMapFrame(QWidget *parent) :
    QFrame(parent)
{

}


/**
 *  mousePressEvent() handler
 *
 * @param event
 */
void EditorMapFrame::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event->y());
}


/**
 *  mouseMoveEvent() handler
 *
 * @param event
 */
void EditorMapFrame::mouseMoveEvent(QMouseEvent *event)
{
    emit mousePressed(event->y());
}


/**
 *  wheelEvent() handler
 *
 * @param event
 */
void EditorMapFrame::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y()/30;
    if(event->modifiers() & Qt::ShiftModifier)
        delta = delta * 14;

    emit wheelDeltaChanged(delta);
}
