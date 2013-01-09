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
 *  @file       qtmanagedtoolbarlistbox.cpp
 *  @brief      QtManagedToolbarListbox class implementation.
 */


#include "qtmanagedwidgetslistbox.h"

#include <QDropEvent>
#include <QByteArray>
#include <QMimeData>




/**
 *  Default constructor.
 *
 * @param parent
 */
QtManagedWidgetsListbox::QtManagedWidgetsListbox(QWidget *parent) :
    QListWidget(parent)
{

}


/**
 *  Drop event handler.
 *
 * @param event
 */
void QtManagedWidgetsListbox::dropEvent(QDropEvent *event)
{
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        int row, col;
        QMap<int,  QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

         // roleDataMap format is
		 // QMap((0, QVariant(QString, "ItemName") ) ( 1 ,  QVariant(QIcon, ) ) )
        QString name = roleDataMap.value(0).toString();
        if(name.isEmpty() || name == "Separator")
            continue;

        QList<QListWidgetItem *> listItems = findItems(name, Qt::MatchExactly);
        foreach(QListWidgetItem *item, listItems) {
            item->setHidden(false);
        }
    }
}


/**
 *  Redefine mouseMoveEvent in order to prevent dragging items.
 *
 *  Without this function it is possible to start dragging list item dropped before (DropOnly mode is set)
 *  @bug Qt v4.8.1 win
 */
void QtManagedWidgetsListbox::mouseMoveEvent(QMouseEvent* /*event*/)
{
    //no action
}
