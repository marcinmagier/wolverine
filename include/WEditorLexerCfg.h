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
 *  @file       WEditorLexerCfg.h
 *  @brief      Wolverine::EditorLexerCfg class interface.
 */




#ifndef __W_EDITOR_LEXER_CFG_H_
 #define __W_EDITOR_LEXER_CFG_H_


#include <QList>

class QString;
class QsciLexer;

namespace Wolverine
{
class EditorLexerCfg;
}

typedef void (*pfCreateLexer)(Wolverine::EditorLexerCfg*);




namespace Wolverine
{


class EditorLexerCfg
{
public:

    explicit EditorLexerCfg(pfCreateLexer createFunct, bool available = false);

    ~EditorLexerCfg();

    QsciLexer *lexer;
    pfCreateLexer createFunction;
    QList<int> styles;
    QList<QString> fileNamesPatterns;
    QList<QString> fileFirstLinePatterns;
    bool isAvailable;

};

}


void createLexNormalText(Wolverine::EditorLexerCfg *eLexer);

void createLexBash(Wolverine::EditorLexerCfg *eLexer);

void createLexCPP(Wolverine::EditorLexerCfg *eLexer);

void createLexHTML(Wolverine::EditorLexerCfg *eLexer);

void createLexJava(Wolverine::EditorLexerCfg *eLexer);

void createLexPython(Wolverine::EditorLexerCfg *eLexer);


#endif // __W_EDITOR_LEXER_CFG_H_
