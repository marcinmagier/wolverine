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
 *  @file       qtmanagedmenu.h
 *  @brief      QtManagedMenu class interface.
 */


#ifndef __QT_MANAGED_MENU_H_
 #define __QT_MANAGED_MENU_H_


class QString;

#include <QMenu>




class QtManagedMenu : public QMenu
{
    Q_OBJECT
    Q_PROPERTY(bool     managerEnabled      READ isManagerEnabled       WRITE setManagerEnabled     )


public:
    explicit QtManagedMenu(QWidget *parent = 0);
    explicit QtManagedMenu(QWidget *parent, const QString &toolbarName);

    void addActiona(const QString &name, QAction *action);

    QAction* exec();
    QAction* exec(const QPoint &pos, QAction *at=0);

    void saveConfig();
    void restoreConfig();

    bool isManagerEnabled() { return mIsManagerEnabled; }



public slots:
    void setManagerEnabled(bool val) { mIsManagerEnabled = val; }



protected:
    void saveConfig(const QStringList &actionNames);



private slots:
    void showManagerDialog();

private:
    void initialize(const QString &name);

    void addActionAvailable(const QString &name, QAction *action);
    void applyConfiguration(const QStringList &actionNames);
    QStringList createConfiguration();


    bool mIsManagerEnabled;
    QString mMenuName;
    QMap<QString, QAction*> mActionsAvailable;
};

#endif //__QT_MANAGED_MENU_H_
