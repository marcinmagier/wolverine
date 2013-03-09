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

    EditorProxy* getCurrentEditor();

public slots:
    void onNew();

    void onOpen(const QString &path);
    void onOpenForm();

    void onSave();
    void onSaveForm();
    void onSaveAll();

    void onClose();
    void onCloseOthers();
    void onCloseAll();


    void onSplit();
    void onMoveToOther();
    void onCopyToOther();
    void onMoveToApp();
    void onCopyToApp();


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void onCloseIdx(int index);
    void onCloseOthersIdx(int index);
    void onSplitIdx(int index);
    void onMoveToOtherIdx(int index);
    void onCopyToOtherIdx(int index);
    void onMoveToAppIdx(int index);
    void onCopyToAppIdx(int index);

    void onEditorStatusIntChanged(int stat);
    void onEditorStatusExtChanged(int stat);
    void onEditorFileInfoChanged(QFileInfo *fileinfo);

    void onInternalWidgetFocusReceived();
    void onCustomContextMenuRequested(QPoint pos);



private:
    void setupContextMenu();
    void removeTab(Panel *panel, int index);
    void removeOthers(Panel *panel, int index);
    void moveAll(Panel *from, Panel *to);
    void moveTab(Panel *from, int fromIdx, Panel *to);
    void copyTab(Panel *from, int fromIdx, Panel *to);
    void setTabIcon(Panel *panel, int idx, EditorBinder::StatusInt statInt, EditorBinder::StatusExt statExt);
    void setCurrentPanel(Panel *panel);
    void setCurrentEditor(Editor *editor);
    void removeEditor(Editor *editor);

    void openFile(Panel *panel, const QString &path);

    bool setCurrentIfExists(Panel *panel, const QString &path, int line = -1);
    bool setCurrentIfExists(Panel *panel, Editor *editor, int line = -1);

    QIcon guesEditorStatusIcon(EditorBinder::StatusInt statInt, EditorBinder::StatusExt statExt);


    QHBoxLayout *mLayout;
    QSplitter *mSplitter;

    Panel *mPanelLeft;
    Panel *mPanelRight;
    Panel *mPanelCurrent;

    EditorProxy *mCurrentEditor;

    QtManagedMenu *mContextMenu;
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
