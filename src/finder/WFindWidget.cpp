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
    QWidget(parent),
    mFinder(finder),
    ui(new Ui::FindWidget)
{
    mGenSettings = AppSettings::instance()->general;

    ui->setupUi(this);

    ui->btnOptCaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btnOptCaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btnOptCaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    connect( ui->btnOptCaseSensitive, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection );

    ui->btnOptWords->setIcon(QIcon(":/search_words.png"));
    ui->btnOptWords->setToolTip(tr("Whole Words"));
    ui->btnOptWords->setChecked(mGenSettings->isFindWholeWordsSet());
    connect( ui->btnOptWords, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection );

    ui->btnOptRegexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btnOptRegexp->setToolTip(tr("Regular Expression"));
    ui->btnOptRegexp->setChecked(mGenSettings->isFindRegexpSet());
    connect( ui->btnOptRegexp, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection );

    ui->btnOptReverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btnOptReverse->setToolTip(tr("Reverse Direction"));
    ui->btnOptReverse->setChecked(mGenSettings->isFindReverseDirectionSet());
    connect( ui->btnOptReverse, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindReverseDirection(bool)), Qt::DirectConnection );

    ui->btnOptWrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btnOptWrap->setToolTip(tr("Wrap"));
    ui->btnOptWrap->setChecked(mGenSettings->isFindWrapSet());
    connect( ui->btnOptWrap, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindWrap(bool)), Qt::DirectConnection );

    ui->btnOptInSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btnOptInSelection->setToolTip(tr("In Selection"));
    ui->btnOptInSelection->setChecked(mGenSettings->isFindInSelectionSet());
    connect( ui->btnOptInSelection, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindInSelection(bool)), Qt::DirectConnection );

    ui->btnOptMark->setIcon(QIcon(":/search_mark.png"));
    ui->btnOptMark->setToolTip("Bookmark Line");
    ui->btnOptMark->setChecked(mGenSettings->isFindMarkSet());
    connect( ui->btnOptMark, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindMark(bool)), Qt::DirectConnection );

    ui->btnOptInSubDirs->setIcon(QIcon(":/search_subdirs.png"));
    ui->btnOptInSubDirs->setToolTip(tr("Search in sub-folders"));
    ui->btnOptInSubDirs->setChecked(mGenSettings->isFindInSubDirsSet());
    connect( ui->btnOptInSubDirs, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindInSubDirs(bool)), Qt::DirectConnection );

    ui->btnOptInHiddenDirs->setIcon(QIcon(":/search_hidden.png"));
    ui->btnOptInHiddenDirs->setToolTip(tr("Search in hidden folders"));
    ui->btnOptInHiddenDirs->setChecked(mGenSettings->isFindInHiddenDirsSet());
    connect( ui->btnOptInHiddenDirs, SIGNAL(toggled(bool)),
             mGenSettings, SLOT(setFindInHiddenDirs(bool)), Qt::DirectConnection );

    ui->btn2SelectDir->setIcon(QIcon(":/search_select_dir.png"));
    ui->btn2SelectDir->setToolTip(tr("Select Directory"));
    connect( ui->btn2SelectDir, SIGNAL(clicked()),
                          this, SLOT(onSelectDirectoryClicked()) );

    ui->btn2SelectCurrentDir->setIcon(QIcon(":/search_current_dir.png"));
    ui->btn2SelectCurrentDir->setToolTip(tr("Select Current Document's Directory"));
    connect( ui->btn2SelectCurrentDir, SIGNAL(clicked()),
                                 this, SLOT(onCurrentDirectoryClicked()) );
}

FindWidget::~FindWidget()
{
    delete ui;
}



void FindWidget::setCurrentIndex(Idx idx)
{
    switch(idx) {
    case FindIdx:
        setupFindWidget();
        break;

    case ReplaceIdx:
        setupReplaceWidget();
        break;

    case FindInFilesIdx:
        setupFindInFilesWidget();
        break;
    }
}

FindWidget::Idx FindWidget::getCurrentIndex()
{
    return mIdx;
}


FindRequest FindWidget::getFindRequest()
{
    FindRequest opt;


    return opt;
}



void FindWidget::onSelectDirectoryClicked()
{

}

void FindWidget::onCurrentDirectoryClicked()
{

}



void FindWidget::setupFindWidget()
{
    mIdx = FindIdx;
    ui->stButtons->setCurrentIndex(mIdx);

    ui->btnOptInSubDirs->hide();
    ui->btnOptInHiddenDirs->hide();

    ui->cmbReplacePattern->hide();
    ui->cmbFilters->hide();
    ui->cmbDirectory->hide();
    ui->lblReplace->hide();
    ui->lblFilters->hide();
    ui->lblDirectory->hide();

    ui->btn1FindNext->hide();
    ui->btn1Replace->hide();
    ui->btn1ReplaceFind->hide();
    ui->btn1ReplaceAll->hide();
    ui->btn1ReplaceAllInTabs->hide();
    ui->btn2FindAll->hide();
    ui->btn2ReplaceAll->hide();
    ui->btn2SelectDir->hide();
    ui->btn2SelectCurrentDir->hide();

    ui->btnOptReverse->show();
    ui->btnOptWrap->show();
    ui->btnOptInSelection->show();
    ui->btnOptMark->show();

    ui->btn0FindNext->show();
    ui->btn0FindPrev->show();
    ui->btn0FindAll->show();
    ui->btn0FindAllInTabs->show();
}


void FindWidget::setupReplaceWidget()
{
    mIdx = ReplaceIdx;
    ui->stButtons->setCurrentIndex(mIdx);

    ui->btnOptInSubDirs->hide();
    ui->btnOptInHiddenDirs->hide();
    ui->btnOptMark->hide();

    ui->cmbFilters->hide();
    ui->cmbDirectory->hide();
    ui->lblFilters->hide();
    ui->lblDirectory->hide();

    ui->btn0FindNext->hide();
    ui->btn0FindPrev->hide();
    ui->btn0FindAll->hide();
    ui->btn0FindAllInTabs->hide();
    ui->btn2FindAll->hide();
    ui->btn2ReplaceAll->hide();
    ui->btn2SelectDir->hide();
    ui->btn2SelectCurrentDir->hide();



    ui->btnOptReverse->show();
    ui->btnOptWrap->show();
    ui->btnOptInSelection->show();

    ui->cmbReplacePattern->show();
    ui->lblReplace->show();

    ui->btn1FindNext->show();
    ui->btn1Replace->show();
    ui->btn1ReplaceFind->show();
    ui->btn1ReplaceAll->show();
    ui->btn1ReplaceAllInTabs->show();

}


void FindWidget::setupFindInFilesWidget()
{
    mIdx = FindInFilesIdx;
    ui->stButtons->setCurrentIndex(mIdx);

    ui->btnOptReverse->hide();
    ui->btnOptWrap->hide();
    ui->btnOptInSelection->hide();
    ui->btnOptMark->hide();

    ui->btn0FindNext->hide();
    ui->btn0FindPrev->hide();
    ui->btn0FindAll->hide();
    ui->btn0FindAllInTabs->hide();
    ui->btn1FindNext->hide();
    ui->btn1Replace->hide();
    ui->btn1ReplaceFind->hide();
    ui->btn1ReplaceAll->hide();
    ui->btn1ReplaceAllInTabs->hide();

    ui->btnOptInSubDirs->show();
    ui->btnOptInHiddenDirs->show();

    ui->cmbReplacePattern->show();
    ui->cmbFilters->show();
    ui->cmbDirectory->show();
    ui->lblReplace->show();
    ui->lblFilters->show();
    ui->lblDirectory->show();

    ui->btn2FindAll->show();
    ui->btn2ReplaceAll->show();
    ui->btn2SelectDir->show();
    ui->btn2SelectCurrentDir->show();
}


QString FindWidget::getCurrentEditorDir()
{
    return QString();
}
