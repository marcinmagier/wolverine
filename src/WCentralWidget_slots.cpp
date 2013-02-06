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

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include <QCursor>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>


using namespace Wolverine;






void CentralWidget::onNew()
{
    EditorBinder *binder = new EditorBinder();
    Editor *edit = binder->getEditor();


    int idx = mPanelCurrent->addTab(edit);
    mPanelCurrent->setCurrentIndex(idx);
    //currentEditor is updated via slot

    connect( binder, SIGNAL(statusIntChanged(int)),
               this, SLOT(onEditorStatusIntChanged(int)) );
    connect( binder, SIGNAL(statusExtChanged(int)),
               this, SLOT(onEditorStatusExtChanged(int)) );
}

void CentralWidget::onNewIdx(int index)
{

}

void CentralWidget::onOpen(const QString &path)
{
    EditorBinder *binder = new EditorBinder(path);
    Editor *edit = binder->getEditor();

    int idx = mPanelCurrent->addTab(edit);
    mPanelCurrent->setCurrentIndex(idx);

    connect( binder, SIGNAL(statusIntChanged(int)),
               this, SLOT(onEditorStatusIntChanged(int)) );
    connect( binder, SIGNAL(statusExtChanged(int)),
               this, SLOT(onEditorStatusExtChanged(int)) );
}

void CentralWidget::onOpenForm()
{
    QString initialPath;
    if(mSettings->general->isAppOpenFromCurrentEnabled()) {
        initialPath = mCurrentEditor->getCurrentEditorDir();
    } else {
        initialPath = mSettings->general->getAppLastOpenedDir();
    }

    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), initialPath);
    if(files.count() == 0)
        return;

    QFileInfo fileInfo = QFileInfo(files[0]);
    mSettings->general->setAppLastOpenedDir(fileInfo.canonicalPath());

    foreach(QString file, files) {
        this->onOpen(file);
    }
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
        this->setCurrentPanel(mPanelLeft);
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

void CentralWidget::onSplit()
{
    this->onSplitIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onSplitIdx(int index)
{
    mPanelCurrent->splitTab(index);
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
        }
    } else {
        this->moveTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
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
        mPanelCurrent = mPanelLeft;
        this->copyTab(mPanelRight, index, mPanelLeft);
    } else {
        // Copy to the right panel
        mPanelCurrent = mPanelRight;
        this->copyTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
    }
}



void CentralWidget::onEditorStatusIntChanged(int stat)
{
    EditorBinder *binder = dynamic_cast<EditorBinder*>(sender());
    EditorBinder::StatusInt statusInt = static_cast<EditorBinder::StatusInt>(stat);
    EditorBinder::StatusExt statusExt = binder->getStatusExt();

    const EditorList &editors = binder->getEditors();
    foreach(Editor *edit, editors) {
        int idx = mPanelLeft->indexOf(edit);
        if(idx >= 0)
            mPanelLeft->setStatusIcon(idx, statusInt, statusExt);

        idx = mPanelRight->indexOf(edit);
        if(idx >= 0)
            mPanelRight->setStatusIcon(idx, statusInt, statusExt);
    }
}

void CentralWidget::onEditorStatusExtChanged(int stat)
{
    EditorBinder *binder = dynamic_cast<EditorBinder*>(sender());
    EditorBinder::StatusExt statusExt = static_cast<EditorBinder::StatusExt>(stat);
    EditorBinder::StatusExt statusExtOld = binder->getStatusExt();
    EditorBinder::StatusInt statusInt = binder->getStatusInt();

    const EditorList &editors = binder->getEditors();
    foreach(Editor *edit, editors) {
        int idx = mPanelLeft->indexOf(edit);
        if(idx >= 0)
            mPanelLeft->setStatusIcon(idx, statusInt, statusExt);

        idx = mPanelRight->indexOf(edit);
        if(idx >= 0)
            mPanelRight->setStatusIcon(idx, statusInt, statusExt);
    }
    statusExt = statusExtOld;
}




void CentralWidget::onInternalWidgetFocusReceived()
{
    if(sender() == mPanelRight)
        this->setCurrentPanel(mPanelRight);
    else
        this->setCurrentPanel(mPanelLeft);
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
    mMenuSplitTab->setEnabled(false);
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

        if(mPanelCurrent->currentIndex() == idx) {
            mMenuSplitTab->setEnabled(true);
        }
    }

    QAction *action = mContextMenu->exec(QCursor::pos());

    if(action == mMenuClose) {
        onCloseIdx(idx);
    } else if(action == mMenuCloseOthers) {
        onCloseOthersIdx(idx);
    } else if(action == mMenuSplitTab) {
        onSplitIdx(idx);
    } else if(action == mMenuMoveTab) {
        onMoveToOtherIdx(idx);
    } else if(action == mMenuCopyTab) {
        onCopyToOtherIdx(idx);
    }
}


