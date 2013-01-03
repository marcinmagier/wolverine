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
 *  @file       qttabwidget.h
 *  @brief      QtTabWidget class interface.
 */



#ifndef __QT_TAB_WIDGET_H_
 #define __QT_TAB_WIDGET_H_


class QToolButton;

#include <QTabWidget>


class QtTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QtTabWidget(QWidget *parent = 0);
    virtual ~QtTabWidget();
    
    void setListButtonCorner(Qt::Corner corner);
    Qt::Corner getListButtonCorner();

    bool isListButtonHidden();



public slots:
    void setListButtonHidden(bool hidden);



signals:



protected:
    QToolButton *mListButton;
    Qt::Corner mListButtonCorner;


private:

};

#endif // __QT_TAB_WIDGET_H_
