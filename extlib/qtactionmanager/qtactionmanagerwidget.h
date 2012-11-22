/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanagerwidget.h
 *  @brief      QtActionManagerWidget class interface.
 *  @details    It shouldn't be used outside qtactionmanager library.
 */


#ifndef __QT_ACTION_MANAGER_WIDGET_H_
 #define __QT_ACTION_MANAGER_WIDGET_H_


class QTreeWidgetItem;
class QKeyEvent;

namespace Impl {
class QtActionManager;
}

namespace Ui {
class QtActionManagerWidget;
}

#include "qtaction.h"

#include <QWidget>



class QtActionManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtActionManagerWidget(Impl::QtActionManager *actionManager, QWidget *parent = 0);
    ~QtActionManagerWidget();


public slots:
    void changeCurrentScheme(QString scheme);
    void onItemDoubleClicked(QTreeWidgetItem* item, int col);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void updateUI();
    void clearSelected();
    void restoreSelected();
    QTreeWidgetItem* findShortcut(QString shortcut);

    Ui::QtActionManagerWidget *ui;
    Impl::QtActionManager *m_actionManager;
    QMap<QTreeWidgetItem *, QtAction*> m_actionMap;
    QTreeWidgetItem *m_itemSelected;
};

#endif // __QT_ACTION_MANAGER_WIDGET_H_
