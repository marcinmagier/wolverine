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
 *  @file       qtfontbutton.cpp
 *  @brief      QtFontButton class implementation.
 */


#include "qtfontbutton.h"

#include <QFontDialog>

#include <QDebug>


#define FONT_BUTTON_LABEL_PATTERN   "%1, %2"

#define FONT_BUTTON_STYLE_PATTERN   "QPushButton {"             \
                                    "font-style: %1;"           \
                                    "font-weight: %2;"          \
                                    "text-decoration: %3;"      \
                                    "}"



/**
 *  Constructor
 *
 * @param parent
 */
QtFontButton::QtFontButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setFont(QFont());

    connect( this, SIGNAL(clicked()),
             this, SLOT(onButtonClicked()) );
}


/**
 *  On button clicked slot
 */
void QtFontButton::onButtonClicked()
{
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok, mFont, this);

    if(ok) {
        this->setFont(newFont);
        emit fontChanged(mFont);
    }
}


/**
 *  Changes button's font
 *
 * @param color
 */
void QtFontButton::setFont(const QFont &font)
{
    mFont = font;
    QString style;
    if(mFont.italic())
        style.append("italic");
    else
        style.append("normal");

    QString weight;
    if(mFont.bold())
        weight.append("bold");
    else
        weight.append("normal");

    QString decoration;
    if(mFont.underline())
        decoration.append(" underline");
    if(mFont.overline())
        decoration.append(" overline");
    if(mFont.strikeOut())
        decoration.append(" line-through");
    if(decoration.isEmpty())
        decoration.append("none");

    this->setStyleSheet( QString(FONT_BUTTON_STYLE_PATTERN).arg(style)
                                                           .arg(weight)
                                                           .arg(decoration) );
    this->setText( QString(FONT_BUTTON_LABEL_PATTERN).arg(font.family())
                                                     .arg(font.pointSize()) );
}
