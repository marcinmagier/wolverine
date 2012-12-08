/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtmanagedtoolbarlistbox.h
 *  @brief      QtManagedToolbarListbox class interface.
 *  @details    It shouldn't be used outside qtmanagedtoolbar library.
 */

#ifndef __QT_MANAGED_TOOLBAR_LISTBOX_H_
 #define __QT_MANAGED_TOOLBAR_LISTBOX_H_


#include <QListWidget>



class QtManagedToolbarListbox : public QListWidget
{
    Q_OBJECT
    
public:
    explicit QtManagedToolbarListbox(QWidget *parent = 0);

    void dropEvent(QDropEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // __QT_MANAGED_TOOLBAR_LISTBOX_H_
