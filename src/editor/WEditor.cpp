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



#include "WEditor.h"
#include "WEditorBinder.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include "Logger.h"

#include <QContextMenuEvent>
#include <QWheelEvent>

#include <algorithm>

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QtScintilla(parent),
    mBinder(new EditorBinder())
{
    initialize();
}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QtScintilla(parent),
    mBinder(doc)
{
    initialize();
}


Editor::~Editor()
{

}


void Editor::initialize()
{
    mSciSettings = AppSettings::instance()->scintilla;

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setUtf8(true);
    this->setAutoIndent(true);
    this->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setMarginLineNumbers(0, false);
    this->setMarginLineNumbers(1, true);
    this->setMarginSensitivity(0, true);

    this->setEolVisibility(mSciSettings->isEolVisible());
    connect( mSciSettings, SIGNAL(eolVisibleChanged(bool)),
                  this, SLOT(setEolVisibility(bool)), Qt::DirectConnection );

    onWhiteSpaceVisibilityChanged(mSciSettings->isWhiteSpaceVisible());
    connect( mSciSettings, SIGNAL(whiteSpaceVisibleChanged(bool)),
                  this, SLOT(onWhiteSpaceVisibilityChanged(bool)), Qt::DirectConnection );

    onWrapModeEnabledChanged(mSciSettings->isWrapModeEnabled());
    connect( mSciSettings, SIGNAL(wrapModeEnabledChanged(bool)),
                  this, SLOT(onWrapModeEnabledChanged(bool)), Qt::DirectConnection );

    //this->setWrapIndentMode();
    //this->setWrapVisualFlags();

    connect( this, SIGNAL(cursorLineChanged(int)),
             this, SLOT(onCursorLineChanged(int)) );

    connect( mSciSettings, SIGNAL(showLineNumbersEnabledChanged(bool)),
                  this, SLOT(onShowLineNumbersEnabledChanged(bool)), Qt::DirectConnection );

    updateLineNoMargin(true);
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


void Editor::setCodec(const QString &name)
{
    mBinder->setCodecName(name);
}

QString Editor::getCode()
{
    return mBinder->getCodecName();
}

void Editor::convertToCodec(const QString &name)
{

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

void Editor::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier) {
        if(event->delta() < 0)
            zoomOut();
        else if(event->delta() > 0)
            zoomIn();

    } else {
        QtScintilla::wheelEvent(event);
    }
}


void Editor::updateLineNoMargin(bool visible)
{
    if(visible) {
        int lastVisibleLine = this->firstVisibleLine() + this->linesVisible() + 1;
        int num = QString::number(lastVisibleLine).size();
        num = std::max(num, 3);
        int width = SendScintilla(SCI_TEXTWIDTH, STYLE_LINENUMBER, "8");
        #define SPACE_PIXELS 8
        setMarginWidth(1, width * num + SPACE_PIXELS);
    } else {
        setMarginWidth(1, 0);
    }
}

