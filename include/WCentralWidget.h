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


public slots:
    void newTab();
    void newTab(int index);

    void onOpen(const QString &path);
    void onOpenForm();

    void onSave();
    void onSaveIdx(int index);
    void onSaveForm();
    void onSaveFormIdx(int index);
    void onSaveAll();

    void onClose();
    void onCloseIdx(int index);
    void onCloseOthers();
    void onCloseOthersIdx(int index);
    void onCloseAll();


    void onSplit();
    void onSplitIdx(int index);

    void onMoveToOther();
    void onMoveToOtherIdx(int index);
    void onCopyToOther();
    void onCopyToOtherIdx(int index);
    void onMoveToApp();
    void onMoveToAppIdx(int index);
    void onCopyToApp();
    void onCopyToAppIdx(int index);


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void onEditorStatusIntChanged(int stat);
    void onEditorStatusExtChanged(int stat);
    void onEditorFileInfoChanged(QFileInfo *fileinfo);

    void onInternalWidgetFocusReceived();
    void onCustomContextMenuRequested(QPoint pos);



private:
    void newTab(Panel *panel, int index);

    void setupContextMenu();
    void removeTab(Panel *panel, int index);
    void removeOthers(Panel *panel, int index);
    void removeAll(Panel *panel);
    void removeAll(bool closeApp);
    void moveAll(Panel *from, Panel *to);
    void moveTab(Panel *from, int fromIdx, Panel *to);
    void copyTab(Panel *from, int fromIdx, Panel *to);
    void setCurrentPanel(Panel *panel, bool updateEditor = false);
    void setCurrentEditor(Editor *editor);
    void removeEditor(Editor *editor);



    void openFile(Panel *panel, const QString &path);
    void saveFile(Panel *panel, int index);
    void saveFileForm(Panel *panel, int index);

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
