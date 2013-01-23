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
#include "WEditorLexerManager.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include "Logger.h"

#include <QContextMenuEvent>

#include <algorithm>

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QtScintilla(parent),
    mBinder(0)
{
    initialize();
    this->setLexer(QString("Normal Text"));
}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QtScintilla(parent),
    mBinder(doc)
{
    initialize();
    this->setLexer(mLexerManager->getLexerName(mBinder));

}


Editor::~Editor()
{

}


void Editor::initialize()
{
    mLexerManager = EditorLexerManager::instance();
    mSettings = AppSettings::instance()->scintilla;

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setUtf8(true);
    this->setAutoIndent(true);
    this->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setMarginLineNumbers(0, false);
    this->setMarginLineNumbers(1, true);
    this->setMarginSensitivity(0, true);


    connect( this, SIGNAL(cursorLineChanged(int)),
             this, SLOT(onCursorLineChanged(int)) );

    connect( mSettings, SIGNAL(showLineNumbersEnabledChanged(bool)),
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

QString Editor::getFileName()
{
    return mBinder->fileName();
}

QString Editor::getFilePath()
{
    return mBinder->canonicalFilePath();
}


void Editor::setLexer(const QString &name)
{
    mLexerName = name;
    QtScintilla::setLexer(mLexerManager->getLexer(name));
    // BUG: set lexer twice to workaround problem with final lexer style
    QtScintilla::setLexer(mLexerManager->getLexer(name));
}

QString Editor::getLexerName()
{
    return mLexerName;
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

