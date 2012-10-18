#include "qtmanagedtoolbarlistbox.h"

#include <QDropEvent>
#include <QDebug>
#include <QByteArray>


QtManagedToolbarListbox::QtManagedToolbarListbox(QWidget *parent) :
    QListWidget(parent)
{

}


void QtManagedToolbarListbox::dropEvent(QDropEvent *event)
{
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        int row, col;
        QMap<int,  QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

         //roleDataMap format - QMap((0, QVariant(QString, "ItemName") ) ( 1 ,  QVariant(QIcon, ) ) )
        QString name = roleDataMap.value(0).toString();
        if(name.isEmpty() || name == "Separator")
            continue;

        QList<QListWidgetItem *> listItems = findItems(name, Qt::MatchExactly);
        foreach(QListWidgetItem *item, listItems) {
            item->setHidden(false);
        }
    }
}
