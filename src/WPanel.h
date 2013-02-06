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
 *  @file       WPanel.h
 *  @brief      Wolverine::Panel class interface.
 */



#ifndef __W_PANEL_H_
 #define __W_PANEL_H_


#include "qtmanagedmenu.h"
#include "qttabwidget.h"

#include "WEditorBinder.h"



namespace Wolverine
{

class Editor;
class EditorProxy;
class PanelTabContent;
class PanelTabBar;



class Panel : public QtTabWidget
{
    Q_OBJECT

public:
    explicit Panel(EditorProxy *editorProxy, QWidget *parent = 0);
    virtual ~Panel();


    int addTab(Editor *editor);
    int indexOf(Editor *editor);
    int indexOf(const QString &filePath);
    int tabAt(const QPoint &pos);
    Editor* getEditor(int index);
    void splitTab(int index);
    void removeTab(int index);

    void setStatusIcon(int idx, EditorBinder::StatusInt statInt, EditorBinder::StatusExt statExt);

public slots:


signals:
    void focusReceived();
    void tabNewRequested();


private slots:
    void onCustomContextMenuRequested(QPoint pos);
    void onInternalWidgetFocusReceived();
    void onCurrentTabChanged(int idx);
    void onTabNewRequested();

private:


    PanelTabContent* getTabContent(int idx);

    PanelTabBar *mTabBar;
    EditorProxy *mEditorProxy;

};


}

#endif // __W_PANEL_H_
