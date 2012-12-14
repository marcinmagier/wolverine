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
 *  @file       qtpopup_flash.cpp
 *  @brief      QtPopupFlash class implementation.
 */


#include "qtpopup.h"



/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
QtPopupFlash::QtPopupFlash(const QString &title, const QString &message):
    QtPopupBase(title, message)
{
    setAlpha(QtPopupBase::AlphaTransparent);

}


/**
 *  Destructor.
 */
//virtual
QtPopupFlash::~QtPopupFlash()
{

}


void QtPopupFlash::makeInitStep()
{
    QWidget *tmp = dynamic_cast<QWidget*>(this->parent());
    int w = tmp->size().width();
    this->resize(this->calculateWidth(), this->size().height());
    w = w-10;
    w = w-this->size().width();

    this->move(w, mPosition);

    setAlpha(0);
}

void QtPopupFlash::makeOpeningStep(int frame)
{
    setAlpha(AlphaTransparent/ANIMATION_FRAME_COUNT*frame);
}

void QtPopupFlash::makeClosingStep(int frame)
{
    setAlpha(AlphaTransparent/ANIMATION_FRAME_COUNT*frame);
}
