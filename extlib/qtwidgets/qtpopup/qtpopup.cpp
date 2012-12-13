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
 *  @file       qtpopup.cpp
 *  @brief      QtPopup class implementation.
 */


#include "qtpopup.h"

#include "QApplication"
#include "QMutex"

#include "QDebug"


QtPopup* QtPopup::sInstance = 0;
int QtPopup::sTimeout = 6;
static QMutex sMutex;


/**
 *  Default constructor.
 */
QtPopup::QtPopup()
{
    mPosition = 10;
    mPopups.clear();

    qAddPostRoutine(QtPopup::deleteInstance);
}


/**
 *  Destructor.
 */
QtPopup::~QtPopup()
{

}


/**
 *  Deletes instance of QtPopup.
 */
//static
void QtPopup::deleteInstance()
{
    delete sInstance;
    sInstance = 0;
}


/**
 *  Shows popup.
 *
 * @param instance
 * @param parent
 * @return
 */
//static
bool QtPopup::popup(IQtPopup *instance, QWidget *parent)
{
    if(sInstance == 0) {
        sMutex.lock();
        if(sInstance == 0) {
            sInstance = new QtPopup();
        }
        sMutex.unlock();
    }

    qDebug() << parent->geometry();
    qDebug() << parent->pos();

    instance->setParent(parent);

    instance->setInitialPos(sInstance->mPosition);
    instance->popup(sTimeout);

    sInstance->mPosition += instance->size().height();
    return true;
}


/**
 *  Sets theme for popups.
 *
 * @param foreground color
 * @param background color
 * @return
 */
//static
void QtPopup::setTheme(const QColor &foreground, const QColor &background)
{
    IQtPopup::updateTheme(foreground, background);
}


/**
 *  Sets timeout for popups.
 *
 * @param seconds
 * @return
 */
//static
void QtPopup::setTimeout(int seconds)
{
    sTimeout = seconds;
}


/**
 *  Slot is called when popup is about to close.
 */
//slot
void QtPopup::onPopupClose()
{

}

