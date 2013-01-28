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
 *  @file       WEditorProxy_slots.cpp
 *  @brief      Wolverine::EditorProxy slots implementation.
 */




#include "WEditorProxy.h"
#include "WEditor.h"
#include "WEditorBinder.h"
#include "qtmanagedmenu.h"


#include <QCursor>


using namespace Wolverine;






void EditorProxy::setCurrentEditor(Editor *editor)
{
    if(mCurrentEditor != editor) {
        mCurrentEditor = editor;
        if(mCurrentEditor) {
            connect( mCurrentEditor, SIGNAL(customContextMenuRequested(QPoint)),
                               this, SLOT(onCustomContextMenuRequested(QPoint)), Qt::UniqueConnection );

            emit currentEditorChanged(mCurrentEditor);
        }
    }
}

void EditorProxy::setCurrentEditorLexer(const QString &name)
{

}


void EditorProxy::onCut()
{

}

void EditorProxy::onCopy()
{

}


void EditorProxy::onPaste()
{

}





void EditorProxy::onCustomContextMenuRequested(const QPoint &pos)
{
    mContextMenu->exec(QCursor::pos());
}

