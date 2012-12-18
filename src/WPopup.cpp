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
 *  @file       WPopup.cpp
 *  @brief      Wolverine::Popup class implementation.
 */


#include "WPopup.h"

#include "CfgAppSettings.h"
#include "CfgViewSettings.h"


using namespace Wolverine;


Popup* Popup::sInstance = 0;



/**
 *  Constructor
 */
Popup::Popup()
{
    AppSettings *settings = AppSettings::instance();

    QtPopup::setTimeout(settings->view->getPopupTimeout());
    connect( settings->view, SIGNAL(popupTimeoutChanged(int)),
                       this, SLOT(onPopupTimeoutChanged(int)), Qt::DirectConnection );

    QtPopup::setTheme(settings->view->getPopupFgColor(), settings->view->getPopupBgColor());
    connect( settings->view, SIGNAL(popupBgColorChanged(QColor)),
                       this, SLOT(onPopupBgColorChanged(QColor)), Qt::DirectConnection );
    connect( settings->view, SIGNAL(popupFgColorChanged(QColor)),
                       this, SLOT(onPopupFgColorChanged(QColor)), Qt::DirectConnection );

}


/**
 *  Initializes popup settings
 */
void Popup::initialize()
{
    if(sInstance == 0) {
        sInstance = new Popup();
    }

}


/**
 *  Shows popup
 *
 * @param title
 * @param message
 * @param parent
 * @return
 */
bool Popup::popup(const QString &title, const QString &message, QWidget *parent)
{
    QtPopupBase *p = 0;
    QString animationType = AppSettings::instance()->view->getPopupAnimationType();
    if(animationType == "Flashing")
        p = new QtPopupFlash(title, message);
    else if(animationType == "Moving")
        p = new QtPopupMove(title, message);
    else if(animationType == "Rising")
        p = new QtPopupRise(title, message);
    else
        return false;

    return QtPopup::popup(p, parent);
}


void Popup::onPopupTimeoutChanged(int timeout)
{
    QtPopup::setTimeout(timeout);
}


void Popup::onPopupBgColorChanged(QColor color)
{
    AppSettings *settings = AppSettings::instance();
    QtPopup::setTheme(settings->view->getPopupFgColor(), color);
}


void Popup::onPopupFgColorChanged(QColor color)
{
    AppSettings *settings = AppSettings::instance();
    QtPopup::setTheme(color, settings->view->getPopupBgColor());
}
