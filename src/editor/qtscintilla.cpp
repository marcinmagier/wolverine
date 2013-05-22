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

#include <QDebug>

#include <cctype>

/**
 *  Constructor
 *
 * @param parent
 */
QtScintilla::QtScintilla(QWidget *parent) :
    QsciScintilla(parent)
{
    mCursorLine = 0;
    mEndAtLastLine = false;

    connect( this, SIGNAL(linesChanged()),
             this, SLOT(onLinesChanged()) );
    connect( this, SIGNAL(cursorPositionChanged(int,int)),
             this, SLOT(onCursorPositionChanged(int,int)) );

    SendScintilla(SCI_SETSCROLLWIDTHTRACKING, true);
    SendScintilla(SCI_SETSCROLLWIDTH, 10);
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



void QtScintilla::setIndicatorStyle(IndicatorStyle style, const QColor &color, int alpha, int alphaLine, int indicatorNumber)
{
    SendScintilla(SCI_INDICSETSTYLE, indicatorNumber, style);
    SendScintilla(SCI_INDICSETUNDER, indicatorNumber, true);
    SendScintilla(SCI_INDICSETFORE, indicatorNumber, color);
    SendScintilla(SCI_INDICSETALPHA, indicatorNumber, alpha);
    SendScintilla(SCI_INDICSETOUTLINEALPHA, indicatorNumber, alphaLine);
}


void QtScintilla::clearIndicator(int indicatorNumber)
{
    QsciScintilla::clearIndicatorRange(0, length(), indicatorNumber);
}


bool QtScintilla::isSignleWordSelected()
{
    int posFrom, posTo;
    getSelection(&posFrom, &posTo);

    if(posFrom == posTo)
        return false;

    char pre = getChar(posFrom-1);
    char post = getChar(posTo);

    if(!std::isalnum(pre) && !std::isalnum(post))
        return true;

    return false;
}

bool QtScintilla::isEndAtLastLineSet()
{
    return SendScintilla(SCI_GETENDATLASTLINE);
}

void QtScintilla::setEndAtLastLine(bool enabled)
{
    SendScintilla(SCI_SETENDATLASTLINE, enabled);
}



void QtScintilla::onLinesChanged()
{
    emit linesChanged(this->lines());
}

void QtScintilla::resizeEvent(QResizeEvent *e)
{
    QsciScintilla::resizeEvent(e);
    emit sizeChanged();
}


char QtScintilla::getChar(int pos)
{

    return SendScintilla(SCI_GETCHARAT, pos);
}


void QtScintilla::onCursorPositionChanged(int line, int index)
{
    if(mCursorLine != line) {
        mCursorLine = line;
        emit cursorLineChanged(mCursorLine);
    }
}
