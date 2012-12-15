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

#include "ui_qtpopup.h"

/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
QtPopupRise::QtPopupRise(const QString &title, const QString &message):
    QtPopupBase(title, message)
{
    mFinalSize = this->calculateSize();
}


/**
 *  Destructor.
 */
//virtual
QtPopupRise::~QtPopupRise()
{

}

/**
 *  Returns final size of the frame
 *
 * @return
 */
//virtual
QSize QtPopupRise::getSize() const
{
    return mFinalSize;
}



void QtPopupRise::makeInitStep()
{
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QWidget *parent = dynamic_cast<QWidget*>(this->parent());
    // We want to show popup on the right side of the parent
    int parentWidth = parent->size().width() - POPUP_MARGIN;
    int finalXPosition = parentWidth - mFinalSize.width();
    mFinalPos = QPoint(finalXPosition, mPosition);
    mInitPos = QPoint(parent->size().width(), mPosition);
    this->move(mInitPos);
    this->resize(0, 0);

    QPoint cur_pos = QCursor::pos();
    cur_pos = QPoint(cur_pos.x()-parent->geometry().x(),
                     cur_pos.y()-parent->geometry().y());
    mCurrentAlpha = QtPopupBase::AlphaTransparent;
    QRect finalPosition = QRect(mFinalPos.x(), mFinalPos.y(), mFinalSize.width(), mFinalSize.height());
    if(finalPosition.contains(cur_pos))
        // Cursor is on the poup frame
        mCurrentAlpha = QtPopupBase::AlphaSolid;
    setAlpha(mCurrentAlpha);
}

void QtPopupRise::makeOpeningStep(int frame)
{
    // Frame is rising from right to left and from top to bottom.
    float distance = mInitPos.x() - mFinalPos.x();
    distance = distance/ANIMATION_FRAME_COUNT*frame;
    this->move(mInitPos.x()-distance, mPosition);

    float width = mFinalSize.width()/ANIMATION_FRAME_COUNT*frame;
    float height = mFinalSize.height()/ANIMATION_FRAME_COUNT*frame;
    this->resize(width, height);
}

void QtPopupRise::makeClosingStep(int frame)
{
    // Frame is rising from right to left and from top to bottom.
    // Current implementation is the same for closing step as for opening step
    this->makeOpeningStep(frame);
}
