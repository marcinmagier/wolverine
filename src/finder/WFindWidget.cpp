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
 *  @file       WFindWidget.cpp
 *  @brief      Wolverine::FindWidget class implementation.
 */



#include "WFindWidget.h"
#include "ui_WFindWidget.h"
#include "WFinder.h"
#include "WEditor.h"
#include "WEditorBinder.h"
#include "WEditorProxy.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include <QLineEdit>
#include <QFileDialog>
#include <QDir>

using namespace Wolverine;



/**
 *  Constructor
 *
 * @param parent
 */
FindWidget::FindWidget(Finder *finder, QWidget *parent) :
    QDockWidget(parent),
    mFinder(finder),
    ui(new Ui::FindWidget)
{
    mGenSettings = AppSettings::instance()->general;

    ui->setupUi(this);


}

FindWidget::~FindWidget()
{
    delete ui;
}
