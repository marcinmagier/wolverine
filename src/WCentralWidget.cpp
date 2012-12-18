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
#include "WDocument.h"
#include "WPanel.h"

#include <QHBoxLayout>
#include <QSplitter>



using namespace Wolverine;


CentralWidget::CentralWidget(QWidget *parent):
    QWidget(parent)
{

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    panelLeft = new Panel(splitter);
    panelRight = new Panel(splitter);
    //panelRight->hide();
    splitter->addWidget(panelLeft);
    splitter->addWidget(panelRight);
    layout->addWidget(splitter);

    editor = new Document();
    panelLeft->addTab(editor, "New");
    Document *editor2 = new Document();
    panelRight->addTab(editor2, "New2");
}

CentralWidget::~CentralWidget()
{

}



void CentralWidget::onCreateNewDoc()
{

}

void CentralWidget::onOpenDoc()
{

}
