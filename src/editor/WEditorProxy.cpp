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
 *  @file       WEditorProxy.cpp
 *  @brief      Wolverine::EditorProxy class implementation.
 */




#include "WEditorProxy.h"
#include "WEditor.h"
#include "WEditorBinder.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "qtmanagedmenu.h"



#define W_ACTION_CUT "Cut"
#define W_ACTION_COPY "Copy"
#define W_ACTION_PASTE "Paste"

#define W_EDITOR_CONTEXT_MENU  "EditorContextMenu"


using namespace Wolverine;


EditorProxy::EditorProxy()
{
    mCurrentEditor = 0;
    setupContextMenu();
}

EditorProxy::~EditorProxy()
{
    delete mContextMenu;
}


Editor *EditorProxy::getCurrentEditor()
{
    return mCurrentEditor;
}

QString EditorProxy::getCurrentEditorDir()
{
    return mCurrentEditor->getBinder()->canonicalPath();
}

QString EditorProxy::getCurrentEditorName()
{
    return mCurrentEditor->getBinder()->fileName();
}





void EditorProxy::setupContextMenu()
{
    QAction *action;
    GeneralSettings *settings = AppSettings::instance()->general;
    mContextMenu = new QtManagedMenu(0, W_EDITOR_CONTEXT_MENU);
    mContextMenu->setManagerEnabled(settings->isAppCustomizeEnabled());
    connect(     settings, SIGNAL(appCustomizeEnabledChanged(bool)),
             mContextMenu, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    action = new QAction(tr("Cut"), mContextMenu);
    action->setIcon(QIcon(":/cut.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCut()) );
    mContextMenu->addAction(W_ACTION_CUT, action);

    action = new QAction(tr("Copy"), mContextMenu);
    action->setIcon(QIcon(":/copy.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onCopy()) );
    mContextMenu->addAction(W_ACTION_COPY, action);

    action = new QAction(tr("Paste"), mContextMenu);
    action->setIcon(QIcon(":/paste.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onPaste()) );
    mContextMenu->addAction(W_ACTION_PASTE, action);




    mContextMenu->restoreConfig();
}
