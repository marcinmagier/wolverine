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
 *  @file       WEditor.cpp
 *  @brief      Wolverine::Editor class implementation.
 */



#include "Logger.h"
#include "WEditor.h"
#include "WEditorBinder.h"


#include <QContextMenuEvent>

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mBinder(0)
{
    initialize();
}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QsciScintilla(parent),
    mBinder(doc)
{
    initialize();
}


Editor::~Editor()
{

}


void Editor::initialize()
{
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);
}

Editor* Editor::getLinkedCopy()
{
   return mBinder->getLinkedEditor(this);
}


//static
void Editor::removeEditor(Editor *editor)
{
    EditorBinder *doc = editor->getBinder();
    doc->removeEditor(editor);    // Document deletes editor
    if(!doc->hasEditors())
        delete doc;
}

void Editor::setBinder(EditorBinder *doc)
{
    mBinder = doc;
}


EditorBinder* Editor::getBinder()
{
    if(mBinder == 0)
        LOG_ERROR("There is no binder asociated with the editor");

    return mBinder;
}


/**
 *  focusInEvent() handler
 *
 */
//virtual
void Editor::focusInEvent(QFocusEvent *event)
{
    emit focusReceived();
    QsciScintilla::focusInEvent(event);
}

void Editor::contextMenuEvent(QContextMenuEvent *event)
{
    emit customContextMenuRequestedd(event->pos());
}
