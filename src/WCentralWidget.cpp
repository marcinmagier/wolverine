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
 *  @file       WCentralWidget.cpp
 *  @brief      Wolverine::CentralWidget class implementation.
 */


#include "WCentralWidget.h"
#include "WEditor.h"
#include "WEditorBinder.h"
#include "WEditorProxy.h"
#include "WPanel.h"
#include "WLib.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "qtmanagedmenu.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QIcon>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>

#include <QDebug>


#define W_ACTION_NEW "New"
#define W_ACTION_CLOSE "Close"
#define W_ACTION_CLOSE_OTHERS "CloseOthers"
#define W_ACTION_CLOSE_ALL "CloseAll"
#define W_ACTION_SPLIT_TAB "SplitTab"
#define W_ACTION_MOVE_TAB "MoveTab"
#define W_ACTION_COPY_TAB "CopyTab"
#define W_ACTION_MOVE_APP "MoveApp"
#define W_ACTION_COPY_APP "CopyApp"


#define W_TABBAR_CONTEXT_MENU  "TabBarContextMenu"

#define CLOSE_MODIVIED_MSG_PATTERN "The document %1 has been modified.\nDo you want to save changes?"
#define STATUS_NOTEXISTS_MSG_PATTERN "The file %1 doesn't exist anymore.\nKeep this file in editor?"
#define STATUS_MODIFIED_MSG_PATTERN "The file %1 has been modified by another program.\nDo you want to reload it?"






using namespace Wolverine;


/**
 *  Constructor.
 *
 * @param parent
 */
CentralWidget::CentralWidget(QWidget *parent):
    QWidget(parent)
{
    setAcceptDrops(true);
    mCurrentEditor = EditorProxy::instance();

    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mSplitter = new QSplitter(this);
    mSplitter->setOrientation(Qt::Horizontal);
    mPanelLeft = new Panel(mSplitter);
    mPanelRight = new Panel(mSplitter);
    mPanelRight->hide();
    mSplitter->addWidget(mPanelLeft);
    mSplitter->addWidget(mPanelRight);
    mLayout->addWidget(mSplitter);


    connect( mPanelLeft, SIGNAL(tabCloseRequested(int)),
                  this, SLOT(closeTab(int)) );
    connect( mPanelLeft, SIGNAL(customContextMenuRequested(QPoint)),
                  this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mPanelLeft, SIGNAL(focusReceived()),
                   this, SLOT(onInternalWidgetFocusReceived()) );
    connect( mPanelLeft, SIGNAL(tabNewRequested()),
                   this, SLOT(newTab()) );

    connect( mPanelRight, SIGNAL(tabCloseRequested(int)),
                   this, SLOT(closeTab(int)) );
    connect( mPanelRight, SIGNAL(customContextMenuRequested(QPoint)),
                   this, SLOT(onCustomContextMenuRequested(QPoint)) );
    connect( mPanelRight, SIGNAL(focusReceived()),
                   this, SLOT(onInternalWidgetFocusReceived()) );
    connect( mPanelRight, SIGNAL(tabNewRequested()),
                    this, SLOT(newTab()) );

    connect( mCurrentEditor, SIGNAL(currentEditorScrollHChanged(int)),
                       this, SLOT(onEditorScrollHChanged(int)) );
    connect( mCurrentEditor, SIGNAL(currentEditorScrollVChanged(int)),
                       this, SLOT(onEditorScrollVChanged(int)) );

    mSettings = AppSettings::instance();

    setCurrentPanel(mPanelLeft);
    setupContextMenu();
}

/**
 *  Destructor.
 */
CentralWidget::~CentralWidget()
{
    delete mContextMenu;
    //layout, spliter and panels are deleted automatically
}


/**
 *  Brings window to front.
 */
void CentralWidget::bringToFront()
{
    raise();
    show();
    activateWindow();
}


/**
 *  Creates new tab.
 */
//slot
void CentralWidget::newTab()
{
    this->newTab(mPanelCurrent, mPanelCurrent->count());
}


/**
 *  Creates new tab.
 *
 * @param index
 */
//slot
void CentralWidget::newTab(int index)
{
    this->newTab(mPanelCurrent, index);
}


/**
 *  Creates new tab.
 *
 * @param panel
 * @param index
 */
void CentralWidget::newTab(Panel *panel, int index)
{
    EditorBinder *binder = new EditorBinder();
    Editor *edit = binder->getEditor();


    int idx = panel->insertTab(index, edit, guesEditorStatusIcon(binder->getStatusInt(), binder->getStatusExt()));
    panel->setCurrentIndex(idx);
    //currentEditor is updated via slot

    connect( binder, SIGNAL(statusIntChanged(int)),
               this, SLOT(onEditorStatusIntChanged(int)) );
    connect( binder, SIGNAL(statusExtChanged(int)),
               this, SLOT(onEditorStatusExtChanged(int)) );
    connect( binder, SIGNAL(fileInfoChanged(QFileInfo*)),
               this, SLOT(onEditorFileInfoChanged(QFileInfo*)) );
}




/**
 *  Opens given file in new tab.
 *
 * @param path
 */
//slot
void CentralWidget::openTab(const QString &path)
{
    this->openTab(mPanelCurrent, path);
}


/**
 *  Opens given file in new tab
 *
 * @param panel
 * @param path
 */
void CentralWidget::openTab(Panel *panel, const QString &path)
{
    bringToFront();

    // If only one and empty tab is
    if( (mPanelRight->count() == 0) && (mPanelLeft->count() == 1) ) {
        Editor *first = mPanelLeft->getEditor(0);
        if( (first->length() == 0) && (first->getBinder()->getStatusExt() == EditorBinder::New) ) {
            this->closeTab(mPanelLeft, 0);
        }
    }

    QString file = Lib::getPathFromFile(path);
    int line = Lib::getLineFromFile(path);
    if(line>0)
        line--; //Lines start from 0.

    if(setCurrentIfExists(mPanelLeft, file))
        return;

    if(setCurrentIfExists(mPanelRight, file))
        return;

    EditorBinder *binder = new EditorBinder(file);
    Editor *edit = binder->getEditor();
    edit->setCursorPosition(line, 0);

    setCurrentPanel(panel);
    int idx = mPanelCurrent->addTab(edit, guesEditorStatusIcon(binder->getStatusInt(), binder->getStatusExt()));
    mPanelCurrent->setCurrentIndex(idx);

    connect( binder, SIGNAL(statusIntChanged(int)),
               this, SLOT(onEditorStatusIntChanged(int)) );
    connect( binder, SIGNAL(statusExtChanged(int)),
               this, SLOT(onEditorStatusExtChanged(int)) );
    connect( binder, SIGNAL(fileInfoChanged(QFileInfo*)),
               this, SLOT(onEditorFileInfoChanged(QFileInfo*)) );
}


/**
 *  Shows file dialog and opens selected file in new tab.
 */
//slot
void CentralWidget::openTabForm()
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
        this->openTab(mPanelCurrent, file);
    }
}




/**
 *  Saves current tab.
 */
//slot
void CentralWidget::saveTab()
{
    this->saveTab(mPanelCurrent, mPanelCurrent->currentIndex());
}


/**
 *  Saves given tab.
 *
 * @param index
 */
//slot
void CentralWidget::saveTab(int index)
{
    this->saveTab(mPanelCurrent, index);
}


/**
 *  Saves given tab.
 *
 * @param panel
 * @param index
 */
void CentralWidget::saveTab(Panel *panel, int index)
{
    EditorBinder *binder = panel->getEditor(index)->getBinder();
    if(binder->getStatusExt() == EditorBinder::New) {
        saveTabForm(panel, index);
        return;
    }

    binder->saveFile();
}


/**
 *  Shows save file dialog and saves current editor to the chosen file.
 */
//slot
void CentralWidget::saveTabForm()
{
    this->saveTabForm(mPanelCurrent, mPanelCurrent->currentIndex());
}


/**
 *  Shows save file dialog and saves given editor to the chosen file.
 *
 * @param index
 */
//slot
void CentralWidget::saveTabForm(int index)
{
    this->saveTabForm(mPanelCurrent, index);
}


/**
 *  Shows save file dialog and saves given editor to the chosen file.
 *
 * @param panel
 * @param index
 */
void CentralWidget::saveTabForm(Panel *panel, int index)
{
    EditorBinder *binder = panel->getEditor(index)->getBinder();

    QString initialPath;
    if(mSettings->general->isAppOpenFromCurrentEnabled()) {
        initialPath = binder->absolutePath();
    } else {
        initialPath = mSettings->general->getAppLastOpenedDir();
    }

    QString newFile = QFileDialog::getSaveFileName(this, tr("Save file"), initialPath);
    if(newFile.isEmpty())
        return;

    binder->saveFile(newFile);
}


/**
 *  Saves all tabs.
 */
//slot
void CentralWidget::saveAllTabs()
{
    Panel *prevPanel = mPanelCurrent;
    int prevIdx = mPanelCurrent->currentIndex();

    saveAllTabs(mPanelLeft);
    saveAllTabs(mPanelRight);

    setCurrentPanel(prevPanel, true);
    prevPanel->setCurrentIndex(prevIdx);
}


/**
 *  Saves all tabs on a given panel.
 *
 * @param panel
 */
void CentralWidget::saveAllTabs(Panel *panel)
{
    int len = panel->count();
    if(len > 0) {
        setCurrentPanel(panel);
        for(int i=0; i<len; i++) {
            panel->setCurrentIndex(i);
            this->saveTab(panel, i);
        }
    }
}




/**
 *  Closes current tab.
 */
//slot
void CentralWidget::closeTab()
{
    this->closeTab(mPanelCurrent, mPanelCurrent->currentIndex());
    this->updatePanels();
}


/**
 *  Closes given tab.
 * @param index
 */
//slot
void CentralWidget::closeTab(int index)
{
    this->closeTab(mPanelCurrent, index);
    this->updatePanels();
}


/**
 *  Closes given tab on a given panel.
 *
 * @param panel
 * @param index
 */
bool CentralWidget::closeTab(Panel *panel, int index)
{
    Editor *edit = panel->getEditor(index);
    EditorBinder *binder = edit->getBinder();

    if(binder->getStatusInt() == EditorBinder::Modified) {
        if( !((binder->getStatusExt() == EditorBinder::New) && (edit->length() == 0)) )
        {
            QString message = tr(CLOSE_MODIVIED_MSG_PATTERN).arg(binder->canonicalFilePath());
            QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Save file"), message,
                                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                    QMessageBox::Save);
            if(ret == QMessageBox::Cancel)
                return false;
            if(ret == QMessageBox::Save) {
                if(binder->getStatusExt() == EditorBinder::New)
                    this->saveTabForm(panel, index);
                else
                    binder->saveFile();
            }
        }
    }
    panel->removeTab(index);
    mCurrentEditor->setCurrentEditor(0);
    Editor::removeEditor(edit);
    return true;
}


/**
 *  Closes all but current tab.
 */
//slot
void CentralWidget::closeOtherTabs()
{
    this->closeOtherTabs(mPanelCurrent, mPanelCurrent->currentIndex());
}


/**
 *  Closes all but given tab
 *
 * @param index
 */
//slot
void CentralWidget::closeOtherTabs(int index)
{
    this->closeOtherTabs(mPanelCurrent, index);
}


/**
 *  Closes all but given tab on a given panel.
 *
 * @param panel
 * @param index
 */
bool CentralWidget::closeOtherTabs(Panel *panel, int index)
{
    if(panel->count() < 2)
        return false;

    int idxToRemove = 0;    // Remove first widget for i < index
    int i=-1;
    int numOfTabs= panel->count();
    while(++i < numOfTabs) {
        if(i == index) {
            idxToRemove = 1;    // Remove second widget for i > index
            continue;
        }
        panel->setCurrentIndex(idxToRemove);
        if(!this->closeTab(panel, idxToRemove))
            return false;
    }
    return true;
}


/**
 *  Closes all tabs.
 */
//slot
void CentralWidget::closeAllTabs()
{
    this->closeAllTabs( mSettings->general->isAppCloseWhenLastTabClosed() );
}


/**
 *  Closes all tabs
 *
 * @param closeApp
 */
bool CentralWidget::closeAllTabs(bool closeApp)
{
    if(!closeAllTabs(mPanelRight))
        return false;
    if(!closeAllTabs(mPanelLeft))
        return false;

    if(closeApp) {
        qApp->quit();
    } else {
        mCurrentEditor->setCurrentEditor(0);
        mPanelRight->hide();
        setCurrentPanel(mPanelLeft);
        newTab();
    }

    return true;
}


/**
 *  Closes all tabs on a given panel.
 *
 * @param panel
 */
bool CentralWidget::closeAllTabs(Panel *panel)
{
    while(panel->count() > 0) {
        panel->setCurrentIndex(0);
        if(!this->closeTab(panel, 0))
            return false;
    }

    return true;
}




/**
 *  Splits current tab.
 */
//slot
void CentralWidget::splitTab()
{
    this->splitTab(mPanelCurrent->currentIndex());
}


/**
 *  Splits given tab.
 *
 * @param index
 */
void CentralWidget::splitTab(int index)
{
    mPanelCurrent->splitTab(index);
}




/**
 *  Copies current tab to other panel.
 */
//slot
void CentralWidget::copyTabToOther()
{
    this->copyTabToOther(mPanelCurrent->currentIndex());
}


/**
 *  Copies given tab to other panel.
 *
 * @param index
 */
//slot
void CentralWidget::copyTabToOther(int index)
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


/**
 *  Copies given tab.
 *
 * @param from
 * @param fromIdx
 * @param to
 */
void CentralWidget::copyTab(Panel *from, int fromIdx, Panel *to)
{
    Editor *edit = from->getEditor(fromIdx);
    setCurrentPanel(to);
    int idx = to->indexOf(edit);
    if(idx<0) {
        Editor *copy = edit->getLinkedCopy();
        EditorBinder *binder = copy->getBinder();
        to->addTab(copy, guesEditorStatusIcon(binder->getStatusInt(), binder->getStatusExt()));
        to->setCurrentWidget(copy);
    } else {
        // There is already a copy of the editor - select it
        to->setCurrentIndex(idx);
    }
}


/**
 *  Moves current tab to other panel.
 */
//slot
void CentralWidget::moveTabToOther()
{
    this->copyTabToOther(mPanelCurrent->currentIndex());
}


/**
 *  Moves given tab to other panel.
 *
 * @param index
 */
//slot
void CentralWidget::moveTabToOther(int index)
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


/**
 *  Moves given tab.
 *
 * @param from
 * @param fromIdx
 * @param to
 */
void CentralWidget::moveTab(Panel *from, int fromIdx, Panel *to)
{
    Editor *edit = from->getEditor(fromIdx);
    from->removeTab(fromIdx);
    setCurrentPanel(to);
    int idx = to->indexOf(edit);
    if(idx<0) {
        EditorBinder *binder = edit->getBinder();
        to->addTab(edit, guesEditorStatusIcon(binder->getStatusInt(), binder->getStatusExt()));
        to->setCurrentWidget(edit);
    } else {
        // There is already a copy of the editor on the other panel
        // Remove this linked copy
        Editor::removeEditor(edit);
        to->setCurrentIndex(idx);
    }
}


/**
 *  Moves all tabs.
 *
 * @param from
 * @param to
 */
void CentralWidget::moveAllTabs(Panel *from, Panel *to)
{
    int idx = to->currentIndex();
    if(to->count() == 0)
        idx = from->currentIndex();

    int fromLength = from->count();
    for(int i=0; i<fromLength; i++) {
        Editor *edit = from->getEditor(0);
        EditorBinder *binder = edit->getBinder();
        from->removeTab(0);
        to->addTab(edit, guesEditorStatusIcon(binder->getStatusInt(), binder->getStatusExt()));
    }
    setCurrentPanel(to);
    to->setCurrentIndex(idx);
}


/**
 *  Copies current tab to new app.
 */
//slot
void CentralWidget::copyTabToApp()
{
    this->copyTabToApp(mPanelCurrent->currentIndex());
}


/**
 *  Copies given tab to new app.
 *
 * @param index
 */
//slot
void CentralWidget::copyTabToApp(int index)
{
    Editor *edit = mPanelCurrent->getEditor(index);
    Lib::openNewInstance(edit->getBinder()->absoluteFilePath());
}


/**
 *  Moves current tab to new app.
 */
//slot
void CentralWidget::moveTabToApp()
{
    this->moveTabToApp(mPanelCurrent->currentIndex());
}


/**
 *  Moves given tab to new app.
 *
 * @param index
 */
//slot
void CentralWidget::moveTabToApp(int index)
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




/**
 *  Update panel layout.
 */
void CentralWidget::updatePanels()
{
    if(mPanelCurrent->count() == 0) {
        if(mPanelCurrent == mPanelLeft)
            this->moveAllTabs(mPanelRight, mPanelLeft);
        mPanelRight->setVisible(false);
        this->setCurrentPanel(mPanelLeft, true);
    }

    if(mPanelLeft->count() == 0) {
        if( mSettings->general->isAppCloseWhenLastTabClosed() ) {
            qApp->quit();
        } else {
            mCurrentEditor->setCurrentEditor(0);
            newTab();
        }
    }

    if(mCurrentEditor->getCurrentEditor() == 0)
        this->setCurrentEditor(mPanelCurrent->getEditor(mPanelCurrent->currentIndex()));
}


/**
 *  Sets current panel.
 *
 * @param panel
 * @param updateEditor
 */
void CentralWidget::setCurrentPanel(Panel *panel, bool updateEditor)
{
    if(mPanelCurrent != panel) {
        mPanelCurrent = panel;
        if(panel == mPanelLeft) {
            mPanelLeft->setActive(true);
            mPanelRight->setActive(false);
        } else {
            mPanelLeft->setActive(false);
            mPanelRight->setActive(true);
        }

        if(updateEditor)
            this->setCurrentEditor(mPanelCurrent->getEditor(mPanelCurrent->currentIndex()));
    }
}


/**
 *  Sets current editor.
 *
 * @param editor
 */
void CentralWidget::setCurrentEditor(Editor *editor)
{
    mCurrentEditor->setCurrentEditor(editor);
    editor->setFocus();

}


/**
 *  Finds given editor.
 *
 * @param editor
 * @param retIdx
 * @return
 */
Panel* CentralWidget::findEditor(Editor *editor, int *retIdx)
{
    int idx = mPanelLeft->indexOf(editor);
    if(idx >= 0) {
        *retIdx = idx;
        return mPanelLeft;
    }

    idx = mPanelRight->indexOf(editor);
    if(idx >= 0) {
        *retIdx = idx;
        return mPanelRight;
    }

    *retIdx = -1;
    return mPanelCurrent;
}


/**
 *  Activate given editor if it already exists.
 *
 * @param panel
 * @param editor
 * @param line
 * @return
 */
bool CentralWidget::setCurrentIfExists(Panel *panel, Editor *editor, int line)
{
    int idx = panel->indexOf(editor);
    if(idx >= 0) {
        setCurrentPanel(panel);
        mPanelCurrent->setCurrentIndex(idx);
        if(line >= 0)
            mPanelCurrent->getEditor(idx)->setCursorPosition(line, 0);
        return true;
    }

    return false;
}


/**
 *  Activate given editor if it already exists.
 *
 * @param panel
 * @param editor
 * @param line
 * @return
 */
bool CentralWidget::setCurrentIfExists(Panel *panel, const QString &path, int line)
{
    int idx = panel->indexOf(path);
    if(idx >= 0) {
        setCurrentPanel(panel);
        mPanelCurrent->setCurrentIndex(idx);
        if(line >= 0)
            mPanelCurrent->getEditor(idx)->setCursorPosition(line, 0);
        return true;
    }

    return false;
}




QIcon CentralWidget::guesEditorStatusIcon(EditorBinder::StatusInt statInt, EditorBinder::StatusExt statExt)
{
    if(statExt == EditorBinder::ReadOnly)
        return QIcon(":/save_grey.png");


    if( (statExt == EditorBinder::Normal) && (statInt == EditorBinder::Unmodified) )
        return QIcon(":/save_blue.png");

    return QIcon(":/save_red.png");
}








void CentralWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void CentralWidget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        foreach(QUrl url, event->mimeData()->urls()) {
            QString path = url.path();
#ifdef Q_OS_WIN
            // file name start with "/" on windows
            if(path.startsWith('/'))
                path.remove(0, 1);
#endif
            if(!path.isEmpty()) {
                if(mPanelRight->underMouse())
                    openTab(mPanelRight, path);
                else
                    openTab(mPanelLeft, path);
            }
        }
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

    if((statusExt == EditorBinder::NotExists) && (statusExtOld != EditorBinder::New)) {
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
    } else if( (statusExt == statusExtOld) && statusExt == EditorBinder::Normal) {
        if(statusInt == EditorBinder::Unmodified) {
            QString message = tr(STATUS_MODIFIED_MSG_PATTERN).arg(binder->absoluteFilePath());
            QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Reload"), message,
                                                                   QMessageBox::Yes | QMessageBox::No,
                                                                   QMessageBox::Yes
                                                                   );
            if(ret == QMessageBox::Yes) {
                binder->loadFile();
            }
        }
    }

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


void CentralWidget::onEditorScrollHChanged(int range)
{
    Panel *other;
    if(mPanelCurrent == mPanelLeft)
        other = mPanelRight;
    else
        other = mPanelLeft;
    if(other->count() == 0)
        return;

    Editor *edit = other->getEditor(other->currentIndex());
    edit->updateScrollH(range);
}

void CentralWidget::onEditorScrollVChanged(int range)
{
    Panel *other;
    if(mPanelCurrent == mPanelLeft)
        other = mPanelRight;
    else
        other = mPanelLeft;
    if(other->count() == 0)
        return;

    Editor *edit = other->getEditor(other->currentIndex());
    edit->updateScrollV(range);
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
    if(idx < 0)
        idx = mPanelCurrent->currentIndex();

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
        splitTab(idx);
    } else if(action == mMenuMoveTab) {
        moveTabToOther(idx);
    } else if(action == mMenuCopyTab) {
        copyTabToOther(idx);
    } else if(action == mMenuMoveApp) {
        moveTabToApp(idx);
    } else if(action == mMenuCopyApp) {
        copyTabToApp(idx);
    }
}




void CentralWidget::setupContextMenu()
{
    QAction *action;
    GeneralSettings *settings = AppSettings::instance()->general;
    mContextMenu = new QtManagedMenu(this, W_TABBAR_CONTEXT_MENU);
    mContextMenu->setManagerEnabled(settings->isAppCustomizeEnabled());
    connect(     settings, SIGNAL(appCustomizeEnabledChanged(bool)),
             mContextMenu, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    action = new QAction(tr("New"), mContextMenu);
    action->setIcon(QIcon(":/new.png"));
    //action is handled within context menu hander
    mMenuNew = action;
    mContextMenu->addAction(W_ACTION_NEW, action);

    action = new QAction(tr("Close"), mContextMenu);
    action->setIcon(QIcon(":/close.png"));
    //action is handled within context menu hander
    mMenuClose = action;
    mContextMenu->addAction(W_ACTION_CLOSE, action);

    action = new QAction(tr("Close Others"), mContextMenu);
    //action->setIcon(QIcon(":/close.png"));
    //action is handled within context menu hander
    mMenuCloseOthers = action;
    mContextMenu->addAction(W_ACTION_CLOSE_OTHERS, action);

    action = new QAction(tr("Close All"), mContextMenu);
    action->setIcon(QIcon(":/close_all.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(closeAllTabs()) );
    mContextMenu->addAction(W_ACTION_CLOSE_ALL, action);

    action = new QAction(tr("Split"), mContextMenu);
    //action is handled within context menu hander
    mMenuSplitTab = action;
    mContextMenu->addAction(W_ACTION_SPLIT_TAB, action);

    action = new QAction(mContextMenu);
    //text is set within menu handler
    //action is handled within menu hander
    mMenuMoveTab = action;
    mContextMenu->addAction(W_ACTION_MOVE_TAB, action);

    action = new QAction(mContextMenu);
    //text is set within menu handler
    //action is handled within menu hander
    mMenuCopyTab = action;
    mContextMenu->addAction(W_ACTION_COPY_TAB, action);

    mMenuMoveApp = new QAction(tr("Move to new instance"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_MOVE_APP, mMenuMoveApp);

    mMenuCopyApp = new QAction(tr("Copy to new instance"), mContextMenu);
    //action is handled within menu hander
    mContextMenu->addAction(W_ACTION_COPY_APP, mMenuCopyApp);

    mContextMenu->restoreConfig();
}

