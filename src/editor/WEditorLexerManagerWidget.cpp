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
#include "Logger.h"

#include <QScrollArea>
#include <QGridLayout>
#include <QSettings>


#include <QDebug>

using namespace Wolverine;



class ColorButton : public QtColorButton
{
public:
    int index;
};


class FontButton : public QtFontButton
{
public:
    int index;
};


class CheckBoxButton : public QCheckBox
{
public:
    int index;
};





EditorLexerManagerWidget::EditorLexerManagerWidget(QMap<QString, EditorLexerCfg *> *lexerMap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorLexerManagerWidget),
    mLexerMap(lexerMap)
{
    ui->setupUi(this);

    ui->cmbLexer->addItems(mLexerMap->keys());
    connect (ui->cmbLexer, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(onLexerChanged(QString)) );

    QString lexName = ui->cmbLexer->currentText();

    ui->checkShowInMenu->setChecked(mLexerMap->value(lexName)->isAvailable);
    connect(ui->checkShowInMenu, SIGNAL(toggled(bool)),
                           this, SLOT(onShowInMenuChanged(bool)) );

    mScrollArea = new QScrollArea();
    mScrollArea->setFrameShape(QFrame::NoFrame);
    mScrollArea->setWidgetResizable(true);
    mScrollArea->setWidget(getLexerStyles(lexName, mLexerMap->value(lexName)));
    ui->tabWidget->insertTab(0, mScrollArea, "Styles");
    ui->tabWidget->setCurrentIndex(0);





}

EditorLexerManagerWidget::~EditorLexerManagerWidget()
{
    delete ui;
    QWidget *widget = mScrollArea->widget();
    delete widget;
    delete mScrollArea;

}


QWidget* EditorLexerManagerWidget::getLexerStyles(const QString &name, EditorLexerCfg *eLexer)
{
    if(eLexer == 0) {
        LOG_ERROR("Lexer unknown");
        return 0;
    }

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

    FontButton *btnDefaultFont = new FontButton();
    btnDefaultFont->setFont(eLexer->lexer->defaultFont());
    btnDefaultFont->index = -1;
    btnDefaultFont->setMinimumHeight(21);
    connect(btnDefaultFont, SIGNAL(fontChanged(QFont)),
                      this, SLOT(onLexerFontChanged(QFont)) );
    layout->addWidget(btnDefaultFont, 0, 2);

    ColorButton *btnDefaultFgColor = new ColorButton();
    btnDefaultFgColor->setColor(eLexer->lexer->defaultColor());
    btnDefaultFgColor->index = -1;
    btnDefaultFgColor->setMaximumSize(21, 21);
    connect(btnDefaultFgColor, SIGNAL(colorChanged(QColor)),
                         this, SLOT(onLexerFgColorChanged(QColor)) );
    layout->addWidget(btnDefaultFgColor, 0, 3);

    ColorButton *btnDefaultBgColor = new ColorButton();
    btnDefaultBgColor->setColor(eLexer->lexer->defaultPaper());
    btnDefaultBgColor->index = -1;
    btnDefaultBgColor->setMaximumSize(21, 21);
    connect(btnDefaultBgColor, SIGNAL(colorChanged(QColor)),
                         this, SLOT(onLexerBgColorChanged(QColor)) );
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

        FontButton *btnFont = new FontButton();
        btnFont->setFont(eLexer->lexer->font(style));
        btnFont->index = style;
        btnFont->setMinimumHeight(21);
        connect(btnFont, SIGNAL(fontChanged(QFont)),
                   this, SLOT(onLexerFontChanged(QFont)) );
        layout->addWidget(btnFont, style+3, 2);

        ColorButton *btnFgColor = new ColorButton();
        btnFgColor->setColor(eLexer->lexer->color(style));
        btnFgColor->index = style;
        btnFgColor->setMaximumSize(21, 21);
        connect(btnFgColor, SIGNAL(colorChanged(QColor)),
                      this, SLOT(onLexerFgColorChanged(QColor)) );
        layout->addWidget(btnFgColor, style+3, 3);

        ColorButton *btnBgColor = new ColorButton();
        btnBgColor->setColor(eLexer->lexer->paper(style));
        btnBgColor->index = style;
        btnBgColor->setMaximumSize(21, 21);
        connect(btnBgColor, SIGNAL(colorChanged(QColor)),
                      this, SLOT(onLexerBgColorChanged(QColor)) );
        layout->addWidget(btnBgColor, style+3, 4);

        CheckBoxButton *checkFillEol = new CheckBoxButton();
        checkFillEol->setChecked(eLexer->lexer->eolFill(style));
        checkFillEol->index = style;
        checkFillEol->setMaximumWidth(50);
        connect(checkFillEol, SIGNAL(toggled(bool)),
                        this, SLOT(onLexerFillEoLChanged(bool)) );
        layout->addWidget(checkFillEol, style+3, 6);
    }

    QSpacerItem *spacer = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(spacer, layout->rowCount(), 0);
    layout->setSpacing(12);
    layout->setColumnMinimumWidth(1, 20);
    layout->setColumnMinimumWidth(5, 20);

    return widget;
}



void EditorLexerManagerWidget::onLexerChanged(const QString &name)
{
    QWidget *widget = mScrollArea->widget();
    delete widget;
    mScrollArea->setWidget(getLexerStyles(name, mLexerMap->value(name)));
    ui->checkShowInMenu->setChecked(mLexerMap->value(name)->isAvailable);
}

void EditorLexerManagerWidget::onLexerFontChanged(const QFont &font)
{
    FontButton *button = dynamic_cast<FontButton*>(sender());
    QString lexName = ui->cmbLexer->currentText();

    if(button->index == -1)
        mLexerMap->value(lexName)->lexer->setDefaultFont(font);
    else
        mLexerMap->value(lexName)->lexer->setFont(font, button->index);
}

void EditorLexerManagerWidget::onLexerFgColorChanged(const QColor &color)
{
    ColorButton *button = dynamic_cast<ColorButton*>(sender());
    QString lexName = ui->cmbLexer->currentText();

    if(button->index == -1)
        mLexerMap->value(lexName)->lexer->setDefaultColor(color);
    else
        mLexerMap->value(lexName)->lexer->setColor(color, button->index);
}

void EditorLexerManagerWidget::onLexerBgColorChanged(const QColor &color)
{
    ColorButton *button = dynamic_cast<ColorButton*>(sender());
    QString lexName = ui->cmbLexer->currentText();

    if(button->index == -1)
        mLexerMap->value(lexName)->lexer->setDefaultPaper(color);
    else
        mLexerMap->value(lexName)->lexer->setPaper(color, button->index);
}

void EditorLexerManagerWidget::onLexerFillEoLChanged(bool checked)
{
    CheckBoxButton *button = dynamic_cast<CheckBoxButton*>(sender());
    QString lexName = ui->cmbLexer->currentText();

    mLexerMap->value(lexName)->lexer->setEolFill(checked, button->index);
}

void EditorLexerManagerWidget::onShowInMenuChanged(bool checked)
{
    QString lexName = ui->cmbLexer->currentText();
    mLexerMap->value(lexName)->isAvailable = checked;
}
