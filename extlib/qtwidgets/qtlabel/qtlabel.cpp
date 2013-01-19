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
 *  @file       qtlabel.cpp
 *  @brief      QtLabel class implementation.
 */


#include "qtlabel.h"

#include <QTimer>
#include <QMouseEvent>


/**
 *  Constructor
 *
 * @param parent
 */
QtLabel::QtLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
    initialize();
}


/**
 *  Constructor
 *
 * @param parent
 */
QtLabel::QtLabel(const QString &text, QWidget *parent, Qt::WindowFlags f) :
    QLabel(text, parent, f)
{
    initialize();
}


/**
 *  Initializes QtLabel class
 */
void QtLabel::initialize()
{
    mTimerTimeout = 1000;
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()),
              this, SLOT(onTimeout()) );
}


/**
 *  Sets long click timeout
 *
 * @param timeout
 */
void QtLabel::setLongClickTimeout(int timeout)
{
    mTimerTimeout = timeout;
}


/**
 *  Returns current long click timeout
 *
 * @return
 */
int QtLabel::getLongClickTimeout()
{
    return mTimerTimeout;
}


/**
 *  mousePressEvent() handler
 *
 * @param event
 */
//virtual
void QtLabel::mousePressEvent(QMouseEvent *event)
{
    if(!mTimer->isActive()) {
        mTimeoutReached = false;
        mMouseButton = event->button();
        mTimer->start(1000);
    }
}


/**
 *  mouseReleaseEvent() handler
 *
 * @param event
 */
//virtual
void QtLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(mMouseButton == event->button()) {
        if(mTimer->isActive()) {
            mTimer->stop();
        }

        if(mTimeoutReached)
            emit clickedLong(event);
        else
            emit clicked(event);
    }
}


/**
 *  mouseDoubleClickEvent() handler
 *
 * @param event
 */
//virtual
void QtLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked(event);
}

/**
 *  mouseMoveEvent() handler
 *
 * @param event
 */
//virtual
void QtLabel::mouseMoveEvent(QMouseEvent *event)
{
    mTimer->stop();
}


/**
 *  onTimeout() slot handler
 */
void QtLabel::onTimeout()
{
    mTimeoutReached = true;
    mTimer->stop();
}
