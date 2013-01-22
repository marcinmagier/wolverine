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

#include "qtcolorbutton.h"
#include "qtfontbutton.h"
#include "Qsci/qscilexer.h"

#include <QScrollArea>
#include <QGridLayout>
#include <QSettings>


using namespace Wolverine;



EditorLexerManagerWidget::EditorLexerManagerWidget(QMap<QString, EditorLexerCfg *> &lexerMap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorLexerManagerWidget),
    mLexerMap(lexerMap)
{
    ui->setupUi(this);

    ui->cmbLexer->addItems(mLexerMap.keys());

    mScrollArea = new QScrollArea();
    mScrollArea->setFrameShape(QFrame::NoFrame);
    ui->tabWidget->insertTab(0, mScrollArea, "Styles");
    ui->tabWidget->setCurrentIndex(0);

    mScrollArea->setWidgetResizable(true);
    mScrollArea->setWidget(getLexerStyles("Normal Text", mLexerMap["Normal Text"]));

}

EditorLexerManagerWidget::~EditorLexerManagerWidget()
{
    delete ui;
    delete mScrollArea;

}


QWidget* EditorLexerManagerWidget::getLexerStyles(const QString &name, EditorLexerCfg *eLexer)
{
    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout(widget);


    if(!eLexer->lexer) {
        QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");
        qset.beginGroup(name);
        eLexer->createFunction(eLexer, &qset);
        qset.endGroup();
    }

    QLabel *lblDefault = new QLabel("default");
    layout->addWidget(lblDefault, 0, 0);

    QtFontButton *btnDefaultFont = new QtFontButton();
    btnDefaultFont->setFont(eLexer->lexer->defaultFont());
    btnDefaultFont->setMinimumHeight(21);
    layout->addWidget(btnDefaultFont, 0, 2);

    QtColorButton *btnDefaultFgColor = new QtColorButton();
    btnDefaultFgColor->setColor(eLexer->lexer->defaultColor());
    btnDefaultFgColor->setMaximumSize(21, 21);
    layout->addWidget(btnDefaultFgColor, 0, 3);

    QtColorButton *btnDefaultBgColor = new QtColorButton();
    btnDefaultBgColor->setColor(eLexer->lexer->defaultPaper());
    btnDefaultBgColor->setMaximumSize(21, 21);
    layout->addWidget(btnDefaultBgColor, 0, 4);

    layout->setRowMinimumHeight(1, 20);

    QLabel *lblFont = new QLabel("Font");
    layout->addWidget(lblFont, 2, 2);
    QLabel *lblFg = new QLabel("Fg");
    layout->addWidget(lblFg, 2, 3);
    QLabel *lblBg = new QLabel("Bg");
    layout->addWidget(lblBg, 2, 4);
    QLabel *lblEol = new QLabel("Fill EoL");
    layout->addWidget(lblEol, 2, 6);

    foreach(int style, eLexer->styles) {
        QLabel *lblStyleName = new QLabel(eLexer->lexer->description(style));
        layout->addWidget(lblStyleName, style+3, 0);

        QtFontButton *btnFont = new QtFontButton();
        btnFont->setFont(eLexer->lexer->font(style));
        btnFont->setMinimumHeight(21);
        layout->addWidget(btnFont, style+3, 2);

        QtColorButton *btnFgColor = new QtColorButton();
        btnFgColor->setColor(eLexer->lexer->color(style));
        btnFgColor->setMaximumSize(21, 21);
        layout->addWidget(btnFgColor, style+3, 3);

        QtColorButton *btnBgColor = new QtColorButton();
        btnBgColor->setColor(eLexer->lexer->paper(style));
        btnBgColor->setMaximumSize(21, 21);
        layout->addWidget(btnBgColor, style+3, 4);

        QCheckBox *checkFillEol = new QCheckBox();
        checkFillEol->setChecked(eLexer->lexer->defaultEolFill(style));
        checkFillEol->setMaximumWidth(50);
        layout->addWidget(checkFillEol, style+3, 6);
    }

    layout->setSpacing(12);
    layout->setColumnMinimumWidth(1, 20);
    layout->setColumnMinimumWidth(5, 20);

    return widget;
}
