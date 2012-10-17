#include "qtmanagedtoolbarlistbox.h"


QtManagedToolbarListbox::QtManagedToolbarListbox(QWidget *parent) :
    QListWidget(parent)
{

}


void QtManagedToolbarListbox::dropEvent(QDropEvent *event)
{
    QListWidget::dropEvent(event);
}
