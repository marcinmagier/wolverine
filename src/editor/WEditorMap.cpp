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



#define FRAME_STYLE_PATTERN     "QFrame {"                                  \
                                "background-color: rgb(27, 122, 231, 30);"  \
                                "}"

#define FRAME_MAX_WIDTH 180
#define FRAME_MIN_WIDTH 60



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


    connect( mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                     this, SLOT(onCurrentEditorChanged(Editor*)) );
}



void EditorMap::resizeEvent(QResizeEvent *e)
{
    mBg->resize(e->size());
    mFg->resize(mBg->width(), 100);
}

void EditorMap::onCurrentEditorChanged(Editor *editor)
{
    this->setDocument(editor->document());
    this->setLexer(editor->lexer());
}
