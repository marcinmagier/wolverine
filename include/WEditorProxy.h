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
 *  @file       WEditorProxy.h
 *  @brief      Wolverine::EditorProxy class interface.
 */




#ifndef __W_EDITOR_PROXY_H_
 #define __W_EDITOR_PROXY_H_


#include <QObject>
#include <QPoint>



class QtManagedMenu;


namespace Wolverine
{

class Editor;


class EditorProxy: public QObject
{
    Q_OBJECT

public:
    explicit EditorProxy();
    virtual ~EditorProxy();

    Editor* getCurrentEditor();

public slots:
    void setCurrentEditor(Editor *editor);

    void onCut();
    void onCopy();
    void onPaste();


signals:
    void currentEditorChanged(Editor *editor);


private slots:
    void onCustomContextMenuRequested(const QPoint &pos);


private:
    void setupContextMenu();

    Editor *mCurrentEditor;

    QtManagedMenu *mContextMenu;

};



}

#endif // __W_EDITOR_PROXY_H_
