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
 *  @file       qtpopup_i.cpp
 *  @brief      IQtPopup class implementation.
 */


#include "qtpopup.h"
#include "ui_qtpopup.h"


#include <QTimer>
#include <QTimeLine>



/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
IQtPopup::IQtPopup(const QString &title, const QString &message) :
    ui(new Ui::IQtPopup)
{
    ui->setupUi(this);

    QString style = QString("QFrame {"
                            "border: 1px solid; "
                            "border-color: rgb(0, 0, 0, 100);"
                            "border-radius: 4px; "
                            "background-color: rgb(111, 43, 43, 100);"
                            "}");

    QString lstyle = QString("QLabel {"
                             "border: 0px;"
                             "background-color: rgb(255, 255, 255, 0);"
                             "}");
    setStyleSheet(style);
    ui->lblMessage->setStyleSheet(lstyle);
    ui->lblTimer->setStyleSheet(lstyle);
    ui->lblTitle->setStyleSheet(lstyle);
}


/**
 *  Destructor.
 */
IQtPopup::~IQtPopup()
{
    delete ui;
}


/**
 *  Enter event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::enterEvent(QEvent *event)
{

}


/**
 *  Leave event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::leaveEvent(QEvent *event)
{

}


/**
 *  Mouse press event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::mousePressEvent(QMouseEvent *event)
{

}


void IQtPopup::popup(int timeout)
{
    QWidget *tmp = dynamic_cast<QWidget*>(this->parent());
    int w = tmp->size().width();
    w = w-10;
    w = w-this->size().width();

    this->move(w, mPosition);

}

void IQtPopup::setFgColor(const QColor &color)
{

}

void IQtPopup::setBgColor(const QColor &color)
{

}

void IQtPopup::setInitialPos(int pos)
{
    mPosition = pos;

}
