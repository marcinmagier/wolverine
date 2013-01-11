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


#include <QCursor>
#include <QDebug>


using namespace Wolverine;






void CentralWidget::onNew()
{
    Document *doc = new Document();
    Editor *edit = doc->getEditor();


    int idx = mPanelCurrent->addTab(edit);
    mPanelCurrent->setCurrentIndex(idx);
    mEditorList.append(edit);
    //currentEditor is updated via slot
}

void CentralWidget::onNewIdx(int index)
{

}

void CentralWidget::onOpen(const QString &path)
{

}

void CentralWidget::onOpenForm()
{

}

void CentralWidget::onClose()
{
    Panel *panel = mPanelRight->hasFocus() ? mPanelRight : mPanelLeft;
    int index = panel->currentIndex();
    this->removeTab(panel, index);
}

void CentralWidget::onCloseIdx(int index)
{
    if(index<0)
        return;

    Panel *panel = mPanelRight->hasFocus() ? mPanelRight : mPanelLeft;
    this->removeTab(panel, index);
}

void CentralWidget::onCloseOthers()
{

}

void CentralWidget::onCloseOthersIdx(int index)
{

}

void CentralWidget::onCloseAll()
{

}

void CentralWidget::onMoveToOther()
{

}

void CentralWidget::onMoveToOtherIdx(int index)
{
    if(mPanelLeft->hasFocus()) {
        //Move to the right
        this->moveTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
    }

}






void CentralWidget::onCustomContextMenuRequested(QPoint pos)
{
    Panel *panel;
    if(mPanelRight->hasFocus()) {
        panel = mPanelRight;
        mMenuMoveTab->setText(tr("Move to left"));
        mMenuMoveTab->setIcon(QIcon(":/move_left.png"));
    } else {
        panel = mPanelLeft;
        mMenuMoveTab->setText(tr("Move to right"));
        mMenuMoveTab->setIcon(QIcon(":/move_right.png"));
    }
    int idx = panel->tabAt(pos);

    if(idx < 0) {
        mMenuClose->setEnabled(false);
        mMenuCloseOthers->setEnabled(false);
        mMenuMoveTab->setVisible(false);
    } else {
        mMenuClose->setEnabled(true);
        mMenuCloseOthers->setEnabled(true);
        mMenuMoveTab->setVisible(true);
    }

    QAction *action = mContextMenu->exec(QCursor::pos());

    if(action == mMenuClose) {
        onCloseIdx(idx);
    } else if(action == mMenuCloseOthers) {
        onCloseOthersIdx(idx);
    } else if(action == mMenuMoveTab) {
        onMoveToOtherIdx(idx);
    }
}

void CentralWidget::onCurrentTabChanged(int index)
{
    Editor *edit = dynamic_cast<Editor*>(mPanelCurrent->widget(index));
    currentEditor->setCurrentEditor(edit);
}

void CentralWidget::onInternalWidgetFocusReceived()
{
    if(sender() == mPanelRight)
        mPanelCurrent = mPanelRight;
    else
        mPanelCurrent = mPanelLeft;
}


