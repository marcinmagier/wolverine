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




#include <QDebug>



#define FRAME_STYLE_PATTERN     "QFrame {"                                  \
                                "border: 1px solid; "                       \
                                "border-color: rgb(%1, %2, %3, ALPHA);"     \
                                "border-radius: 10px; "                     \
                                "background-color: rgb(%4, %5, %6, ALPHA);" \
                                "}"

#define LABEL_STYLE_PATTERN     "QLabel {"                                  \
                                "border: 0px;"                              \
                                "color: rgb(%1, %2, %3);"                   \
                                "background-color: rgb(255, 255, 255, 0);"  \
                                "}"



QString IQtPopup::sStyleSheetFrame;
QString IQtPopup::sStyleSheetLabel;




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


/**
 * @brief IQtPopup::setInitialPos
 * @param pos
 */
void IQtPopup::setInitialPos(int pos)
{
    mPosition = pos;

}


/**
 * @brief IQtPopup::setAlpha
 * @param alpha
 */
void IQtPopup::setAlpha(int alpha)
{
    QString style = QString(sStyleSheetFrame).replace("ALPHA", QString::number(alpha));
    setStyleSheet(style);

    style = QString(sStyleSheetLabel).replace("ALPHA", QString::number(alpha));
    ui->lblMessage->setStyleSheet(style);
    ui->lblTimer->setStyleSheet(style);
    ui->lblTitle->setStyleSheet(style);

}


/**
 * @brief IQtPopup::updateTheme
 * @param fg
 * @param bg
 */
//static
void IQtPopup::updateTheme(const QColor &fg, const QColor &bg)
{
    sStyleSheetFrame = QString(FRAME_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue())
                                                   .arg(bg.red()).arg(bg.green()).arg(bg.blue());

    sStyleSheetLabel = QString(LABEL_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue());
}



