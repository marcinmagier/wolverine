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

#include "Qsci/qscilexer.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexerpython.h"

#include <QString>
#include <QSettings>

#include <QDebug>



using namespace Wolverine;


static void readCommonSettings(EditorLexerCfg *eLexer, QSettings *qset);
static void saveCommonSettings(EditorLexerCfg *eLexer, QSettings *qset);





EditorLexerCfg::EditorLexerCfg(pfCreateLexer createFunct, pfSaveLexer saveFunct, bool available) :
    lexer(0),
    createFunction(createFunct),
    saveFunction(saveFunct),
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






void createLexCPP(EditorLexerCfg *eLexer, QSettings *qset)
{
    QsciLexerCPP *lexer = new QsciLexerCPP();
    eLexer->lexer = lexer;
    eLexer->styles << QsciLexerCPP::Default
                   << QsciLexerCPP::Comment
                   << QsciLexerCPP::CommentLine
                   << QsciLexerCPP::CommentDoc ;

    readCommonSettings(eLexer, qset);
}
void saveLexCPP(Wolverine::EditorLexerCfg *eLexer, QSettings *qset)
{
    saveCommonSettings(eLexer, qset);
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
