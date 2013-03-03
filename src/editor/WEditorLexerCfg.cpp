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
#include "qscilexerhtml.h"
#include "qscilexerjava.h"
#include "qscilexerjavascript.h"
#include "qscilexerpython.h"
#include "qscilexerxml.h"

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
                   << QsciLexerCPP::RawString
                   << QsciLexerCPP::TripleQuotedVerbatimString
                   << QsciLexerCPP::HashQuotedString
                   << QsciLexerCPP::PreProcessorComment;
}


void createLexHTML(EditorLexerCfg *eLexer)
{
    QsciLexerHTML *lexer = new QsciLexerHTML();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerHTML::Default
                   << QsciLexerHTML::Tag
                   << QsciLexerHTML::UnknownTag
                   << QsciLexerHTML::Attribute
                   << QsciLexerHTML::UnknownAttribute
                   << QsciLexerHTML::HTMLNumber
                   << QsciLexerHTML::HTMLDoubleQuotedString
                   << QsciLexerHTML::HTMLSingleQuotedString
                   << QsciLexerHTML::OtherInTag
                   << QsciLexerHTML::HTMLComment
                   << QsciLexerHTML::Entity
                   << QsciLexerHTML::XMLTagEnd
                   << QsciLexerHTML::XMLStart
                   << QsciLexerHTML::XMLEnd
                   << QsciLexerHTML::Script
                   << QsciLexerHTML::ASPAtStart
                   << QsciLexerHTML::ASPStart
                   << QsciLexerHTML::CDATA
                   << QsciLexerHTML::PHPStart
                   << QsciLexerHTML::HTMLValue
                   << QsciLexerHTML::ASPXCComment

                   << QsciLexerHTML::SGMLDefault
                   << QsciLexerHTML::SGMLCommand
                   << QsciLexerHTML::SGMLParameter
                   << QsciLexerHTML::SGMLDoubleQuotedString
                   << QsciLexerHTML::SGMLSingleQuotedString
                   << QsciLexerHTML::SGMLError
                   << QsciLexerHTML::SGMLSpecial
                   << QsciLexerHTML::SGMLEntity
                   << QsciLexerHTML::SGMLComment
                   << QsciLexerHTML::SGMLParameterComment
                   << QsciLexerHTML::SGMLBlockDefault

                   << QsciLexerHTML::JavaScriptStart
                   << QsciLexerHTML::JavaScriptDefault
                   << QsciLexerHTML::JavaScriptComment
                   << QsciLexerHTML::JavaScriptCommentLine
                   << QsciLexerHTML::JavaScriptCommentDoc
                   << QsciLexerHTML::JavaScriptNumber
                   << QsciLexerHTML::JavaScriptWord
                   << QsciLexerHTML::JavaScriptKeyword
                   << QsciLexerHTML::JavaScriptDoubleQuotedString
                   << QsciLexerHTML::JavaScriptSingleQuotedString
                   << QsciLexerHTML::JavaScriptSymbol
                   << QsciLexerHTML::JavaScriptUnclosedString
                   << QsciLexerHTML::JavaScriptRegex

                   << QsciLexerHTML::ASPJavaScriptStart
                   << QsciLexerHTML::ASPJavaScriptDefault
                   << QsciLexerHTML::ASPJavaScriptComment
                   << QsciLexerHTML::ASPJavaScriptCommentLine
                   << QsciLexerHTML::ASPJavaScriptCommentDoc
                   << QsciLexerHTML::ASPJavaScriptNumber
                   << QsciLexerHTML::ASPJavaScriptWord
                   << QsciLexerHTML::ASPJavaScriptKeyword
                   << QsciLexerHTML::ASPJavaScriptDoubleQuotedString
                   << QsciLexerHTML::ASPJavaScriptSingleQuotedString
                   << QsciLexerHTML::ASPJavaScriptSymbol
                   << QsciLexerHTML::ASPJavaScriptUnclosedString
                   << QsciLexerHTML::ASPJavaScriptRegex

                   << QsciLexerHTML::VBScriptStart
                   << QsciLexerHTML::VBScriptDefault
                   << QsciLexerHTML::VBScriptComment
                   << QsciLexerHTML::VBScriptNumber
                   << QsciLexerHTML::VBScriptKeyword
                   << QsciLexerHTML::VBScriptString
                   << QsciLexerHTML::VBScriptIdentifier
                   << QsciLexerHTML::VBScriptUnclosedString

                   << QsciLexerHTML::ASPVBScriptStart
                   << QsciLexerHTML::ASPVBScriptDefault
                   << QsciLexerHTML::ASPVBScriptComment
                   << QsciLexerHTML::ASPVBScriptNumber
                   << QsciLexerHTML::ASPVBScriptKeyword
                   << QsciLexerHTML::ASPVBScriptString
                   << QsciLexerHTML::ASPVBScriptIdentifier
                   << QsciLexerHTML::ASPVBScriptUnclosedString

                   << QsciLexerHTML::PythonStart
                   << QsciLexerHTML::PythonDefault
                   << QsciLexerHTML::PythonComment
                   << QsciLexerHTML::PythonNumber
                   << QsciLexerHTML::PythonDoubleQuotedString
                   << QsciLexerHTML::PythonSingleQuotedString
                   << QsciLexerHTML::PythonKeyword
                   << QsciLexerHTML::PythonTripleSingleQuotedString
                   << QsciLexerHTML::PythonTripleDoubleQuotedString
                   << QsciLexerHTML::PythonClassName
                   << QsciLexerHTML::PythonFunctionMethodName
                   << QsciLexerHTML::PythonOperator
                   << QsciLexerHTML::PythonIdentifier

                   << QsciLexerHTML::ASPPythonStart
                   << QsciLexerHTML::ASPPythonDefault
                   << QsciLexerHTML::ASPPythonComment
                   << QsciLexerHTML::ASPPythonNumber
                   << QsciLexerHTML::ASPPythonDoubleQuotedString
                   << QsciLexerHTML::ASPPythonSingleQuotedString
                   << QsciLexerHTML::ASPPythonKeyword
                   << QsciLexerHTML::ASPPythonTripleSingleQuotedString
                   << QsciLexerHTML::ASPPythonTripleDoubleQuotedString
                   << QsciLexerHTML::ASPPythonClassName
                   << QsciLexerHTML::ASPPythonFunctionMethodName
                   << QsciLexerHTML::ASPPythonOperator
                   << QsciLexerHTML::ASPPythonIdentifier

                   << QsciLexerHTML::PHPDefault
                   << QsciLexerHTML::PHPDoubleQuotedString
                   << QsciLexerHTML::PHPSingleQuotedString
                   << QsciLexerHTML::PHPKeyword
                   << QsciLexerHTML::PHPNumber
                   << QsciLexerHTML::PHPVariable
                   << QsciLexerHTML::PHPComment
                   << QsciLexerHTML::PHPCommentLine
                   << QsciLexerHTML::PHPDoubleQuotedVariable
                   << QsciLexerHTML::PHPOperator;
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
                   << QsciLexerJava::RawString
                   << QsciLexerJava::TripleQuotedVerbatimString
                   << QsciLexerJava::HashQuotedString
                   << QsciLexerJava::PreProcessorComment;
}


void createLexJavaScript(EditorLexerCfg *eLexer)
{
    QsciLexerJavaScript *lexer = new QsciLexerJavaScript();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerJavaScript::Default
                   << QsciLexerJavaScript::Comment
                   << QsciLexerJavaScript::CommentLine
                   << QsciLexerJavaScript::CommentDoc
                   << QsciLexerJavaScript::Number
                   << QsciLexerJavaScript::Keyword
                   << QsciLexerJavaScript::DoubleQuotedString
                   << QsciLexerJavaScript::SingleQuotedString
                   << QsciLexerJavaScript::UUID
                   << QsciLexerJavaScript::PreProcessor
                   << QsciLexerJavaScript::Operator
                   << QsciLexerJavaScript::Identifier
                   << QsciLexerJavaScript::UnclosedString
                   << QsciLexerJavaScript::VerbatimString
                   << QsciLexerJavaScript::Regex
                   << QsciLexerJavaScript::CommentLineDoc
                   << QsciLexerJavaScript::KeywordSet2
                   << QsciLexerJavaScript::CommentDocKeyword
                   << QsciLexerJavaScript::CommentDocKeywordError
                   << QsciLexerJavaScript::GlobalClass
                   << QsciLexerJavaScript::RawString
                   << QsciLexerJavaScript::TripleQuotedVerbatimString
                   << QsciLexerJavaScript::HashQuotedString
                   << QsciLexerJavaScript::PreProcessorComment;
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


void createLexXML(EditorLexerCfg *eLexer)
{
    QsciLexerXML *lexer = new QsciLexerXML();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerXML::Default
                   << QsciLexerXML::Tag
                   << QsciLexerXML::UnknownTag
                   << QsciLexerXML::Attribute
                   << QsciLexerXML::UnknownAttribute
                   << QsciLexerXML::HTMLNumber
                   << QsciLexerXML::HTMLDoubleQuotedString
                   << QsciLexerXML::HTMLSingleQuotedString
                   << QsciLexerXML::OtherInTag
                   << QsciLexerXML::HTMLComment
                   << QsciLexerXML::Entity
                   << QsciLexerXML::XMLTagEnd
                   << QsciLexerXML::XMLStart
                   << QsciLexerXML::XMLEnd
                   << QsciLexerXML::Script
                   << QsciLexerXML::ASPAtStart
                   << QsciLexerXML::ASPStart
                   << QsciLexerXML::CDATA
                   << QsciLexerXML::PHPStart
                   << QsciLexerXML::HTMLValue
                   << QsciLexerXML::ASPXCComment

                   << QsciLexerXML::SGMLDefault
                   << QsciLexerXML::SGMLCommand
                   << QsciLexerXML::SGMLParameter
                   << QsciLexerXML::SGMLDoubleQuotedString
                   << QsciLexerXML::SGMLSingleQuotedString
                   << QsciLexerXML::SGMLError
                   << QsciLexerXML::SGMLSpecial
                   << QsciLexerXML::SGMLEntity
                   << QsciLexerXML::SGMLComment
                   << QsciLexerXML::SGMLParameterComment
                   << QsciLexerXML::SGMLBlockDefault

                   << QsciLexerXML::JavaScriptStart
                   << QsciLexerXML::JavaScriptDefault
                   << QsciLexerXML::JavaScriptComment
                   << QsciLexerXML::JavaScriptCommentLine
                   << QsciLexerXML::JavaScriptCommentDoc
                   << QsciLexerXML::JavaScriptNumber
                   << QsciLexerXML::JavaScriptWord
                   << QsciLexerXML::JavaScriptKeyword
                   << QsciLexerXML::JavaScriptDoubleQuotedString
                   << QsciLexerXML::JavaScriptSingleQuotedString
                   << QsciLexerXML::JavaScriptSymbol
                   << QsciLexerXML::JavaScriptUnclosedString
                   << QsciLexerXML::JavaScriptRegex

                   << QsciLexerXML::ASPJavaScriptStart
                   << QsciLexerXML::ASPJavaScriptDefault
                   << QsciLexerXML::ASPJavaScriptComment
                   << QsciLexerXML::ASPJavaScriptCommentLine
                   << QsciLexerXML::ASPJavaScriptCommentDoc
                   << QsciLexerXML::ASPJavaScriptNumber
                   << QsciLexerXML::ASPJavaScriptWord
                   << QsciLexerXML::ASPJavaScriptKeyword
                   << QsciLexerXML::ASPJavaScriptDoubleQuotedString
                   << QsciLexerXML::ASPJavaScriptSingleQuotedString
                   << QsciLexerXML::ASPJavaScriptSymbol
                   << QsciLexerXML::ASPJavaScriptUnclosedString
                   << QsciLexerXML::ASPJavaScriptRegex

                   << QsciLexerXML::VBScriptStart
                   << QsciLexerXML::VBScriptDefault
                   << QsciLexerXML::VBScriptComment
                   << QsciLexerXML::VBScriptNumber
                   << QsciLexerXML::VBScriptKeyword
                   << QsciLexerXML::VBScriptString
                   << QsciLexerXML::VBScriptIdentifier
                   << QsciLexerXML::VBScriptUnclosedString

                   << QsciLexerXML::ASPVBScriptStart
                   << QsciLexerXML::ASPVBScriptDefault
                   << QsciLexerXML::ASPVBScriptComment
                   << QsciLexerXML::ASPVBScriptNumber
                   << QsciLexerXML::ASPVBScriptKeyword
                   << QsciLexerXML::ASPVBScriptString
                   << QsciLexerXML::ASPVBScriptIdentifier
                   << QsciLexerXML::ASPVBScriptUnclosedString

                   << QsciLexerXML::PythonStart
                   << QsciLexerXML::PythonDefault
                   << QsciLexerXML::PythonComment
                   << QsciLexerXML::PythonNumber
                   << QsciLexerXML::PythonDoubleQuotedString
                   << QsciLexerXML::PythonSingleQuotedString
                   << QsciLexerXML::PythonKeyword
                   << QsciLexerXML::PythonTripleSingleQuotedString
                   << QsciLexerXML::PythonTripleDoubleQuotedString
                   << QsciLexerXML::PythonClassName
                   << QsciLexerXML::PythonFunctionMethodName
                   << QsciLexerXML::PythonOperator
                   << QsciLexerXML::PythonIdentifier

                   << QsciLexerXML::ASPPythonStart
                   << QsciLexerXML::ASPPythonDefault
                   << QsciLexerXML::ASPPythonComment
                   << QsciLexerXML::ASPPythonNumber
                   << QsciLexerXML::ASPPythonDoubleQuotedString
                   << QsciLexerXML::ASPPythonSingleQuotedString
                   << QsciLexerXML::ASPPythonKeyword
                   << QsciLexerXML::ASPPythonTripleSingleQuotedString
                   << QsciLexerXML::ASPPythonTripleDoubleQuotedString
                   << QsciLexerXML::ASPPythonClassName
                   << QsciLexerXML::ASPPythonFunctionMethodName
                   << QsciLexerXML::ASPPythonOperator
                   << QsciLexerXML::ASPPythonIdentifier

                   << QsciLexerXML::PHPDefault
                   << QsciLexerXML::PHPDoubleQuotedString
                   << QsciLexerXML::PHPSingleQuotedString
                   << QsciLexerXML::PHPKeyword
                   << QsciLexerXML::PHPNumber
                   << QsciLexerXML::PHPVariable
                   << QsciLexerXML::PHPComment
                   << QsciLexerXML::PHPCommentLine
                   << QsciLexerXML::PHPDoubleQuotedVariable
                   << QsciLexerXML::PHPOperator;
}
