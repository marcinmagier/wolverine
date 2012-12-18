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
 *  @file       WCentralWidget.h
 *  @brief      Wolverine::CentralWidget class interface.
 */


#ifndef __W_CENTRAL_WIDGET_H_
 #define __W_CENTRAL_WIDGET_H_


class QHBoxLayout;
class QSplitter;


#include <QWidget>

namespace Wolverine
{

class Document;
class Panel;



class CentralWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

public slots:
    void onCreateNewDoc();
    void onOpenDoc();

private:
    QHBoxLayout *layout;
    QSplitter *splitter;

    Panel *panelLeft;
    Panel *panelRight;

    Document *editor;
};



}









#endif // __W_CENTRAL_WIDGET_H_
