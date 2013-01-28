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
 *  @file       WPopup.h
 *  @brief      Wolverine::Popup class interface.
 */



#ifndef __W_POPUP_H_
#define __W_POPUP_H_

#include <QObject>
#include <QColor>

namespace Wolverine {


class Popup : public QObject
{
    Q_OBJECT

private:
    Popup();

public:
    static void initialize();
    static bool popup(const QString &title, const QString &message, QWidget *parent=0);
    
protected slots:
    void onPopupTimeoutChanged(int timeout);
    void onPopupBgColorChanged(QColor color);
    void onPopupFgColorChanged(QColor color);

private:
    static Popup *sInstance;
    
};


}

#endif // __W_POPUP_H_
