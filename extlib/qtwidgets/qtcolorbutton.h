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
 *  @file       qtcolorbutton.h
 *  @brief      QtColorButton class interface.
 */



#ifndef __QT_COLOR_BUTTON_H_
 #define __QT_COLOR_BUTTON_H_


#include <QPushButton>
#include <QColor>


class QtColorButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QtColorButton(const QColor &color, QWidget *parent = 0);
    
signals:
    void colorChanged(QColor color);
    
protected slots:
    void onButtonClicked();

protected:
    void setButtonColor(const QColor &color);

private:
    QColor mColor;
};

#endif // __QT_COLOR_BUTTON_H_
