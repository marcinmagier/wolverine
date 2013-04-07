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
 *  @file       WCentralWidget.h
 *  @brief      Wolverine::CentralWidget class interface.
 */


#ifndef __W_CENTRAL_WIDGET_H_
 #define __W_CENTRAL_WIDGET_H_


class QFileInfo;
class QHBoxLayout;
class QSplitter;
class QtManagedMenu;
class QIcon;

class AppSettings;

#include "WEditorBinder.h"

#include <QWidget>

namespace Wolverine
{
class Editor;
class EditorProxy;
class Panel;

typedef QList<Editor*> EditorList;


class CentralWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

    void bringToFront();

    void closeAllTabs(bool closeApp);


public slots:
    void newTab();
    void newTab(int index);

    void openTab(const QString &path);
    void openTabForm();

    void saveTab();
    void saveTab(int index);
    void saveTabForm();
    void saveTabForm(int index);
    void saveAllTabs();

    void closeTab();
    void closeTab(int index);
    void closeOtherTabs();
    void closeOtherTabs(int index);
    void closeAllTabs();

    void splitTab();
    void splitTab(int index);

    void copyTabToOther();
    void copyTabToOther(int index);
    void moveTabToOther();
    void moveTabToOther(int index);
    void copyTabToApp();
    void copyTabToApp(int index);
    void moveTabToApp();
    void moveTabToApp(int index);


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void onEditorStatusIntChanged(int stat);
    void onEditorStatusExtChanged(int stat);
    void onEditorFileInfoChanged(QFileInfo *fileinfo);
    void onEditorScrollHChanged(int range);
    void onEditorScrollVChanged(int range);

    void onInternalWidgetFocusReceived();
    void onCustomContextMenuRequested(QPoint pos);



private:
    void newTab(Panel *panel, int index);

    void openTab(Panel *panel, const QString &path);

    void saveTab(Panel *panel, int index);
    void saveTabForm(Panel *panel, int index);
    void saveAllTabs(Panel *panel);

    void closeTab(Panel *panel, int index);
    void closeOtherTabs(Panel *panel, int index);
    void closeAllTabs(Panel *panel);

    void copyTab(Panel *from, int fromIdx, Panel *to);
    void moveTab(Panel *from, int fromIdx, Panel *to);
    void moveAllTabs(Panel *from, Panel *to);

    void updatePanels();
    void setCurrentPanel(Panel *panel, bool updateEditor = false);
    void setCurrentEditor(Editor *editor);
    Panel* findEditor(Editor *editor, int *retIdx);
    bool setCurrentIfExists(Panel *panel, const QString &path, int line = -1);
    bool setCurrentIfExists(Panel *panel, Editor *editor, int line = -1);


    void setupContextMenu();


    QIcon guesEditorStatusIcon(EditorBinder::StatusInt statInt, EditorBinder::StatusExt statExt);


    QHBoxLayout *mLayout;
    QSplitter *mSplitter;

    Panel *mPanelLeft;
    Panel *mPanelRight;
    Panel *mPanelCurrent;

    EditorProxy *mCurrentEditor;

    QtManagedMenu *mContextMenu;
    QAction *mMenuNew;
    QAction *mMenuClose;
    QAction *mMenuCloseOthers;
    QAction *mMenuSplitTab;
    QAction *mMenuMoveTab;
    QAction *mMenuCopyTab;
    QAction *mMenuMoveApp;
    QAction *mMenuCopyApp;

    AppSettings *mSettings;
};



}









#endif // __W_CENTRAL_WIDGET_H_
