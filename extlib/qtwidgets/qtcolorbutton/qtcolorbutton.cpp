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
 *  @file       qtcolorbutton.cpp
 *  @brief      QtColorButton class implementation.
 */


#include "qtcolorbutton.h"

#include "QColorDialog"


#define COLOR_BUTTON_STYLE_PATTERN  "QPushButton {"                       \
                                    "background-color: rgb(%1, %2, %3);"  \
                                    "}"



/**
 *  Constructor
 *
 * @param parent
 */
QtColorButton::QtColorButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setColor(QColor());
    this->setAutoFillBackground(true);
    this->setText("");

    connect( this, SIGNAL(clicked()),
             this, SLOT(onButtonClicked()) );
}


/**
 *  On button clicked slot
 */
void QtColorButton::onButtonClicked()
{
    QColor newColor = QColorDialog::getColor(mColor);

    if(newColor.isValid() && newColor!=mColor) {
        this->setColor(newColor);
        emit colorChanged(newColor);
    }
}


/**
 *  Changes button's color
 *
 * @param color
 */
void QtColorButton::setColor(const QColor &color)
{
    mColor = color;
    QString style = QString(COLOR_BUTTON_STYLE_PATTERN).arg(mColor.red()).arg(mColor.green()).arg(mColor.blue());
    this->setStyleSheet(style);
}
