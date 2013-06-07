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
 *  @file       WEditorMap.cpp
 *  @brief      Wolverine::EditorMap class implementation.
 */




#include "WEditorMap.h"
#include "WEditor.h"
#include "WEditorProxy.h"


#include <QFrame>
#include <QResizeEvent>

#include <QDebug>


#define FRAME_STYLE_PATTERN     "QFrame {"                                  \
                                "background-color: rgb(27, 122, 231, 30);"  \
                                "}"

#define FRAME_MAX_WIDTH  180
#define FRAME_MIN_WIDTH  80

#define MINI_LINE_HEIGHT 3



using namespace Wolverine;

EditorMap::EditorMap(QWidget *parent) :
    QtScintilla(parent)
{
    mEditorProxy = EditorProxy::instance();

    mBg = new QFrame(this);
    mFg = new QFrame(this);
    mFg->setStyleSheet(QString(FRAME_STYLE_PATTERN));

    this->setMaximumWidth(FRAME_MAX_WIDTH);
    this->setMinimumWidth(FRAME_MIN_WIDTH);

    this->setFocusPolicy(Qt::NoFocus);
    this->setMarginWidth(0, 0);
    this->setMarginWidth(1, 0);
    this->zoomTo(-10);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setEndAtLastLine(false);


    connect( mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                     this, SLOT(onCurrentEditorChanged(Editor*)) );
    connect( mEditorProxy, SIGNAL(currentEditorNotValid(Editor*)),
                     this, SLOT(onCurrentEditorNotValid(Editor*)) );

    onCurrentEditorChanged(mEditorProxy->getCurrentEditor());
}



void EditorMap::resizeEvent(QResizeEvent *e)
{
    mBg->resize(e->size());
    mFg->resize(e->size().width(), mFg->height());
}

void EditorMap::onCurrentEditorChanged(Editor *editor)
{
    this->setDocument(editor->document());
    this->setLexer(editor->lexer());

    connect( editor, SIGNAL(sizeChanged()),
               this, SLOT(onCurrentEditorSizeChanged()) );
    connect( editor, SIGNAL(SCN_ZOOM()),
               this, SLOT(onCurrentEditorZoomChanged()) );
    connect( editor, SIGNAL(verticalScrollBarChanged(int)),
               this, SLOT(onCurrentEditorScrollChanged(int)) );

    updateMap(editor);
}

void EditorMap::onCurrentEditorNotValid(Editor *editor)
{
    editor->disconnect(this);
}


void EditorMap::onCurrentEditorSizeChanged()
{
    updateMap(mEditorProxy->getCurrentEditor());
}

void EditorMap::onCurrentEditorZoomChanged()
{
    updateMap(mEditorProxy->getCurrentEditor());
}

void EditorMap::onCurrentEditorScrollChanged(int)
{
    updateMap(mEditorProxy->getCurrentEditor());
}


void EditorMap::updateMap(Editor *editor)
{
    int editLines = editor->lines();
    int editLinesVisible = editor->linesVisible();
    float editFirstVisibleLine = editor->firstVisibleLine();

    int miniLinesVisiblePlus = this->linesVisible() - editLinesVisible;

    int fgFrameFirstLine = editFirstVisibleLine/editLines * miniLinesVisiblePlus;
    int miniFirstVisibleLine = editFirstVisibleLine - fgFrameFirstLine;
    int fgMoveLines = editFirstVisibleLine - miniFirstVisibleLine;

    this->setFirstVisibleLine(miniFirstVisibleLine);

    mFg->resize(mFg->width(), editLinesVisible * MINI_LINE_HEIGHT);
    mFg->move(0, fgMoveLines * MINI_LINE_HEIGHT);
}
