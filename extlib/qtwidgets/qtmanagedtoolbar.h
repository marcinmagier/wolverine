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
 *  @file       qtmanagedtoolbar.h
 *  @brief      QtManagedToolbar class interface.
 */


#ifndef __QT_MANAGED_TOOLBAR_H_
 #define __QT_MANAGED_TOOLBAR_H_


class QMenu;
class QString;

#include <QMap>
#include <QToolBar>




class QtManagedToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(bool     managerEnabled      READ isManagerEnabled       WRITE setManagerEnabled     )


public:
    explicit QtManagedToolBar(QWidget *parent = 0);
    explicit QtManagedToolBar(QWidget *parent, const QString &toolbarName);

    void addAction(const QString &name, QAction *action);
    QAction *addWidget(const QString &name, QWidget *widget);
    void removeAction(QAction *action);
    void removeAction(const QString &name);

    void saveConfig();
    void restoreConfig();

    bool isManagerEnabled() { return mIsManagerEnabled; }

    void contextMenuEvent(QContextMenuEvent *);

public slots:
    void setManagerEnabled(bool val) { mIsManagerEnabled = val; }



protected:
    void saveConfig(const QStringList &actionNames);
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);



private slots:
    void showManagerDialog();

private:
    void initialize(const QString &name);

    void addActionAvailable(const QString &name, QAction *action);
    void applyConfiguration(const QStringList &actionNames);
    QStringList createConfiguration();


    bool mIsManagerEnabled;
    QString mToolbarName;
    QMap<QString, QAction*> mActionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
