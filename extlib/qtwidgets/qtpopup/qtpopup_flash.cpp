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


#include "QCursor"


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


/**
 *  Initializes popup
 */
//virtual
void QtPopupFlash::makeInitStep()
{
    QWidget *parent = dynamic_cast<QWidget*>(this->parent());
    this->resize(this->calculateSize());
    // We want to show popup on the right side of the parent
    int parent_width = parent->size().width() - POPUP_MARGIN;
    int popup_x_position = parent_width-this->size().width();
    this->move(popup_x_position, mPosition);


    QPoint cur_pos = QCursor::pos();
    cur_pos = QPoint(cur_pos.x()-parent->geometry().x(),
                     cur_pos.y()-parent->geometry().y());
    if(this->geometry().contains(cur_pos))
        // Cursor is on the poup frame
        mCurrentAlpha = QtPopupBase::AlphaSolid;

    setAlpha(0);
}


/**
 *  Makes one step for opening
 *
 * @param frame
 */
//virtual
void QtPopupFlash::makeOpeningStep(int frame)
{
    setAlpha(mCurrentAlpha/ANIMATION_FRAME_COUNT*frame);
}


/**
 *  Makes one step for closing
 *
 * @param frame
 */
//virtual
void QtPopupFlash::makeClosingStep(int frame)
{
    setAlpha(mCurrentAlpha/ANIMATION_FRAME_COUNT*frame);
}
