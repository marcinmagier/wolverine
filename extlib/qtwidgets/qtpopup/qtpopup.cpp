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


static QtPopup *sInstance = 0;


static void deleteQtPopupInstance();


/**
 *  Default constructor.
 */
QtPopup::QtPopup()
{
    mPosition = 0;

    qAddPostRoutine(deleteQtPopupInstance);
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
void deleteQtPopupInstance()
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
bool setTheme(const QColor &foreground, const QColor &background)
{
    return true;
}


/**
 *  Sets timeout for popups.
 *
 * @param seconds
 * @return
 */
//static
bool setTimeout(int seconds)
{
    return true;
}




