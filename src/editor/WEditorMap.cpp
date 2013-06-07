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
#include "WEditorMapFrame.h"
#include "WEditor.h"
#include "WEditorProxy.h"


#include <QFrame>
#include <QResizeEvent>

#include <QDebug>


#define FRAME_STYLE_PATTERN     "QFrame {"                                \
                                "background-color: rgb(%1, %2, %3, 30);"  \
                                "}"

#define FRAME_MAX_WIDTH  180
#define FRAME_MIN_WIDTH  80

#define MINI_LINE_HEIGHT 3



using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
EditorMap::EditorMap(QWidget *parent) :
    QtScintilla(parent)
{
    mEditorProxy = EditorProxy::instance();

    mFg = new QFrame(this);
    mBg = new EditorMapFrame(this);

    this->setColorFrame(QColor(27, 122, 231));
    this->setMaximumWidth(FRAME_MAX_WIDTH);
    this->setMinimumWidth(FRAME_MIN_WIDTH);

    this->setFocusPolicy(Qt::NoFocus);
    this->setMarginWidth(0, 0);
    this->setMarginWidth(1, 0);
    this->zoomTo(-10);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setEndAtLastLine(false);


    connect(  mBg, SIGNAL(mousePressed(int)),
             this, SLOT(onFramePressed(int)) );
    connect(  mBg, SIGNAL(wheelDeltaChanged(int)),
             this, SLOT(onFrameWheelDeltaChanged(int)) );

    connect( mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                     this, SLOT(onCurrentEditorChanged(Editor*)) );
    connect( mEditorProxy, SIGNAL(currentEditorNotValid(Editor*)),
                     this, SLOT(onCurrentEditorNotValid(Editor*)) );

    onCurrentEditorChanged(mEditorProxy->getCurrentEditor());
}


/**
 *  Destructor
 */
EditorMap::~EditorMap()
{
    delete mFg;
    delete mBg;
}


/**
 *  Sets current screen frame color.
 *
 * @param color
 */
void EditorMap::setColorFrame(const QColor &color)
{
    mFg->setStyleSheet(QString(FRAME_STYLE_PATTERN).arg(color.red()).arg(color.green()).arg(color.blue()));
}


/**
 *  resizeEvent() handler
 *
 * @param e
 */
void EditorMap::resizeEvent(QResizeEvent *e)
{
    mBg->resize(e->size());
    mFg->resize(e->size().width(), mFg->height());
}


/**
 *  Slot called when current editor has changed.
 *
 * @param editor
 */
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


/**
 *  Slot called when current editor has become invalid.
 *
 * @param editor
 */
void EditorMap::onCurrentEditorNotValid(Editor *editor)
{
    editor->disconnect(this);
}


/**
 *  Slot called when size of current editor changed.
 */
void EditorMap::onCurrentEditorSizeChanged()
{
    updateMap(mEditorProxy->getCurrentEditor());
}


/**
 *  Slot called when zoom of current editor changed.
 */
void EditorMap::onCurrentEditorZoomChanged()
{
    updateMap(mEditorProxy->getCurrentEditor());
}


/**
 *  Slot called when current editor was scrolled.
 */
void EditorMap::onCurrentEditorScrollChanged(int)
{
    updateMap(mEditorProxy->getCurrentEditor());
}


/**
 *  Slot called when mini map was clicked.
 *
 * @param y
 */
void EditorMap::onFramePressed(int y)
{
    Editor *editor = mEditorProxy->getCurrentEditor();

    int frame = editor->linesVisible() * MINI_LINE_HEIGHT;
    int line = this->lineAt(QPoint(1, y-frame/2));
    editor->setFirstVisibleLine(line);
}


/**
 *  Slot called when mini map was scrolled.
 *
 * @param delta
 */
void EditorMap::onFrameWheelDeltaChanged(int delta)
{
    Editor *editor = mEditorProxy->getCurrentEditor();
    int line = editor->firstVisibleLine();
    editor->setFirstVisibleLine(line - delta);
}


/**
 *  Updates mini map layout.
 *
 * @param editor
 */
void EditorMap::updateMap(Editor *editor)
{
    int editLines = editor->lines();
    int editLinesVisible = editor->linesVisible();
    float editFirstVisibleLine = editor->firstVisibleLine();

    int miniLinesVisiblePlus = this->linesVisible() - editLinesVisible;

    int miniFirstVisibleLine = 0;
    if(editLines > miniLinesVisiblePlus) {
        int fgFrameFirstLine = editFirstVisibleLine/editLines * miniLinesVisiblePlus;
        miniFirstVisibleLine = editFirstVisibleLine - fgFrameFirstLine;
    }
    int fgMoveLines = editFirstVisibleLine - miniFirstVisibleLine;

    this->setFirstVisibleLine(miniFirstVisibleLine);

    mFg->resize(mFg->width(), editLinesVisible * MINI_LINE_HEIGHT);
    mFg->move(0, fgMoveLines * MINI_LINE_HEIGHT);
}
