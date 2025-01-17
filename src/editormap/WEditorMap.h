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
 *  @file       WEditorMap.h
 *  @brief      Wolverine::EditorMap class interface.
 */



#ifndef __W_EDITOR_MAP_H_
 #define __W_EDITOR_MAP_H_


#include "qtscintilla.h"


class QFrame;

namespace Wolverine {

class Editor;
class EditorProxy;


class EditorMap : public QtScintilla
{
    Q_OBJECT

public:
    explicit EditorMap(QWidget *parent = 0);
    ~EditorMap();
    
signals:
    
public slots:
    void setColorFrame(const QColor &color);

protected:
    void resizeEvent(QResizeEvent *e);


private slots:
    void onCurrentEditorChanged(Editor *editor);
    void onCurrentEditorNotValid(Editor *editor);
    void onCurrentEditorSizeChanged();
    void onCurrentEditorZoomChanged();
    void onCurrentEditorScrollChanged(int);

    void onFramePressed(int y);
    void onFrameWheelDeltaChanged(int delta);

private:
    void updateMap(Editor *editor);

    EditorProxy *mEditorProxy;

    QFrame *mBg;
    QFrame *mFg;

};


}


#endif // __W_EDITOR_MAP_H_
