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
 *  @file       WEditor_slots.cpp
 *  @brief      Wolverine::Editor slots implementation.
 */



#include "Logger.h"
#include "WEditor.h"
#include "WEditorBinder.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include <QDebug>

using namespace Wolverine;



void Editor::onShowLineNumbersEnabledChanged(bool val)
{
    this->updateLineNoMargin(val);
}

void Editor::onCursorPositionChanged(int line, int index)
{
    //qDebug() << "Hello";
}

void Editor::onCursorLineChanged(int line)
{
    this->updateLineNoMargin(mSciSettings->isShowLineNumbersEnabled());
}

void Editor::onSelectionChanged()
{
    isSignleWordSelected();
}

void Editor::onWhiteSpaceVisibilityChanged(bool val)
{
    if(val) {
        this->setWhitespaceVisibility( static_cast<QsciScintilla::WhitespaceVisibility>(mSciSettings->getWhiteSpaceVisibleMode()) );
    } else {
        this->setWhitespaceVisibility( QsciScintilla::WsInvisible);
    }
}

void Editor::onWrapModeEnabledChanged(bool val)
{
    if(val) {
        this->setWrapMode( static_cast<QsciScintilla::WrapMode>(mSciSettings->getWrapMode()));
    } else {
        this->setWrapMode(QsciScintilla::WrapNone);
    }
}
