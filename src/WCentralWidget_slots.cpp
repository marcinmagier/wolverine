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
 *  @file       WCentralWidget_slots.cpp
 *  @brief      Wolverine::CentralWidget slots implementation.
 */


#include "WCentralWidget.h"
#include "WEditor.h"
#include "WEditorProxy.h"
#include "WDocument.h"
#include "WPanel.h"




using namespace Wolverine;






void CentralWidget::onCreateNewDoc()
{
    Document *doc = new Document();
    Editor *edit = doc->getEditor();
    int idx = panelLeft->addTab(edit);
    panelLeft->setCurrentIndex(idx);
    mEditorList.append(edit);
    //currentEditor is update via slot
}

void CentralWidget::onOpenDoc(const QString &path)
{

}

void CentralWidget::onOpenDocForm()
{

}

void CentralWidget::onClose()
{
    Panel *panel = panelRight->hasFocus() ? panelRight : panelLeft;
    int index = panel->currentIndex();
    this->removeTab(panel, index);
}

void CentralWidget::onCloseOthers()
{

}

void CentralWidget::onCloseAll()
{

}

void CentralWidget::onMoveToLeft()
{

}

void CentralWidget::onMoveToRight()
{

}








void CentralWidget::onCurrentTabChanged(int index)
{
    Panel *panel = panelRight->hasFocus() ? panelRight : panelLeft;
    Editor *edit = dynamic_cast<Editor*>(panel->widget(index));
    currentEditor->setCurrentEditor(edit);
}

void CentralWidget::onTabCloseRequest(int index)
{
    if(index<0)
        return;

    Panel *panel = panelRight->hasFocus() ? panelRight : panelLeft;
    this->removeTab(panel, index);
}
