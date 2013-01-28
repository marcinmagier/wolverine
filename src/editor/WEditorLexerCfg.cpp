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
#include "qscilexercpp.h"
#include "qscilexerjava.h"
#include "qscilexerpython.h"

#include <QString>
#include <QSettings>

#include <QDebug>



using namespace Wolverine;


static void readCommonSettings(EditorLexerCfg *eLexer, QSettings *qset);
static void saveCommonSettings(EditorLexerCfg *eLexer, QSettings *qset);





EditorLexerCfg::EditorLexerCfg(pfCreateLexer createFunct, pfSaveLexer saveFunct, pfCopyLexer copyFunct, bool available) :
    lexer(0),
    createFunction(createFunct),
    saveFunction(saveFunct),
    copyFunction(copyFunct),
    isAvailable(available)
{

}

EditorLexerCfg::~EditorLexerCfg()
{
    delete lexer;
}




void readCommonSettings(EditorLexerCfg *eLexer, QSettings *qset)
{
    if(qset->contains("def_font")) {
        QFont font;
        if(font.fromString( qset->value("def_font").toString()) )
            eLexer->lexer->setDefaultFont(font);
    }
    if(qset->contains("def_fgcolor"))
        eLexer->lexer->setDefaultColor( QColor(qset->value("def_fgcolor").toString()) );
    if(qset->contains("def_bgcolor"))
        eLexer->lexer->setDefaultPaper( QColor(qset->value("def_bgcolor").toString()) );

    foreach(int style, eLexer->styles) {
        QString styleGroup = eLexer->lexer->description(style).replace(" ", "_");
        qset->beginGroup(styleGroup);
        if(qset->contains("font")) {
            QFont font;
            if( font.fromString(qset->value("font").toString()) )
                eLexer->lexer->setFont( font, style);
        }
        if(qset->contains("fgcolor"))
            eLexer->lexer->setColor( QColor(qset->value("fgcolor").toString()), style);
        if(qset->contains("bgcolor"))
            eLexer->lexer->setPaper( QColor(qset->value("bgcolor").toString()), style);
        if(qset->contains("filleol"))
            eLexer->lexer->setEolFill( qset->value("filleol").toBool(), style);
        qset->endGroup();
    }
}

void saveCommonSettings(EditorLexerCfg *eLexer, QSettings *qset)
{
    qset->setValue( "def_font", QVariant::fromValue(eLexer->lexer->defaultFont().toString()) );
    qset->setValue( "def_fgcolor", QVariant::fromValue(eLexer->lexer->defaultColor().name()) );
    qset->setValue( "def_bgcolor", QVariant::fromValue(eLexer->lexer->defaultPaper().name()) );

    foreach(int style, eLexer->styles) {
        QString styleGroup = eLexer->lexer->description(style).replace(" ", "_");
        qset->beginGroup(styleGroup);
        qset->setValue( "font", QVariant::fromValue(eLexer->lexer->font(style).toString()) );
        qset->setValue( "fgcolor", QVariant::fromValue(eLexer->lexer->color(style).name()) );
        qset->setValue( "bgcolor", QVariant::fromValue(eLexer->lexer->paper(style).name()) );
        qset->setValue( "filleol", QVariant::fromValue(eLexer->lexer->eolFill(style)) );
        qset->endGroup();
    }

}

void copyCommonSettings(EditorLexerCfg *from, EditorLexerCfg *to)
{
    to->styles = from->styles;

    to->lexer->setDefaultFont(from->lexer->defaultFont());
    to->lexer->setDefaultColor(from->lexer->defaultColor());
    to->lexer->setDefaultPaper(from->lexer->defaultPaper());

    foreach(int style, from->styles) {
        to->lexer->setFont(from->lexer->font(style), style);
        to->lexer->setColor(from->lexer->color(style), style);
        to->lexer->setPaper(from->lexer->paper(style), style);
        to->lexer->setEolFill(from->lexer->eolFill(style), style);
    }

}





void createLexCPP(EditorLexerCfg *eLexer, QSettings *qset)
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

                   << QsciLexerCPP::InactiveDefault
                   << QsciLexerCPP::InactiveComment
                   << QsciLexerCPP::InactiveCommentLine
                   << QsciLexerCPP::InactiveCommentDoc
                   << QsciLexerCPP::InactiveNumber
                   << QsciLexerCPP::InactiveKeyword
                   << QsciLexerCPP::InactiveDoubleQuotedString
                   << QsciLexerCPP::InactiveSingleQuotedString
                   << QsciLexerCPP::InactiveUUID
                   << QsciLexerCPP::InactivePreProcessor
                   << QsciLexerCPP::InactiveOperator
                   << QsciLexerCPP::InactiveIdentifier
                   << QsciLexerCPP::InactiveUnclosedString
                   << QsciLexerCPP::InactiveVerbatimString
                   << QsciLexerCPP::InactiveRegex
                   << QsciLexerCPP::InactiveCommentLineDoc
                   << QsciLexerCPP::InactiveKeywordSet2
                   << QsciLexerCPP::InactiveCommentDocKeyword
                   << QsciLexerCPP::InactiveCommentDocKeywordError
                   << QsciLexerCPP::InactiveGlobalClass
                   << QsciLexerCPP::InactiveRawString ;

    readCommonSettings(eLexer, qset);
}
void saveLexCPP(Wolverine::EditorLexerCfg *eLexer, QSettings *qset)
{
    saveCommonSettings(eLexer, qset);
}
void copyLexCPP(EditorLexerCfg *from, EditorLexerCfg *to)
{
    if((from->lexer) && (to->lexer == 0)) {
        to->lexer = new QsciLexerCPP();
    }
    copyCommonSettings(from, to);
}


void createLexJava(EditorLexerCfg *eLexer, QSettings *qset)
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

                   << QsciLexerJava::InactiveDefault
                   << QsciLexerJava::InactiveComment
                   << QsciLexerJava::InactiveCommentLine
                   << QsciLexerJava::InactiveCommentDoc
                   << QsciLexerJava::InactiveNumber
                   << QsciLexerJava::InactiveKeyword
                   << QsciLexerJava::InactiveDoubleQuotedString
                   << QsciLexerJava::InactiveSingleQuotedString
                   << QsciLexerJava::InactiveUUID
                   << QsciLexerJava::InactivePreProcessor
                   << QsciLexerJava::InactiveOperator
                   << QsciLexerJava::InactiveIdentifier
                   << QsciLexerJava::InactiveUnclosedString
                   << QsciLexerJava::InactiveVerbatimString
                   << QsciLexerJava::InactiveRegex
                   << QsciLexerJava::InactiveCommentLineDoc
                   << QsciLexerJava::InactiveKeywordSet2
                   << QsciLexerJava::InactiveCommentDocKeyword
                   << QsciLexerJava::InactiveCommentDocKeywordError
                   << QsciLexerJava::InactiveGlobalClass
                   << QsciLexerJava::InactiveRawString ;

    readCommonSettings(eLexer, qset);
}
void saveLexJava(Wolverine::EditorLexerCfg *eLexer, QSettings *qset)
{
    saveCommonSettings(eLexer, qset);
}
void copyLexJava(EditorLexerCfg *from, EditorLexerCfg *to)
{
    if((from->lexer) && (to->lexer == 0)) {
        to->lexer = new QsciLexerJava();
    }
    copyCommonSettings(from, to);
}


void createLexPython(EditorLexerCfg *eLexer, QSettings *qset)
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

    readCommonSettings(eLexer, qset);
}
void saveLexPython(Wolverine::EditorLexerCfg *eLexer, QSettings *qset)
{
    saveCommonSettings(eLexer, qset);
}
void copyLexPython(EditorLexerCfg *from, EditorLexerCfg *to)
{
    if((from->lexer) && (to->lexer == 0)) {
        to->lexer = new QsciLexerPython();
    }
    copyCommonSettings(from, to);
}
