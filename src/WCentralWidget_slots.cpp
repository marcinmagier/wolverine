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
#include "WEditorBinder.h"
#include "WEditorProxy.h"
#include "WPanel.h"


#include <QCursor>
#include <QDebug>


using namespace Wolverine;






void CentralWidget::onNew()
{
    EditorBinder *doc = new EditorBinder();
    Editor *edit = doc->getEditor();


    int idx = mPanelCurrent->addTab(edit);
    mPanelCurrent->setCurrentIndex(idx);
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
    this->onCloseIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onCloseIdx(int index)
{
    this->removeTab(mPanelCurrent, index);

    if(mPanelCurrent->count() == 0) {
        if(mPanelCurrent == mPanelLeft)
            this->moveAll(mPanelRight, mPanelLeft);
        mPanelRight->setVisible(false);
        mPanelCurrent = mPanelLeft;
    }
}

void CentralWidget::onCloseOthers()
{
    this->onCloseOthersIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onCloseOthersIdx(int index)
{
    this->removeOthers(mPanelCurrent, index);
}

void CentralWidget::onCloseAll()
{

}

void CentralWidget::onMoveToOther()
{
    this->onCopyToOtherIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onMoveToOtherIdx(int index)
{
    if(mPanelCurrent == mPanelRight) {
        this->moveTab(mPanelRight, index, mPanelLeft);
        if(mPanelRight->count() == 0) {
            mPanelRight->setVisible(false);
            mPanelCurrent = mPanelLeft;
        }
    } else {
        this->moveTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
        mPanelCurrent = mPanelRight;
    }
}

void CentralWidget::onCopyToOther()
{
    this->onCopyToOtherIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onCopyToOtherIdx(int index)
{
    if(mPanelCurrent == mPanelRight) {
        // Copy to the left panel
        this->copyTab(mPanelRight, index, mPanelLeft);
    } else {
        // Copy to the right panel
        this->copyTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
    }
}




void CentralWidget::onCurrentTabChanged(int index)
{
    Editor *edit = mPanelCurrent->getEditor(index);
    currentEditor->setCurrentEditor(edit);
}

void CentralWidget::onInternalWidgetFocusReceived()
{
    if(sender() == mPanelRight)
        mPanelCurrent = mPanelRight;
    else
        mPanelCurrent = mPanelLeft;
}

void CentralWidget::onCustomContextMenuRequested(QPoint pos)
{
    if(mPanelCurrent == mPanelRight) {
        mMenuMoveTab->setText(tr("Move to left"));
        mMenuCopyTab->setText(tr("Copy to left"));
    } else {
        mMenuMoveTab->setText(tr("Move to right"));
        mMenuCopyTab->setText(tr("Copy to right"));
    }

    int idx = mPanelCurrent->tabAt(pos);

    mMenuClose->setEnabled(false);
    mMenuCloseOthers->setEnabled(false);
    mMenuMoveTab->setEnabled(false);
    mMenuCopyTab->setEnabled(false);

    if(idx >= 0) {
        mMenuClose->setEnabled(true);
        mMenuCopyTab->setEnabled(true);

        if(mPanelCurrent->count() > 1) {
            mMenuCloseOthers->setEnabled(true);
            mMenuMoveTab->setEnabled(true);
        } else {
            // Only one tab
            if(mPanelCurrent == mPanelRight) {
                mMenuMoveTab->setEnabled(true);
            }
        }
    }

    QAction *action = mContextMenu->exec(QCursor::pos());

    if(action == mMenuClose) {
        onCloseIdx(idx);
    } else if(action == mMenuCloseOthers) {
        onCloseOthersIdx(idx);
    } else if(action == mMenuMoveTab) {
        onMoveToOtherIdx(idx);
    } else if(action == mMenuCopyTab) {
        onCopyToOtherIdx(idx);
    }
}


