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
 *  @file       qtfontbutton.h
 *  @brief      QtFontButton class interface.
 */



#ifndef __QT_FONT_BUTTON_H_
 #define __QT_FONT_BUTTON_H_


#include <QPushButton>
#include <QFont>


class QtFontButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QtFontButton(QWidget *parent = 0);
    void setFont(const QFont &font);
    

signals:
    void fontChanged(QFont font);
    

protected slots:
    void onButtonClicked();


private:
    QFont mFont;
};

#endif // __QT_FONT_BUTTON_H_
