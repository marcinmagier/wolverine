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
 *  @file       WEditorLexerManagerWidget.cpp
 *  @brief      Wolverine::EditorLexerManagerWidget class implementation.
 */



#include "WEditorLexerManagerWidget.h"
#include "ui_WEditorLexerManagerWidget.h"
#include "WEditorLexerCfg.h"
#include "Qsci/qscilexer.h"


using namespace Wolverine;



EditorLexerManagerWidget::EditorLexerManagerWidget(QMap<QString, EditorLexerCfg *> &lexerMap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorLexerManagerWidget),
    mLexerMap(lexerMap)
{
    ui->setupUi(this);

    ui->cmbLexer->addItems(mLexerMap.keys());
    ui->btnDefFont->setFont(QFont("Verdana"));
    ui->btnDefFgColor->setColor(QColor(32, 148, 92));
    ui->btnDefBgColor->setColor(QColor(210, 182, 81));

}

EditorLexerManagerWidget::~EditorLexerManagerWidget()
{
    delete ui;
}
