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

    mScrollAreaLayout = new QGridLayout(mScrollArea);
    mScrollArea->setWidgetResizable(false);
    mScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
/*
    QLabel *lblDefault = new QLabel("default");
    QtFontButton *btnDefaultFont = new QtFontButton();
    QtColorButton *btnDefaultFgColor = new QtColorButton();
    QtColorButton *btnDefaultBgColor = new QtColorButton();

    mScrollAreaLayout->addWidget(lblDefault, 0, 0);
    mScrollAreaLayout->addWidget(btnDefaultFont, 0, 2);
    mScrollAreaLayout->addWidget(btnDefaultFgColor, 0, 4);
    btnDefaultFgColor->setMaximumSize(21, 21);
    mScrollAreaLayout->addWidget(btnDefaultBgColor, 0, 5);
    btnDefaultBgColor->setMaximumSize(21, 21);

    QLabel *lblStyle1 = new QLabel("Style1");
    QtFontButton *btnStyle1Font = new QtFontButton();
    QtColorButton *btnStyle1FgColor = new QtColorButton();
    btnStyle1FgColor->setMaximumSize(21, 21);
    QtColorButton *btnStyle1BgColor = new QtColorButton();
    btnStyle1BgColor->setMaximumSize(21, 21);

    mScrollAreaLayout->addWidget(lblStyle1, 2, 0);
    mScrollAreaLayout->addWidget(btnStyle1Font, 2, 2);
    mScrollAreaLayout->addWidget(btnStyle1FgColor, 2, 4);
    mScrollAreaLayout->addWidget(btnStyle1BgColor, 2, 5);
*/
    setupLexerStyles("Normal Text", mLexerMap["Normal Text"]);
}

EditorLexerManagerWidget::~EditorLexerManagerWidget()
{
    delete ui;
    delete mScrollAreaLayout;
    delete mScrollArea;

}


void EditorLexerManagerWidget::setupLexerStyles(const QString &name, EditorLexerCfg *eLexer)
{
    if(!eLexer->lexer) {
        QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");
        qset.beginGroup(name);
        eLexer->createFunction(eLexer, &qset);
        qset.endGroup();
    }

    foreach(int style, eLexer->styles) {
        QLabel *lblStyle = new QLabel(eLexer->lexer->description(style));
        mScrollAreaLayout->addWidget(lblStyle, style, 0);

        QtFontButton *btnFont = new QtFontButton();
        btnFont->setFont(eLexer->lexer->font(style));
        btnFont->setMinimumHeight(21);
        mScrollAreaLayout->addWidget(btnFont, style, 2);

        QtColorButton *btnFgColor = new QtColorButton();
        btnFgColor->setColor(eLexer->lexer->color(style));
        btnFgColor->setMaximumSize(21, 21);
        mScrollAreaLayout->addWidget(btnFgColor, style, 4);

        QtColorButton *btnBgColor = new QtColorButton();
        btnBgColor->setColor(eLexer->lexer->paper(style));
        btnBgColor->setMaximumSize(21, 21);
        mScrollAreaLayout->addWidget(btnBgColor, style, 5);

        QCheckBox *checkFillEol = new QCheckBox();
        mScrollAreaLayout->addWidget(checkFillEol, style, 7);
        mScrollAreaLayout->setRowMinimumHeight(style, 21);
    }
}
