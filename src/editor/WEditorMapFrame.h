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
 *  @file       WEditorMapFrame.h
 *  @brief      Wolverine::EditorMapFrame class interface.
 */




#ifndef __W_EDITOR_MAP_FRAME_H_
 #define __W_EDITOR_MAP_FRAME_H_

#include <QFrame>


namespace Wolverine {


class EditorMapFrame : public QFrame
{
    Q_OBJECT

public:
    explicit EditorMapFrame(QWidget *parent = 0);
    
signals:
    void mousePressed(int y);
    void wheelDeltaChanged(int delta);
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    
};


}

#endif // __W_EDITOR_MAP_FRAME_H_
