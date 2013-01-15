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
 *  @file       qtscintilla.h
 *  @brief      QtScintilla class interface.
 */



#ifndef __QT_SCINTILLA_H_
 #define __QT_SCINTILLA_H_


#include "Qsci/qsciscintilla.h"


class QtScintilla : public QsciScintilla
{
    Q_OBJECT

public:
    explicit QtScintilla(QWidget *parent = 0);


public slots:
    

signals:
    void cursorLineChanged(int line);
    void linesChanged(int lines);

protected:

private slots:
    void onLinesChanged();
    void onCursorPositionChanged(int line, int index);

private:
    int mCursorLine;
};

#endif // __QT_SCINTILLA_H_
