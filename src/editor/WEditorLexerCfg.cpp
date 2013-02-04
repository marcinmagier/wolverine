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
 *  @file       WEditorLexerCfg.cpp
 *  @brief      Wolverine::EditorLexerCfg class implementation.
 */




#include "WEditorLexerCfg.h"

#include "qscilexer.h"
#include "qscilexerbash.h"
#include "qscilexercpp.h"
#include "qscilexerjava.h"
#include "qscilexerpython.h"

#include <QString>
#include <QSettings>

#include <QDebug>



using namespace Wolverine;



EditorLexerCfg::EditorLexerCfg(pfCreateLexer createFunct, bool available) :
    lexer(0),
    createFunction(createFunct),
    isAvailable(available)
{

}

EditorLexerCfg::~EditorLexerCfg()
{
    delete lexer;
}




void createLexNormalText(EditorLexerCfg *eLexer)
{
    QsciLexerPython *lexer = new QsciLexerPython();
    eLexer->lexer = lexer;
}



void createLexBash(EditorLexerCfg *eLexer)
{
    QsciLexerBash *lexer = new QsciLexerBash();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerBash::Default
                   << QsciLexerBash::Error
                   << QsciLexerBash::Comment
                   << QsciLexerBash::Number
                   << QsciLexerBash::Keyword
                   << QsciLexerBash::DoubleQuotedString
                   << QsciLexerBash::SingleQuotedString
                   << QsciLexerBash::Operator
                   << QsciLexerBash::Identifier
                   << QsciLexerBash::Scalar
                   << QsciLexerBash::ParameterExpansion
                   << QsciLexerBash::Backticks
                   << QsciLexerBash::HereDocumentDelimiter
                   << QsciLexerBash::SingleQuotedHereDocument ;
}


void createLexCPP(EditorLexerCfg *eLexer)
{
    QsciLexerCPP *lexer = new QsciLexerCPP();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerCPP::Default
                   << QsciLexerCPP::Comment
                   << QsciLexerCPP::CommentLine
                   << QsciLexerCPP::CommentDoc
                   << QsciLexerCPP::Number
                   << QsciLexerCPP::Keyword
                   << QsciLexerCPP::DoubleQuotedString
                   << QsciLexerCPP::SingleQuotedString
                   << QsciLexerCPP::UUID
                   << QsciLexerCPP::PreProcessor
                   << QsciLexerCPP::Operator
                   << QsciLexerCPP::Identifier
                   << QsciLexerCPP::UnclosedString
                   << QsciLexerCPP::VerbatimString
                   << QsciLexerCPP::Regex
                   << QsciLexerCPP::CommentLineDoc
                   << QsciLexerCPP::KeywordSet2
                   << QsciLexerCPP::CommentDocKeyword
                   << QsciLexerCPP::CommentDocKeywordError
                   << QsciLexerCPP::GlobalClass
                   << QsciLexerCPP::RawString ;
}


void createLexJava(EditorLexerCfg *eLexer)
{
    QsciLexerJava *lexer = new QsciLexerJava();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerJava::Default
                   << QsciLexerJava::Comment
                   << QsciLexerJava::CommentLine
                   << QsciLexerJava::CommentDoc
                   << QsciLexerJava::Number
                   << QsciLexerJava::Keyword
                   << QsciLexerJava::DoubleQuotedString
                   << QsciLexerJava::SingleQuotedString
                   << QsciLexerJava::UUID
                   << QsciLexerJava::PreProcessor
                   << QsciLexerJava::Operator
                   << QsciLexerJava::Identifier
                   << QsciLexerJava::UnclosedString
                   << QsciLexerJava::VerbatimString
                   << QsciLexerJava::Regex
                   << QsciLexerJava::CommentLineDoc
                   << QsciLexerJava::KeywordSet2
                   << QsciLexerJava::CommentDocKeyword
                   << QsciLexerJava::CommentDocKeywordError
                   << QsciLexerJava::GlobalClass
                   << QsciLexerJava::RawString ;
}



void createLexPython(EditorLexerCfg *eLexer)
{
    QsciLexerPython *lexer = new QsciLexerPython();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerPython::Default
                   << QsciLexerPython::Comment
                   << QsciLexerPython::Number
                   << QsciLexerPython::DoubleQuotedString
                   << QsciLexerPython::SingleQuotedString
                   << QsciLexerPython::Keyword
                   << QsciLexerPython::TripleSingleQuotedString
                   << QsciLexerPython::TripleDoubleQuotedString
                   << QsciLexerPython::ClassName
                   << QsciLexerPython::FunctionMethodName
                   << QsciLexerPython::Operator
                   << QsciLexerPython::Identifier
                   << QsciLexerPython::CommentBlock
                   << QsciLexerPython::UnclosedString
                   << QsciLexerPython::HighlightedIdentifier
                   << QsciLexerPython::Decorator ;
}
