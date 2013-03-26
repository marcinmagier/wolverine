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
 *  @file       qtscintilla.cpp
 *  @brief      QtScintilla class implementation.
 */


#include "qtscintilla.h"

#include <QScrollBar>


/**
 *  Constructor
 *
 * @param parent
 */
QtScintilla::QtScintilla(QWidget *parent) :
    QsciScintilla(parent)
{
    mCursorLine = 0;

    connect( this, SIGNAL(linesChanged()),
             this, SLOT(onLinesChanged()) );
    connect( this, SIGNAL(cursorPositionChanged(int,int)),
             this, SLOT(onCursorPositionChanged(int,int)) );
}


int QtScintilla::linesVisible()
{
    return SendScintilla(SCI_LINESONSCREEN);
}



void QtScintilla::updateScrollH(int range)
{
    QScrollBar *scrollBar = horizontalScrollBar();
    scrollBar->setValue(scrollBar->value() + range);
}

void QtScintilla::updateScrollV(int range)
{
    QScrollBar *scrollBar = verticalScrollBar();
    scrollBar->setValue(scrollBar->value() + range);
}







void QtScintilla::onLinesChanged()
{
    emit linesChanged(this->lines());
}


void QtScintilla::onCursorPositionChanged(int line, int index)
{
    if(mCursorLine != line) {
        mCursorLine = line;
        emit cursorLineChanged(mCursorLine);
    }
}
