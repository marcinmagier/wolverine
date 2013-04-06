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
 *  @file       WFindOptions.h
 *  @brief      Wolverine::FindOptions class interface.
 */




#ifndef __W_FIND_OPTIONS_H_
 #define __W_FIND_OPTIONS_H_


#include <QString>


namespace Wolverine {


struct FindOptions
{
    FindOptions::FindOptions() :
        isCaseSensitive(false), isWholeWords(false), isRegexp(false),
        isReverseDirection(false), isWrap(false), isInSelection(false),
        isBookmarkLine(false), isInSubDirs(false), isInHiddenDirs(false) { }

    bool isCaseSensitive;
    bool isWholeWords;
    bool isRegexp;
    bool isReverseDirection;
    bool isWrap;
    bool isInSelection;
    bool isBookmarkLine;
    bool isInSubDirs;
    bool isInHiddenDirs;

    QString searchPattern;
    QString replacePattern;
    QString filters;
    QString directory;
};

};


#endif // __W_FIND_OPTIONS_H_
