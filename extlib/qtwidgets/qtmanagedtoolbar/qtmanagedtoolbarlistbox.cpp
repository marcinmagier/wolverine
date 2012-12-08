/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtmanagedtoolbarlistbox.cpp
 *  @brief      QtManagedToolbarListbox class implementation.
 */


#include "qtmanagedtoolbarlistbox.h"

#include <QDropEvent>
#include <QDebug>
#include <QByteArray>
#include <QMimeData>




/**
 *  Default constructor.
 *
 * @param parent
 */
QtManagedToolbarListbox::QtManagedToolbarListbox(QWidget *parent) :
    QListWidget(parent)
{

}


/**
 *  Drop event handler.
 *
 * @param event
 */
void QtManagedToolbarListbox::dropEvent(QDropEvent *event)
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
void QtManagedToolbarListbox::mouseMoveEvent(QMouseEvent* /*event*/)
{
    //no action
}
