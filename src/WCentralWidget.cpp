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

#include <QHBoxLayout>
#include <QSplitter>
#include <QIcon>



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
    panelLeft->setIconSize(QSize(12, 12));
    panelRight = new Panel(splitter);
    panelRight->setIconSize(QSize(12, 12));
    panelRight->hide();
    splitter->addWidget(panelLeft);
    splitter->addWidget(panelRight);
    layout->addWidget(splitter);


    connect( panelLeft, SIGNAL(currentChanged(int)),
                  this, SLOT(onCurrentTabChanged(int)) );
    connect( panelLeft, SIGNAL(tabCloseRequested(int)),
                  this, SLOT(onTabCloseRequest(int)) );
    connect( panelRight, SIGNAL(currentChanged(int)),
                   this, SLOT(onCurrentTabChanged(int)) );
    connect( panelRight, SIGNAL(tabCloseRequested(int)),
                   this, SLOT(onTabCloseRequest(int)) );


    onCreateNewDoc();
}

CentralWidget::~CentralWidget()
{
    delete currentEditor;
    //layout, spliter and panels are deleted automatically
}



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

}

void CentralWidget::onCloseOthers()
{

}

void CentralWidget::onCloseAll()
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
    Panel *panel = panelRight->hasFocus() ? panelRight : panelLeft;
    Editor *edit = dynamic_cast<Editor*>(panel->widget(index));
    panel->removeTab(index);
    removeEditor(edit);

    //TODO: nowa zakladka jeżeli to jest ostatnia (lub zamknięcie) - nastrojka
    //jeżeli to jest ostatnia w lewym a w prawym cos jest to przerzuc z prawego do lewego
    //jezeli to jest ostatnia w prawym to ukryj prawy
}


void CentralWidget::removeEditor(Editor *editor)
{
    mEditorList.removeAll(editor);

    Document *doc = editor->getDocument();
    doc->removeEditor(editor);    // Document deletes editor
    if(!doc->hasEditors())
        delete doc;
}

