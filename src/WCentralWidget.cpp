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
#include "WEditorProxy.h"
#include "WDocument.h"
#include "WPanel.h"

#include "qtmanagedmenu.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QIcon>




#define W_ACTION_MOVE_TAB "MoveTab"





using namespace Wolverine;


CentralWidget::CentralWidget(QWidget *parent):
    QWidget(parent)
{
    currentEditor = new EditorProxy();
    mEditorList.clear();

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    panelLeft = new Panel(splitter);
    panelRight = new Panel(splitter);
    panelRight->hide();
    splitter->addWidget(panelLeft);
    splitter->addWidget(panelRight);
    layout->addWidget(splitter);


    connect( panelLeft, SIGNAL(currentChanged(int)),
                  this, SLOT(onCurrentTabChanged(int)) );
    connect( panelLeft, SIGNAL(tabCloseRequested(int)),
                  this, SLOT(onCloseIdx(int)) );
    connect( panelLeft, SIGNAL(customContextMenuRequested(QPoint)),
                  this, SLOT(onCustomContextMenuRequested(QPoint)) );

    connect( panelRight, SIGNAL(currentChanged(int)),
                   this, SLOT(onCurrentTabChanged(int)) );
    connect( panelRight, SIGNAL(tabCloseRequested(int)),
                   this, SLOT(onCloseIdx(int)) );
    connect( panelRight, SIGNAL(customContextMenuRequested(QPoint)),
                   this, SLOT(onCustomContextMenuRequested(QPoint)) );

    onNew();
    setupContextMenu();
}

CentralWidget::~CentralWidget()
{
    delete currentEditor;
    //layout, spliter and panels are deleted automatically
}



void CentralWidget::removeTab(Panel *panel, int index)
{
    Editor *edit = dynamic_cast<Editor*>(panel->widget(index));
    panel->removeTab(index);
    removeEditor(edit);

    //TODO: nowa zakladka jeżeli to jest ostatnia (lub zamknięcie) - nastrojka
    //jeżeli to jest ostatnia w lewym a w prawym cos jest to przerzuc z prawego do lewego
    //jezeli to jest ostatnia w prawym to ukryj prawy
}


void CentralWidget::moveTab(Panel *from, int fromIdx, Panel *to)
{
    Editor *edit = dynamic_cast<Editor*>(from->widget(fromIdx));
    to->addTab(edit);
}

void CentralWidget::removeEditor(Editor *editor)
{
    mEditorList.removeAll(editor);

    Document *doc = editor->getDocument();
    doc->removeEditor(editor);    // Document deletes editor
    if(!doc->hasEditors())
        delete doc;
}



void CentralWidget::setupContextMenu()
{
    QAction *action;
    mContextMenu = new QtManagedMenu(this, "TabBarContextMenu");
    action = new QAction(tr("New"), mContextMenu);
    action->setIcon(QIcon(":/new.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onNew()) );
    mContextMenu->addAction("New", action);

    action = new QAction(tr("Close"), mContextMenu);
    action->setIcon(QIcon(":/close.png"));
    //action is done within context menu hander
    menuClose = action;
    mContextMenu->addAction("Close", action);

    action = new QAction(tr("Close Others"), mContextMenu);
    //action->setIcon(QIcon(":/close.png"));
    //action is done within context menu hander
    menuCloseOthers = action;
    mContextMenu->addAction("CloseOthers", action);

    action = new QAction(tr("Close All"), mContextMenu);
    action->setIcon(QIcon(":/close_all.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCloseAll()) );
    mContextMenu->addAction("CloseAll", action);

    action = new QAction(mContextMenu);
    //icon and text is set within menu handler
    //action is done within menu hander
    menuMoveTab = action;
    mContextMenu->addAction("MoveTab", action);

    mContextMenu->restoreConfig();
}

