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
class QSettings;
class QsciLexer;

namespace Wolverine
{
class EditorLexerCfg;
}

typedef void (*pfCreateLexer)(Wolverine::EditorLexerCfg*, QSettings*);
typedef void (*pfSaveLexer)(Wolverine::EditorLexerCfg*, QSettings*);




namespace Wolverine
{


class EditorLexerCfg
{
public:

    explicit EditorLexerCfg(pfCreateLexer createFunct, pfSaveLexer saveFunct, bool available = false);
    ~EditorLexerCfg();

    QsciLexer *lexer;
    pfCreateLexer createFunction;
    pfSaveLexer saveFunction;
    QList<int> styles;
    bool isAvailable;

};

}



void createLexCPP(Wolverine::EditorLexerCfg *eLexer, QSettings *qset);
void saveLexCPP(Wolverine::EditorLexerCfg *eLexer, QSettings *qset);

void createLexPython(Wolverine::EditorLexerCfg *eLexer, QSettings *qset);
void saveLexPython(Wolverine::EditorLexerCfg *eLexer, QSettings *qset);


#endif // __W_EDITOR_LEXER_CFG_H_
