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
 *  @file       qttabwidget.cpp
 *  @brief      QtTabWidget class implementation.
 */


#include "qttabwidget.h"

#include <QToolButton>


/**
 *  Constructor
 */
QtTabWidget::QtTabWidget(QWidget *parent) :
    QTabWidget(parent),
    mListButtonCorner(Qt::TopLeftCorner)
{
    mListButton = new QToolButton(this);
    mListButton->setArrowType(Qt::DownArrow);
}


/**
 *  Destructor
 */
QtTabWidget::~QtTabWidget()
{
    delete mListButton;
}


/**
 * @brief QtTabWidget::getListButtonCorner
 * @return
 */
Qt::Corner QtTabWidget::getListButtonCorner()
{
    return mListButtonCorner;
}


/**
 * @brief QtTabWidget::setListButtonCorner
 * @param corner
 */
void QtTabWidget::setListButtonCorner(Qt::Corner corner)
{
    mListButtonCorner = corner;
}


/**
 * @brief QtTabWidget::isListButtonHidden
 * @return
 */
bool QtTabWidget::isListButtonHidden()
{
    if( cornerWidget(mListButtonCorner) )
        return false;
    else
        return true;
}


/**
 * @brief QtTabWidget::setListButtonHidden
 * @param hidden
 */
void QtTabWidget::setListButtonHidden(bool hidden)
{
    if(hidden) {
        setCornerWidget(0, mListButtonCorner);
    } else {
        setCornerWidget(mListButton, mListButtonCorner);
        mListButton->setHidden(false);
    }
}
