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
 *  @file       qtpopup_move.cpp
 *  @brief      QtPopupMove class implementation.
 */


#include "qtpopup.h"
#include <QDebug>


/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
QtPopupMove::QtPopupMove(const QString &title, const QString &message):
    QtPopupBase(title, message)
{

}


/**
 *  Destructor.
 */
//virtual
QtPopupMove::~QtPopupMove()
{

}


void QtPopupMove::makeInitStep()
{
    QWidget *parent = dynamic_cast<QWidget*>(this->parent());
    this->resize(this->calculateSize());
    // We want to show popup on the right side of the parent
    int parentWidth = parent->size().width() - POPUP_MARGIN;
    int finalXPosition = parentWidth-this->size().width();
    mFinalPos = QPoint(finalXPosition, mPosition);
    mInitPos = QPoint(parent->size().width(), mPosition);
    this->move(mInitPos);

    QPoint cur_pos = QCursor::pos();
    cur_pos = QPoint(cur_pos.x()-parent->geometry().x(),
                     cur_pos.y()-parent->geometry().y());
    mCurrentAlpha = QtPopupBase::AlphaTransparent;
    QRect finalPosition = QRect(mFinalPos.x(), mFinalPos.y(), size().width(), size().height());
    if(finalPosition.contains(cur_pos))
        // Cursor is on the poup frame
        mCurrentAlpha = QtPopupBase::AlphaSolid;
    setAlpha(mCurrentAlpha);
}

void QtPopupMove::makeOpeningStep(int frame)
{
    // Frame is moving from right to left
    float distance = mInitPos.x() - mFinalPos.x();
    distance = distance/ANIMATION_FRAME_COUNT*frame;
    this->move(mInitPos.x()-distance, mPosition);
}

void QtPopupMove::makeClosingStep(int frame)
{
    // Frame is moving from left to right
    float distance = mInitPos.x() - mFinalPos.x();
    distance = distance/ANIMATION_FRAME_COUNT*frame;
    this->move(mInitPos.x()-distance, mPosition);
}
