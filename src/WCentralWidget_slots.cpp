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
#include "WLib.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include <QApplication>
#include <QCursor>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include <QDebug>


using namespace Wolverine;


#define STATUS_NOTEXISTS_MSG_PATTERN "The file %1 doesn't exist anymore.\nKeep this file in editor?"



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
        setCurrentPanel(mPanelLeft);
        this->copyTab(mPanelRight, index, mPanelLeft);
    } else {
        // Copy to the right panel
        setCurrentPanel(mPanelRight);
        this->copyTab(mPanelLeft, index, mPanelRight);
        mPanelRight->setVisible(true);
    }
}

void CentralWidget::onMoveToApp()
{
    this->onMoveToAppIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onMoveToAppIdx(int index)
{
    Editor *edit = mPanelCurrent->getEditor(index);
    mPanelCurrent->removeTab(index);
    if(mPanelCurrent == mPanelRight) {
        if(mPanelRight->count() == 0) {
            mPanelRight->setVisible(false);
        }
    }
    Lib::openNewInstance(edit->getBinder()->absoluteFilePath());
}

void CentralWidget::onCopyToApp()
{
    this->onCopyToAppIdx(mPanelCurrent->currentIndex());
}

void CentralWidget::onCopyToAppIdx(int index)
{
    Editor *edit = mPanelCurrent->getEditor(index);
    Lib::openNewInstance(edit->getBinder()->absoluteFilePath());
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
            mPanelLeft->setTabIcon(idx, guesEditorStatusIcon(statusInt, statusExt));

        idx = mPanelRight->indexOf(edit);
        if(idx >= 0)
            mPanelRight->setTabIcon(idx, guesEditorStatusIcon(statusInt, statusExt));
    }
}

void CentralWidget::onEditorStatusExtChanged(int stat)
{
    EditorBinder *binder = dynamic_cast<EditorBinder*>(sender());
    EditorBinder::StatusExt statusExt = static_cast<EditorBinder::StatusExt>(stat);
    EditorBinder::StatusExt statusExtOld = binder->getStatusExt();
    EditorBinder::StatusInt statusInt = binder->getStatusInt();

    if(statusExt == EditorBinder::NotExists && statusExtOld != EditorBinder::New) {
        QString message = tr(STATUS_NOTEXISTS_MSG_PATTERN).arg(binder->absoluteFilePath());
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Keep non existing file"), message,
                                                               QMessageBox::Yes | QMessageBox::No,
                                                               QMessageBox::Yes
                                                               );
        if(ret == QMessageBox::No) {
            foreach(Editor *edit, binder->getEditors()) {
                int idx;
                Panel *panel = this->findEditor(edit, &idx);
                if(idx >= 0)
                    this->closeTab(panel, idx);
            }
            this->updatePanels();
            return;
        }
    }

    //TODO: Show message window to inform user about change.
    // statusExt == Normal && statusExt == Normal
        //&& statusInt == Unmodified ==> Ask if file should be reloaded?
        //&& statusInt == Modified ==> Ask if file should be reloaded or saved as new file?


    const EditorList &editors = binder->getEditors();
    foreach(Editor *edit, editors) {
        int idx = mPanelLeft->indexOf(edit);
        if(idx >= 0)
            mPanelLeft->setTabIcon(idx, guesEditorStatusIcon(statusInt, statusExt));

        idx = mPanelRight->indexOf(edit);
        if(idx >= 0)
            mPanelRight->setTabIcon(idx, guesEditorStatusIcon(statusInt, statusExt));
    }
    statusExt = statusExtOld;
}

void CentralWidget::onEditorFileInfoChanged(QFileInfo *fileinfo)
{
    EditorBinder *binder = dynamic_cast<EditorBinder*>(sender());

    const EditorList &editors = binder->getEditors();
    foreach(Editor *edit, editors) {
        int idx = mPanelLeft->indexOf(edit);
        if(idx >= 0)
            mPanelLeft->setTabText(idx, fileinfo->fileName());

        idx = mPanelRight->indexOf(edit);
        if(idx >= 0)
            mPanelRight->setTabText(idx, fileinfo->fileName());
    }
}



void CentralWidget::onInternalWidgetFocusReceived()
{
    if(sender() == mPanelRight)
        this->setCurrentPanel(mPanelRight, true);
    else
        this->setCurrentPanel(mPanelLeft, true);
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

    EditorBinder::StatusExt statExt = mPanelCurrent->getEditor(idx)->getBinder()->getStatusExt();
    bool isNew = (statExt == EditorBinder::New || statExt == EditorBinder::NotExists) ? true : false;

    mMenuClose->setEnabled(false);
    mMenuCloseOthers->setEnabled(false);
    mMenuSplitTab->setEnabled(false);
    mMenuMoveTab->setEnabled(false);
    mMenuCopyTab->setEnabled(false);
    mMenuMoveApp->setEnabled(false);
    mMenuCopyApp->setEnabled(false);

    if(idx >= 0) {
        mMenuClose->setEnabled(true);
        mMenuCopyTab->setEnabled(true);
        if(!isNew)
            mMenuCopyApp->setEnabled(true);

        if(mPanelCurrent->count() > 1) {
            mMenuCloseOthers->setEnabled(true);
            mMenuMoveTab->setEnabled(true);
            if(!isNew)
                mMenuMoveApp->setEnabled(true);
        } else {
            // Only one tab
            if(mPanelCurrent == mPanelRight) {
                mMenuMoveTab->setEnabled(true);
                if(!isNew)
                    mMenuMoveApp->setEnabled(true);
            }
        }

        if(mPanelCurrent->currentIndex() == idx) {
            mMenuSplitTab->setEnabled(true);
        }
    }

    QAction *action = mContextMenu->exec(QCursor::pos());

    if(action == mMenuNew) {
        newTab(idx+1);
    } else if(action == mMenuClose) {
        closeTab(idx);
    } else if(action == mMenuCloseOthers) {
        closeOtherTabs(idx);
    } else if(action == mMenuSplitTab) {
        onSplitIdx(idx);
    } else if(action == mMenuMoveTab) {
        onMoveToOtherIdx(idx);
    } else if(action == mMenuCopyTab) {
        onCopyToOtherIdx(idx);
    } else if(action == mMenuMoveApp) {
        onMoveToAppIdx(idx);
    } else if(action == mMenuCopyApp) {
        onCopyToAppIdx(idx);
    }
}


