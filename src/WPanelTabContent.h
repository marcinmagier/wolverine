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
 *  @file       WPanelTabContent.h
 *  @brief      Wolverine::PanelTabContent class interface.
 */



#ifndef __W_PANEL_TAB_CONTENT_H_
 #define __W_PANEL_TAB_CONTENT_H_


#include <QSplitter>


namespace Wolverine
{

class Editor;



class PanelTabContent : public QSplitter
{
    Q_OBJECT

public:
    explicit PanelTabContent(QWidget *parent = 0);
    virtual ~PanelTabContent();
    

    void addWidget(Editor *editor);
    Editor* getEditor();
    bool hasEditor(Editor *editor);
    bool hasEditor(const QString &filePath);
    void split();



signals:
    void focusReceived();



private slots:
    void onInternalWidgetFocusReceived();
    void onSplitterMoved(int pos, int index);



private:
    void removeEditor(int index);

    Editor *mEditorProxy;


};


}

#endif // __W_PANEL_TAB_CONTENT_H_
