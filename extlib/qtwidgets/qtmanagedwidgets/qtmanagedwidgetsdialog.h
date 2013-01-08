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
 *  @file       qtmanagedtoolbardialog.h
 *  @brief      QtManagedToolbarDialog class interface.
 *  @details    It shouldn't be used outside qtmanagedtoolbar library.
 */

#ifndef __QT_MANAGED_TOOLBAR_DIALOG_H_
 #define __QT_MANAGED_TOOLBAR_DIALOG_H_


class QAction;
class QString;
class QStringList;
class QListWidgetItem;

namespace Ui {
class QtManagedToolBarDialog;
}

#include <QMap>
#include <QDialog>



typedef QMap<QString, QAction*> QtActionNameMap;



class QtManagedToolBarDialog : public QDialog
{
    Q_OBJECT


public:
    explicit QtManagedToolBarDialog(QWidget *parent = 0);
    ~QtManagedToolBarDialog();

    int exec(const QtActionNameMap *actionsAvailable, QStringList *actionsVisible);



private slots:
    void moveActionUp();
    void moveActionDown();
    void moveActionToLeft();
    void moveActionToLeft(QListWidgetItem *item);
    void moveActionToRight();
    void moveActionToRight(QListWidgetItem *item);



private:
    void fillActionsAvailable(const QtActionNameMap *actionsAvailable, const QStringList *actionsVisible);
    void fillActionsVisible(const QStringList *actionsVisible);

    QMap<QListWidgetItem*, QString> mActionsAvailableMap;
    QMap<QListWidgetItem*, QString> mActionsVisibleMap;

    Ui::QtManagedToolBarDialog *ui;
};

#endif // __QT_MANAGED_TOOLBAR_DIALOG_H_
